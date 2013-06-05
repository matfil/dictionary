#include "preprocess.h"
#include "compare.hpp"
#include "RBtree.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>


void preprocess (std::string filename, std::string outputName, RBtree<std::string,std::string,Strcomp>& defines, std::vector<std::string>& inputFileNames) throw (BadInput)
{
	std::ifstream input;
	std::ofstream output;

	std::ifstream test;

	std::string word;

	//otwieranie plików do czytania i pisania
	input.open(filename,std::ifstream::in);
	
	if ( !( input.is_open() ) ) //czy jest z czego czytać?
	{
		throw BadInput();
	}

	test.open(outputName,std::ifstream::in);
	if ( !( test.is_open() ) ) //czy istnieje plik, do którego mam pisać?
	{
		output.open(outputName,std::ofstream::out); //stwórz
	}
	else
	{
		test.close();
		output.open(outputName,std::ofstream::app); //dopisuj
	}

	//---------------------------------------

	auto result = std::find(inputFileNames.begin(),inputFileNames.end(),filename);
	if (result!=inputFileNames.end())
	{
		input.close();
		output.close();
		return;
	}
	else
		inputFileNames.push_back(filename);

	std::string l;
	while(std::getline(input,l))//powtarzaj dopóki można pobrać kolejną linię
	{
		std::stringstream line;//stwórz strumień z którego będą pobierane słowa
		line << l; 

		while(line >> word)//powtarzaj dopóki można pobrać słowo ze strumienia
		{

		if ( iscommand(word) )//jeśli słowo jest komendą preprocesora to
		{
			if ( word == "#define" )//jeśli jest to #define
			{

				std::string k;
				std::string v;
			
				if( !(line >> k) )//pobierz pierwszy argument
					throw BadInput();//a jeśli go nie było to krzycz
				
				if(line >> v)//pobierz drugi argument
				{
					if( !defines.exists(k) )//jeśli jeszcze nie było takiego elementu
					{
						defines.add(k,v);//to zdefiniuj
					}
					//w przeciwnym przypadku nic nie rób
				}
				else//a jak go nie ma
				{
					defines.add(k," ");//to dodaj z domyślną wartością
				}
					
			}//if ( word == "#define" )

			if (word == "#include")//jeśli jest to #include
			{
			
				std::string incl;

				if ( line >> incl )//pobierz argument
				{

					if ( incl[0] == '<' )//jak jest to jakiś nagłówek systemowy
					{
						output << incl;//to go olej
					}

					if ( incl[0] == '"' && incl[ incl.size()-1 ] == '"' )//jak nie trzeba szukać tego nagłówka to
					{
						output.close();//zamknij wyjście (kolejna instancja preprocesora będzie pisać do tego samego pliku)
						incl.pop_back();
						std::string temp = incl.substr(1);//wypreparuj nazwę pliku
						preprocess ( temp , outputName , defines, inputFileNames );//uruchom preprocesor dla następnego pliku
						output.open(outputName,std::ofstream::app);//przywróć wyjście
					}

					if (incl[0] != '<' && incl[0] != '"')//jeśli argument jest bez sensu
					{
						throw BadInput();//to krzycz
					}
				}
				else//jak argumentu nie ma
				{
					throw BadInput();//to krzycz
				}

			}//if (word == "#include")

		
		}
		else//jak nie jest komendą
		{
			
			if( defines.exists(word) )//jak zostało zdefiniowane
			{
				output << defines.get(word) << ' ';//to zastąp przezwartość tego czegoś
			}
			else//w przeciwnym przypadku
			{
				output << word << ' ';//przepisz
			}
			}
		}
		output << std::endl;//a jak się skończą słowa w strumieniu to postaw koniez linii
	
	}
	//defines.show();
}
	



bool iscommand(std::string w)
{
	return w[0]=='#'?true:false;
}

const char* BadInput::what()const noexcept
{
	return "Bad input exception";
}
