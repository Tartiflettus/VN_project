/*
* A scenario selector allow the scenario to divide into multiple branches.
* Which scenario is chosen depends on how the user answered questions.
*/
#ifndef DEF_SCENARIOSELECTOR_HPP
#define DEF_SCENARIOSELECTOR_HPP

#include <string>
#include <vector>


class ScenarioSelector
{
	public:
		ScenarioSelector();

		void setExpression(const std::wstring& expr);
		std::wstring getExpression() const;

		void setScenario(const std::wstring& scenario);
		std::wstring getScenario() const;
		
	private:
		std::wstring m_expression;
		std::wstring m_scenario;
};



typedef std::vector<ScenarioSelector> SelectorArray;



#endif //DEF_SCENARIOSELECTOR_HPP

