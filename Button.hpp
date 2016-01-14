/*
* A button is ... do I really need to explain this?
*/
#ifndef DEF_BUTTON_HPP
#define DEF_BUTTON_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


namespace sf
{
	class RenderTarget;
}



class Button: public sf::Drawable, public sf::Transformable
{
	public:
		Button(const std::wstring& msg = std::wstring());
		
		sf::FloatRect getGlobalBounds() const;

		static void loadStaticData();

		static sf::Font stdFont;
		

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void initText();
		void updateDisplay();

		sf::RectangleShape m_sprite;
		sf::Text m_text;
};


bool collision(const sf::Vector2f& point, const Button& b);




#endif //DEF_BUTTON_HPP

