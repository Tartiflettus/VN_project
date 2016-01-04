/*
* Errors that occur when a file cannot be opened.
*/
#ifndef DEF_OPENFILEERROR_HPP
#define DEF_OPENFILEERROR_HPP


#include <exception>


class OpenFileError : public std::exception
{
	public:
		OpenFileError();
		virtual ~OpenFileError() throw();

		virtual const char* what() const throw();
};



#endif
