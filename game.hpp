/*
* Main loop of the game.
*/
#ifndef DEF_GAME_HPP
#define DEF_GAME_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>


namespace sf
{
	class RenderWindow;
}


namespace game
{
	struct Action
	{
		typedef std::vector<sf::Vector2f> ClickArray;

		Action();

		ClickArray clicks;

		bool nextPressed;
		bool closeRequest;
	};

	void getEvents(sf::RenderWindow &window, Action &action);

	void game(sf::RenderWindow &window);


} //namespace game


#endif //DEF_GAME_HPP

