#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>
#include "game.hpp"
#include "edit.hpp"



int main(int argc, char **argv)
{
	//sf::ContextSettings winSettings;
	//winSettings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Visual Novel");//, sf::Style::Default, winSettings);

	/* std::locale::global(std::locale("")); */
	/* std::wcout.imbue(std::locale("")); */

	try
	{
		if(argc >= 2)
		{
			if(std::string(argv[1]) == std::string("edit"))
			{
				edit::edit(window);
			}
			else
			{
				game::game(window);
			}

		}
		else
		{
			game::game(window);
		}
	}
	catch(std::exception &except)
	{
		std::cerr<< except.what();
	}

	return EXIT_SUCCESS;
}
