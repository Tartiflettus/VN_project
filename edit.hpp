/*
* Definition of the main loop of the visual novel editor.
* It is meant to (more or less) easily make a visual novel.
*/
#ifndef DEF_EDIT_HPP
#define DEF_EDIT_HPP


#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/String.hpp>
#include "editTypes.hpp"
#include <list>
#include "Editor.hpp"
#include <deque>
#include "SignalThread.hpp"


namespace sf
{
	class RenderWindow;
}


namespace edit
{
	typedef std::deque<Editor> EditorArray;


	void getEvents(sf::RenderWindow &window, Action &action, EventQueue& eventQueue);

	void edit(sf::RenderWindow &window, EventQueue& eventQueue);

	std::string toString(Action::item aItem);

	void updateEditorArray(EditorArray &editors, std::size_t& cur, Action &action, sf::Music& voice, sf::Music& music);
	/* void updateEditorNumbersFrom(EditorArray& editors, std::size_t cur); */

	void saveToFile(EditorArray& editors, const std::string& file);

	//void updateAtomicScene(AtomicScene &scene, Action &action);

} //namespace edit



#endif //DEF_EDIT_HPP

