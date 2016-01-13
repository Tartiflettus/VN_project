#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>
#include "game.hpp"
#include "edit.hpp"

#include "SignalThread.hpp"
#include <thread>
#include <SFML/System/Sleep.hpp>



int main(int argc, char **argv)
{	try
	{
		//sf::ContextSettings winSettings;
		//winSettings.antialiasingLevel = 8;
		sf::RenderWindow** p_window;
		EventQueue** p_eventQueue;

		std::thread signalThread(signalLoop, p_window, p_eventQueue);
		sf::sleep(sf::seconds(1));

		SignalMutex.lock();

		sf::RenderWindow& window = **p_window;
		EventQueue& eventQueue = **p_eventQueue;

		SignalMutex.unlock();

		if(eventQueue.empty())
		{
			std::cout<< "\n\nempty queue\n\n";
		}


		//, sf::Style::Default, winSettings);

		/* std::locale::global(std::locale("")); */
		/* std::wcout.imbue(std::locale("")); */


		if(argc >= 2)
		{
			if(std::string(argv[1]) == std::string("edit"))
			{
				edit::edit(window, eventQueue);
			}
			else
			{
				game::game(window, eventQueue);
			}

		}
		else
		{
			game::game(window, eventQueue);
		}


		SignalMutex.lock();

		window.close();

		SignalMutex.unlock();

		signalThread.join();

		return EXIT_SUCCESS;
	}
	catch(std::exception &except)
	{
		std::cerr<< except.what();
	}

}
