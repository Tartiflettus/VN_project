/*
* Main loop of the game.
*/
#ifndef DEF_GAME_HPP
#define DEF_GAME_HPP


#include "SignalThread.hpp"


namespace sf
{
	class RenderWindow;
}


namespace game
{
	struct Action
	{
		Action();

		bool nextPressed;
		bool closeRequest;
	};

	void getEvents(sf::RenderWindow &window, Action &action);

	void game(sf::RenderWindow &window, EventQueue& eventQueue);


} //namespace game


#endif //DEF_GAME_HPP

