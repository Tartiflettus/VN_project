#include "TextBoxStream.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "OpenFileError.hpp"
#include <iostream>
#include "constants.hpp"



TextBoxStream::TextBoxStream()
{
	m_textSprite.setFont(stdFont);
	m_textSprite.setColor(sf::Color::White);
	m_textSprite.setCharacterSize(24);
	m_textSprite.setPosition(TEXTBOX_RECT.left, TEXTBOX_RECT.top);

	m_nameSprite.setFont(stdFont);
	m_nameSprite.setColor(sf::Color::White);
	m_nameSprite.setCharacterSize(25);
	m_nameSprite.setPosition(NAME_POS);
}



sf::Font TextBoxStream::stdFont;

TextBoxStream tstream;


void TextBoxStream::loadStaticData()
{
	if(!stdFont.loadFromFile(FONT_PATH + std::string("Pacifico.ttf")))
	{
		throw OpenFileError();
	}
}




void TextBoxStream::clear()
{
	m_string.clear();
	m_textSprite.setString(m_string);
}



TextBoxStream& TextBoxStream::operator<<(const std::string& string)
{
	for(std::string::size_type i = 0; i < string.size(); i++)
	{
		(*this)<< string[i];
	}
	return *this;
}


/*TextBoxStream& TextBoxStream::operator<<(const sf::String& string)
{
	for(size_t i = 0; i < string.getSize(); i++)
	{
		(*this)<< string[i];
	}
	return *this;
}*/


TextBoxStream& TextBoxStream::operator<<(const Text& string)
{
	for(size_t i = 0; i < string.size(); i++)
	{
		(*this)<< string[i];
	}
	return *this;
}


TextBoxStream& TextBoxStream::operator<<(const std::wstring& string)
{
	for(size_t i = 0; i < string.size(); i++)
	{
		(*this)<< string[i];
	}
	return *this;
}


TextBoxStream& TextBoxStream::operator<<(const sf::String& string)
{
	(*this)<< string.toWideString();
	return *this;
}



TextBoxStream& TextBoxStream::operator<<(char c)
{
	m_string += c;
	m_textSprite.setString(m_string);

	sf::FloatRect bounds(m_textSprite.getGlobalBounds());

	//verify that we are within the text box
	if(bounds.left + bounds.width > TEXTBOX_RECT.left + TEXTBOX_RECT.width)
	{
		m_string[m_string.size() - 1] = '\n';
		m_string += c;
		m_textSprite.setString(m_string);
	}

	return *this;
}


TextBoxStream& TextBoxStream::operator<<(wchar_t c)
{
	m_string += c;

	m_textSprite.setString(m_string);
	sf::FloatRect bounds(m_textSprite.getGlobalBounds());

	//verify that we are within the text box
	if(bounds.left + bounds.width > TEXTBOX_RECT.left + TEXTBOX_RECT.width)
	{
		m_string[m_string.size() - 1] = L'\n';
		m_string += c;
		m_textSprite.setString(m_string);
	}

	return *this;
}






void TextBoxStream::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//std::wcout<< m_string<< "\n";
	//m_textSprite.setString(m_string);
	target.draw(m_textSprite, states);
	target.draw(m_nameSprite);
	/*for(size_t i =0; i < m_string.size(); i++)
	{
		std::cout<< char(m_string[i]);
	}*/
	//std::cout<< "\n";
}






void TextBoxStream::setName(const std::wstring &string)
{
	m_name = string;
	m_nameSprite.setString(m_name);
}




void TextBoxStream::clearName()
{
	m_name.clear();
	m_nameSprite.setString(m_name);
}



