#ifndef COMPARE_HPP
#define COMPARE_HPP

#include <string>

template<class T>
class Comparator
{
	private:
	protected:
	public:
	virtual bool less (T,T) = 0; // a < b
//	virtual ~Comparator() = 0;
};

class Strcomp:public Comparator<std::string>
{
	public:
	Strcomp(){}
	bool less(std::string a,std::string b){return a<b?true:false;}
	~Strcomp() {}
};

#endif
