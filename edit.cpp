#include "edit.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Timer.hpp"
#include "Editor.hpp"
#include "TextBoxStream.hpp"
#include "OpenFileError.hpp"
#include <fstream>


namespace edit
{
	
	std::string toString(Action::item aItem)
	{
		switch(aItem)
		{
			case Action::character:
				return std::string("character");
				break;
			case Action::text:
				return std::string("text");
				break;
			case Action::voice:
				return std::string("voice");
				break;
			case Action::music:
				return std::string("music");
				break;
			case Action::background:
				return std::string("background");
				break;
			default:
				return std::string("invalid Item");
				break;
		}

		//instruction that shall never be executed
		return std::string();
	}


	Action::Action()
	{
		nextPressed = false;
		precPressed = false;
		closeRequest = false;


		h = 0;
		v = 0;

		aItem = character;
	}




	void updateEditorArray(EditorArray &editors, std::size_t& cur, Action &action, sf::Music& voice, sf::Music& music)
	{
		if(action.nextPressed)
		{
			/* auto itPrev = it; */
			/* it++; */
			/* if(it == editors.end()) */
			/* { */
			/* 	it = editors.insert(it, *itPrev); */
			/* } */
			if(++cur == editors.size()) //adding an element at the end
			{
				editors.push_back(editors[cur-1]);
			}
		}
		if(action.precPressed)
		{
			/* if(it == editors.begin()) */
			/* { */
			/* 	it = editors.insert(it, Editor(voice, music)); */
			/* } */
			/* else */
			/* { */
			/* 	it--; */
			/* } */
			if(cur == 0) //adding an element at the beggining
			{
				editors.push_front(Editor(cur, voice, music));
			}
			else
			{
				cur--;
			}

		}

		//it->refresh();
	}


	/* void updateEditorNumbersFrom(EditorArray& editors, std::size_t cur) */
	/* { */
	/* 	for(std::size_t i = cur; i < editors.size(); i++) */
	/* 	{ */
	/* 		editors[i].setNumber(i); */
	/* 	} */
	/* } */


	void getEvents(sf::RenderWindow &window, Action &action)
	{
		//reset action
		action.nextPressed = false;
		action.precPressed = false;
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
							//action.nextPressed = true;
							break;
						case sf::Keyboard::Return:
							//action.nextPressed = true;
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
						case sf::Keyboard::Numpad5:
							action.aItem = Action::background;
							std::cout<< "background selected\n";
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

		//verify if we want to take the next or prec Editor
		action.precPressed = action.aItem != Action::text && action.textBuffer.find(L'-') != std::wstring::npos;

		action.nextPressed = action.aItem != Action::text && action.textBuffer.find(L'+') != std::wstring::npos;

		
	}





	void saveToFile(EditorArray& editors, const std::string& file)
	{
		std::locale::global(std::locale(""));
		std::wofstream fileStream(file);
		if(!fileStream.is_open())
		{
			throw OpenFileError();
		}
		fileStream.imbue(std::locale(""));

		fileStream<< L"\n";
		
		//write each Editor
		for(auto it = editors.begin(); it != editors.end(); it++)
		{
			it->saveToStream(fileStream);
		}
	}





	void edit(sf::RenderWindow &window)
	{
		sf::Time loadingDuration;
		sf::Clock loadingClock;
		loadingDuration = loadingClock.getElapsedTime();

		std::cout<< "Loading ...\n";

		Editor::loadStaticData();

		EditorArray editorArray;
		std::size_t curEditor = 0;

		sf::Music voice;
		sf::Music music;

		Action action;

		editorArray.push_back(Editor(curEditor, voice, music));

		TextBoxStream::loadStaticData();

		sf::Texture textBoxTexture;
		if(!textBoxTexture.loadFromFile(sf::String(L"gameData/images/text_boxes/textbox.png")))
		{
			throw OpenFileError();
		}
		sf::Sprite textBoxSprite(textBoxTexture);



		std::cout<<".. Finished !\n";
		std::cout<< (loadingClock.getElapsedTime() - loadingDuration).asSeconds()<< "\n";

		Timer loopTimer(sf::seconds(1./60.)); //60 fps

		while(!action.closeRequest)
		{
			getEvents(window, action);

			updateEditorArray(editorArray, curEditor, action, voice, music);

			editorArray[curEditor].handleAction(action);

			editorArray[curEditor].updateDisplayers();

			window.clear(sf::Color::Black);

			window.draw(editorArray[curEditor]);
			window.draw(textBoxSprite);
			window.draw(tstream);

			window.display();

			loopTimer.autoSleep();
		}

		std::wstring saveFile = selectFile(L"select a file to save in");
		if(saveFile.empty())
		{
			saveFile = L"default.scen";
		}

		saveFile = std::wstring(SCENE_DIRECTORY.begin(), SCENE_DIRECTORY.end()) + saveFile;

		std::wcout<< saveFile<< "\n";
		saveToFile(editorArray, std::string(saveFile.begin(), saveFile.end()));
	}




} //namespace edit



