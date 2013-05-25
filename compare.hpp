#ifndef COMPARE_HPP
#define COMPARE_HPP

template<class T>
class Comparator
{
	private:
	protected:
	public:
	virtual bool less (T,T) = 0; // a < b
//	virtual ~Comparator() = 0;
};

#endif
