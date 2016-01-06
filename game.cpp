#include "game.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <fstream>
#include <locale>
#include "FileLoader.hpp"
#include "OpenFileError.hpp"
#include "AtomicScene.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

#include "Button.hpp"


namespace game
{
	Action::Action()
	{
		nextPressed = false;
		closeRequest = false;
	}

	void getEvents(sf::RenderWindow &window, Action &action)
	{
		//reset action
		action.nextPressed = false;
		action.closeRequest = false;

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
						default:
							break;
					}
					break;
				case sf::Event::KeyReleased:
					break;
				/* case sf::Event::MouseButtonPressed: */
				/* 	switch(event.mouseButton.button) */
				/* 	{ */
				/* 		case sf::Mouse::Left: */
							
				/* 			break; */
				/* 	} */
				/* 	break; */
				default:
					break;
			}
		}
	}


	void game(sf::RenderWindow &window)
	{
		sf::Time loadingDuration;
		sf::Clock loadingClock;
		loadingDuration = loadingClock.getElapsedTime();

		std::cout<< "Loading ...\n";

		AtomicScene::loadStaticData();
		Action action;

		std::locale::global(std::locale(""));
		std::cout<< "Locale actuelle : "<< std::locale("").name().c_str()<< "\n";

		std::wifstream mainScenario;
		mainScenario.imbue(std::locale(""));
		mainScenario.open(SCENE_DIRECTORY + std::string("main.scen"));
		if(!mainScenario.is_open())
		{
			throw OpenFileError();
		}

		//std::wstring scenarioString = 
		//L"[character {Batler.png slot 1 1} text {cl blabla bla}] [text {cl Vide intersidéral!! On fait exprès ici une ligne bien trop longue pour la text box afin de tester si elle gère bien les retours à la ligne.aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}][character {Batler.png slot 1 2}character {Yamada.png slot 2 2}text {cl Ceci est un texte de test.}][text {cl Vide intersidéral!! On fait exprès ici une ligne bien trop longue pour la text box afin de tester si elle gère bien les retours à la ligne.aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}][character{Batler.png slot 2 2}text {app Ceci en est la suite.}][character {}text {cl Salutations, utilisateur !!} ][]";


		TextBoxStream::loadStaticData();

		Scene mainScene;
		mainScene.loadFromStream(mainScenario);
		//mainScene.loadFromString(scenarioString);

		sf::Texture textBoxTexture;
		if(!textBoxTexture.loadFromFile(sf::String(L"gameData/images/text_boxes/textbox.png")))
		{
			throw OpenFileError();
		}
		sf::Sprite textBoxSprite(textBoxTexture);


		std::cout<< "... Finished !\n";

		std::cout<< (loadingClock.getElapsedTime() - loadingDuration).asSeconds()<< "\n";

		
		//std::locale::global(std::locale(""));
		std::cout<< "Locale actuelle : "<< std::locale("").name().c_str()<< "\n";

		/*std::string testFile("test");
		std::wofstream testOf;
		testOf.imbue(std::locale(""));
		testOf.open(testFile);

		for(std::size_t i = 0; i < scenarioString.size(); i++)
		{
			testOf<< scenarioString[i];
		}
		testOf.close();
		
		std::wifstream testIf;
		testIf.imbue(std::locale(""));
		testIf.open(testFile);

		std::wstring testString;
		do
		{
			std::wstring currentString;
			testIf>> currentString;
			if(testIf.eof())
			{
				break;
			}
			testString += currentString;
		} while(!testIf.eof());
		testIf.close();

		std::wcout.imbue(std::locale(""));
		std::wcout<< testString<< "\n";*/

		

		//std::cout<< "Un wchar_t fait : "<< sizeof(wchar_t)<< "\n";
		//std::cout<< "Un int fait : "<< sizeof(std::int32_t)<< "\n";


		Timer loopTimer(sf::seconds(1./60.)); //60 fps

		Button::loadStaticData();
		Button button(L"Ceci est un bouton ! è_é");

		
		//main loop
		while(!action.closeRequest)
		{
			getEvents(window, action);
			
			
			if(mainScene.empty())
			{
				break;
			}
			if(action.nextPressed)
			{
				mainScene.loadNextAtomicScene();
			}

			window.clear(sf::Color::Black);

			window.draw(mainScene);
			window.draw(textBoxSprite);
			window.draw(tstream);
			window.draw(button);
			
			window.display();

			loopTimer.autoSleep();
		}
	}






} //namespace game

