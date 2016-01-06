#include "Button.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "constants.hpp"
#include "OpenFileError.hpp"


Button::Button(const std::wstring& msg)
{
	initText();


}


sf::Font Button::stdFont;


void Button::loadStaticData()
{
	if(!stdFont.loadFromFile(FONT_PATH + std::string("Pacifico.ttf")))
	{
		throw OpenFileError();
	}
}



void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_sprite, states);
	target.draw(m_text, states);
}





void Button::initText()
{
	m_text.setFont(stdFont);
}



