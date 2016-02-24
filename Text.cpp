#include "Text.hpp"
//#include <SFML/Graphics/RenderTarget.hpp>
//#include "OpenFileError.hpp"



//sf::Font Text::stdFont;





/*void Text::loadStaticData()
{
	if(!stdFont.loadFromFile(FONT_PATH + std::string("CANON.ttf")))
	{
		throw OpenFileError();
	}
}*/



Text::Text(const std::wstring &string_)
{
	m_append = false;
	//m_textSprite.setFont(stdFont);
	//m_textSprite.setCharacterSize(20);
	m_string = string_;
}




wchar_t& Text::operator[](size_type pos)
{
	return m_string[pos];
}


const wchar_t& Text::operator[](size_type pos) const
{
	return m_string[pos];
}



Text::size_type Text::size() const
{
	return m_string.size();
}



Text::iterator Text::begin() noexcept
{
	return m_string.begin();
}

Text::const_iterator Text::begin() const noexcept
{
	return m_string.begin();
}

Text::iterator Text::end() noexcept
{
	return m_string.end();
}

Text::const_iterator Text::end() const noexcept
{
	return m_string.end();
}


void Text::resize(size_type n)
{
	m_string.resize(n);
}


Text& Text::operator+=(const Text &text)
{
	m_string += text.m_string;
	return *this;
}
Text& Text::operator+=(const std::wstring &string)
{
	m_string += string;
	return *this;
}
Text& Text::operator+=(const char *s)
{
	;
	return *this;
}
Text& Text::operator+=(char c)
{
	m_string += c;
	return *this;
}




void Text::setAppend(bool app)
{
	m_append = app;
}



bool Text::append() const
{
	return m_append;
}




/*void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}*/






std::ostream& operator<<(std::ostream& stream, const Text& text)
{
	for(Text::size_type i = 0; i < text.size(); i++)
	{
		stream<< text[i];
	}
	return stream;
}





