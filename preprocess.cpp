#include "preprocess.h"
#include "compare.hpp"
#include "RBtree.hpp"

#include <string>
#include <sstream>
#include <fstream>

class Strcomp:public Comparator<std::string>
{
	public:
	Strcomp(){}
	bool less(std::string a,std::string b){return a<b?true:false;}
	~Strcomp() {}
};

void preprocess (std::string&& filename, std::string&& outputName) throw (BadInput)
{
	std::ifstream input;
	std::ofstream output;

	std::string word;

	//otwieranie plików do czytania i pisania
	input.open(filename,std::ifstream::in);
	output.open(outputName,std::ofstream::out);
	//---------------------------------------

	RBtree<std::string,std::string,Strcomp> defines;		
	
	std::string l;
	while(std::getline(input,l))
	{
		std::stringstream line;
		line << l;
		while(line >> word)
		{

		if ( iscommand(word) )
		{
			if ( word == "#define" )
			{

			std::string k;
			std::string v;
			
			if( !(line >> k) )
				throw BadInput();
			
			if(line >> v)
			{
				if( !defines.exists(k) )
				{
					defines.add(k,v);
				}
			}

			else
			{
				defines.add(k," ");
			}
				
			}//if ( word == "#define" )
		
		}
		else
		{
			
			if( defines.exists(word) )
			{
				output << defines.get(word) << ' ';
			}
			else
			{
				output << word << ' ';
			}
			}
		}
		output << std::endl;
	}
	defines.show();
}
	



bool iscommand(std::string w)
{
	return w[0]=='#'?true:false;
}

const char* BadInput::what()const noexcept
{
	return "Bad input exception";
}
