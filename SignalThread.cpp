#include "SignalThread.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>



std::mutex SignalMutex;




void signalLoop(sf::RenderWindow& window, EventQueue& queue)
{
	sf::Event event;

	while(true)
	{
		window.waitEvent(event);
			
		SignalMutex.lock();

		queue.push(event); //there might be a deadlock if this function throws exceptions

		SignalMutex.unlock();
	}
}


