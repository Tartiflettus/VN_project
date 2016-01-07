/*
* Error thatshall be thrown when the scenario is not well formated.
*/
#ifndef DEF_SCENARIOSYNTAXERROR_HPP
#define DEF_SCENARIOSYNTAXERROR_HPP

#include <exception>



namespace pv
{
	
}



class ScenarioSyntaxError: public std::exception
{
	public:
		//types////////////////////////////////////
		enum errorType
		{
			missingBlockStart = 1,
			missingBlockEnd = 1<<1
		};
		//typedef pv::ScenarioErrorType errorType;

		ScenarioSyntaxError(errorType flags);
		virtual ~ScenarioSyntaxError() throw();

		virtual const char* what() const throw();
	
	private:
		errorType m_flags;
};


#endif //DEF_SCENARIOSYNTAXERROR_HPP

