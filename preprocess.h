#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <string>
#include <exception>

class BadInput: public std::exception
{
	private:
	protected:
	public:
	BadInput() {}
	const char* what()const noexcept;
};

void preprocess (std::string&&, std::string&&) throw (BadInput);
bool iscommand(std::string);

#endif
