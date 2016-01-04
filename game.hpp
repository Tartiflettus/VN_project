/*
* Main loop of the game.
*/
#ifndef DEF_GAME_HPP
#define DEF_GAME_HPP



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

	void game(sf::RenderWindow &window);


} //namespace game


#endif //DEF_GAME_HPP

