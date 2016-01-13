#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>

#include "SignalThread.hpp"
#include <thread>
#include <SFML/System/Sleep.hpp>



int main(int argc, char **argv)
{	try
	{
		sf::RenderWindow** p_window;

		std::thread signalThread(signalLoop, p_window);
		sf::sleep(sf::seconds(1));


		sf::RenderWindow& window = **p_window;



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
