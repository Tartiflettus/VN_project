#include "ScenarioSyntaxError.hpp"



ScenarioSyntaxError::ScenarioSyntaxError(errorType flags)
{
	m_flags = flags;
}



ScenarioSyntaxError::~ScenarioSyntaxError() throw()
{
}




const char* ScenarioSyntaxError::what() const throw()
{
	if(m_flags & missingBlockStart)
		return "Missing block start\n";
	if(m_flags & missingBlockEnd)
		return "Missing block end\n";

	return "Scenario syntax error\n";
}




