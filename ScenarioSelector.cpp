#include "ScenarioSelector.hpp"
#include <SFML/Graphics/RenderTarget.hpp>



ScenarioSelector::ScenarioSelector()
{
}




void ScenarioSelector::setExpression(const std::wstring& expr)
{
	m_expression = expr;
}

std::wstring ScenarioSelector::getExpression() const
{
	return m_expression;
}

void ScenarioSelector::setScenario(const std::wstring& scenario)
{
	m_scenario = scenario;
}

std::wstring ScenarioSelector::getScenario() const
{
	return m_scenario;
}





