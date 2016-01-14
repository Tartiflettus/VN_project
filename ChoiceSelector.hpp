/*
* A choice selector is an interface to branch on a specific scenario.
* Which scenario is chosen depends on how the user answers a question.
* In a (not far I hope) future, a branch will depend on the previous choices.
*/
#ifndef DEF_CHOICESELECTOR_HPP
#define DEF_CHOICESELECTOR_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Button.hpp"


namespace sf
{
	class RenderTarget;
}



class ChoiceSelector: public sf::Drawable
{
	public:
		typedef std::vector<Button> ButtonArray;

		ChoiceSelector();
		
		Button& operator[](std::size_t i);
		const Button& operator[](std::size_t i) const;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		ButtonArray m_buttons;

};



#endif //DEF_CHOICESELECTOR_HPP

