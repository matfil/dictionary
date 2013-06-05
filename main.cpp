#include "compare.hpp"
#include "preprocess.h"

class Xxx: public Comparator<int>
{
	public:
	bool less (int a,int b){return a<b?true:false;}
	~Xxx(){};
};
#include "RBtree.hpp"

#include <iostream>
#include <string>

int main()
{
/**********************debug block
	RBtree<int,int,Xxx> tree;
	tree.add(1,0);
	tree.add(4,3);
	tree.add(8,7);
	tree.add(3,2);
	tree.add(9,8);
	tree.show();

	tree.get(8) = 16;

	std::cout << tree.get(8) << std::endl;
	
	try
	{
		std::cout << tree.get(10)  << std::endl;
	}
	catch(RBtree<int,int,Xxx>::NoSuchItemFound a)
	{
		std::cout << "It worked "  << a.what()<< std::endl;	
	}
	tree.show();
**********************************/
	bool failure;
	do
	{
	failure = false;
	std::string a,b;
		std::cout << "Podaj nazwę pliku wejściowego"<< std::endl;
		std::cin >> a;
		std::cout << "Podaj nazwę pliku wyjściowego"<< std::endl;	
		std::cin >> b;
	

	RBtree<std::string,std::string,Strcomp> defines;//drzewo
	std::vector<std::string> files;//pliki

	try
	{
		preprocess (a, b, defines, files);
	}
	catch(BadInput)
	{
		std::cout << "Popraw plik wejściowy i spróbuj ponownie"<< std::endl<<std::endl;
		failure = true;
	}
	}while(failure);
	return 0;
}
