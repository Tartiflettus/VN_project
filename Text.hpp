/*
* A text is a derivate of std::string that shall be used in a text box.
*/
#ifndef DEF_TEXT_HPP
#define DEF_TEXT_HPP

#include <string>
//#include <SFML/Graphics/Drawable.hpp>
//#include <SFML/Graphics/RenderStates.hpp>
//#include <SFML/Graphics/Text.hpp>
#include <iostream>


/*namespace sf
{
	class RenderTarget;
}*/


//const std::string FONT_PATH = std::string("gameData/fonts/");


class Text//: public sf::Drawable
{
	public:
		//types////////////////////////////////////
		typedef std::wstring::iterator iterator;
		typedef std::wstring::const_iterator const_iterator;
		//typedef std::string::back_insert_iterator back_insert_iterator;
		typedef std::wstring::size_type size_type;



		Text(const std::wstring &string_ = std::wstring());

		//static sf::Font stdFont;
		//void loadStaticData();


		wchar_t& operator[](size_type pos);
		const wchar_t& operator[](size_type pos) const;

		size_type size() const;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;

		void resize(size_type n);
		Text& operator+=(const Text &text);
		Text& operator+=(const std::wstring &string);
		Text& operator+=(const char *s);
		Text& operator+=(char c);

		
		void setAppend(bool app);
		bool append() const;


	
	/*protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;*/

	private:
		std::wstring m_string;
		bool m_append;
		//sf::Text m_textSprite;
};



std::ostream& operator<<(std::ostream& stream, const Text& text);



#endif //DEF_TEXT_HPP

