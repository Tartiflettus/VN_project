#include "ChoiceSelector.hpp"
#include <SFML/Graphics/RenderTarget.hpp>



ChoiceSelector::ChoiceSelector()
{
}




Button& ChoiceSelector::operator[](std::size_t i)
{
	return m_buttons[i];
}

const Button& ChoiceSelector::operator[](std::size_t i) const
{
	return m_buttons[i];
}




void ChoiceSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{
		target.draw(m_buttons[i], states);
	}
}



