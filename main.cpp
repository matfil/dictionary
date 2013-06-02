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

int main()
{
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


	preprocess ("testfile","asd");
	return 0;
}
