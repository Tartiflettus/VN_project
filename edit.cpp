#include "edit.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Timer.hpp"
#include "Editor.hpp"
#include "TextBoxStream.hpp"


namespace edit
{

	Action::Action()
	{
		nextPressed = false;
		closeRequest = false;


		h = 0;
		v = 0;

		aItem = character;
	}

	void getEvents(sf::RenderWindow &window, Action &action)
	{
		//reset action
		action.nextPressed = false;
		action.closeRequest = false;
		action.h = 0;
		action.v = 0;
		action.textBuffer.clear();

		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					action.closeRequest = true;
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code)
					{
						case sf::Keyboard::Escape:
							action.closeRequest = true;
							break;
						case sf::Keyboard::Space:
							action.nextPressed = true;
							break;
						case sf::Keyboard::Return:
							action.nextPressed = true;
							break;
						case sf::Keyboard::Left:
							action.h--;
							break;
						case sf::Keyboard::Right:
							action.h++;
							break;
						case sf::Keyboard::Up:
							action.v++;
							break;
						case sf::Keyboard::Down:
							action.v--;
							break;
						case sf::Keyboard::Numpad1:
							action.aItem = Action::character;
							std::cout<< "character selected\n";
							break;
						case sf::Keyboard::Numpad2:
							action.aItem = Action::text;
							std::cout<< "text selected\n";
							break;
						case sf::Keyboard::Numpad3:
							action.aItem = Action::voice;
							std::cout<< "voice selected\n";
							break;
						case sf::Keyboard::Numpad4:
							action.aItem = Action::music;
							std::cout<< "music selected\n";
							break;
						default:
							break;
					}
					break;
				case sf::Event::KeyReleased:
					break;
				case sf::Event::TextEntered:
					action.textBuffer += event.text.unicode;
					//std::cout<< "text entered\n";
					break;
				default:
					break;
			}
		}
	}





	void edit(sf::RenderWindow &window)
	{
		Action action;
		Editor editor;

		TextBoxStream::loadStaticData();

		Timer loopTimer(sf::seconds(1./60.)); //60 fps

		while(!action.closeRequest)
		{
			getEvents(window, action);


			switch(action.aItem)
			{
				case Action::character:
					editor.handleCharacter(action);
					break;
				case Action::text:
					editor.handleText(action);
					break;
				case Action::voice:
					editor.handleVoice(action);
					break;
				case Action::music:
					editor.handleMusic(action);
					break;
				default:
					break;
			}


			window.clear(sf::Color::Black);

			window.draw(editor);
			window.draw(tstream);

			window.display();

			loopTimer.autoSleep();
		}
	}




} //namespace edit



