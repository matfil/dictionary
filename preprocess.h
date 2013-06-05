#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <string>
#include <vector>
#include <exception>
#include "RBtree.hpp"
#include "compare.hpp"



class BadInput: public std::exception
{
	private:
	protected:
	public:
	BadInput() {}
	const char* what()const noexcept;
};

void preprocess (std::string, std::string, RBtree<std::string, std::string, Strcomp>&, std::vector<std::string>&) throw (BadInput);
bool iscommand(std::string);

#endif
