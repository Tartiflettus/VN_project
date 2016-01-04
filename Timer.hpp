/*
* The timer's main purpose is verifiying if a specified amount of time has been reached.
*/
#ifndef DEF_TIMER_HPP
#define DEF_TIMER_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


class Timer
{
	public:
		Timer();
		Timer(const sf::Time &duration);

		void setDuration(const sf::Time &duration);
		sf::Time getDuration() const;

		
		bool ticked(); //exceeded the specified duration
		sf::Time getFullWaitedDuration() const;
		sf::Time getExceededDuration() const;

		void restart();

		sf::Time swapTime();

		void autoSleep();


		//global clock that will be followed by all of the timers
		static sf::Clock programClock;

		static sf::Time globalTime();


	private:
		sf::Time m_duration;

		sf::Time m_startingTimeShift; //shift from the programClock
		
		sf::Time m_oldTime; //Last time the clock ticked
};


#endif //DEF_TIMER_HPP
