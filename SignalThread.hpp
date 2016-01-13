/*
* A thread wich handles the events to directly make actions when detected (slots)
*/
#ifndef DEF_SIGNAL_THREAD_HPP
#define DEF_SIGNAL_THREAD_HPP

#include "SignalThreadTypes.hpp"
#include <mutex>


namespace sf
{
	class RenderWindow;
}


extern std::mutex SignalMutex;


void signalLoop(sf::RenderWindow** p_window, EventQueue** p_queue);




#endif //DEF_SIGNAL_THREAD_HPP

