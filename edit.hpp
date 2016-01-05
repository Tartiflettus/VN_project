/*
* Definition of the main loop of the visual novel editor.
* It is meant to (more or less) easily make a visual novel.
*/
#ifndef DEF_EDIT_HPP
#define DEF_EDIT_HPP


#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/String.hpp>


namespace sf
{
	class RenderWindow;
}


namespace edit
{
	struct Action
	{
		enum item
		{
			character,
			text,
			voice,
			music,
			invalidItem
		};

		Action();

		item aItem;

		bool nextPressed;
		bool closeRequest;

		sf::String textBuffer;		

		int h; //left and right keys
		int v; //up and down keys

	};

	void getEvents(sf::RenderWindow &window, Action &action);

	void edit(sf::RenderWindow &window);

	std::string toString(Action::item aItem);

	//void updateAtomicScene(AtomicScene &scene, Action &action);

} //namespace edit



#endif //DEF_EDIT_HPP

