/*
* A choice selector is an interface to branch on a specific scenario.
* Which scenario is chosen depends on how the user answers a question.
* In a (not far I hope) future, a branch will depend on the previous choices.
*/
#ifndef DEF_CHOICESELECTOR_HPP
#define DEF_CHOICESELECTOR_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>



namespace sf
{
	class RenderTarget;
}



class ChoiceSelector: public sf::Drawable
{
	public:
		ChoiceSelector();

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

};



#endif //DEF_CHOICESELECTOR_HPP

