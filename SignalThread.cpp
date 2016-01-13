#include "SignalThread.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "constants.hpp"
#include <iostream>


std::mutex SignalMutex;




void signalLoop(sf::RenderWindow** p_window, EventQueue** p_queue)
{
	try
	{
		SignalMutex.lock();

		*p_window = nullptr;
		*p_queue = nullptr;

		*p_window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Visual Novel");
		*p_queue = new EventQueue;

		sf::RenderWindow& window = **p_window;
		EventQueue& queue = **p_queue;

		SignalMutex.unlock();

		std::cout<< "\n\nqueue construite\n\n";


		sf::Event event;
		bool finished = false;

		while(!finished)
		{
			window.waitEvent(event);

			SignalMutex.lock();

			queue.push(event); //there might be a deadlock if this function throws exceptions

			finished = !window.isOpen();

			SignalMutex.unlock();
		}

		std::cout<< "\n\ndelete reached\n\n";
		delete *p_window;
		delete *p_queue;
	}
	catch(std::exception& except)
	{
		std::cerr<< except.what();
		delete *p_window;
		delete *p_queue;
	}
}


