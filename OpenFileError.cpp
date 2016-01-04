#include "OpenFileError.hpp"


OpenFileError::OpenFileError()
{
}


OpenFileError::~OpenFileError() throw()
{
}


const char* OpenFileError::what() const throw()
{
	return "Error : Cannot open the file\n";
}
