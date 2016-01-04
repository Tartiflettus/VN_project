/*
* A text box stream is an interface that allows the developper to easily write in the text box.
*/
#ifndef DEF_TEXTBOXSTREAM_HPP
#define DEF_TEXTBOXSTREAM_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include "Text.hpp"
#include "constants.hpp"


namespace sf
{
	class RenderTarget;
}



const std::string FONT_PATH = std::string("gameData/fonts/");


class TextBoxStream: public sf::Drawable
{
	public:
		TextBoxStream();

		static sf::Font stdFont;
		static void loadStaticData();

		TextBoxStream& operator<<(const std::string& string);
		//TextBoxStream& operator<<(const sf::String& string);
		TextBoxStream& operator<<(const Text& string);
		TextBoxStream& operator<<(const std::wstring& string);
		TextBoxStream& operator<<(const sf::String& string);
		TextBoxStream& operator<<(char c);
		TextBoxStream& operator<<(wchar_t c);

		void clear();

		void setName(const std::wstring &string);
		void clearName();

	
	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;



	private:
		sf::Text m_textSprite;
		std::wstring m_string;
		
		std::wstring m_name;
		sf::Text m_nameSprite;
};




extern TextBoxStream tstream;




#endif //DEF_TEXTBOXSTREAM_HPP

