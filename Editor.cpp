#include "Editor.hpp"
#include "edit.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "TextBoxStream.hpp"
#include "Scene.hpp"

#include <iostream>


namespace edit
{
	sf::Font Editor::stdFont;

	Editor::Editor()
	{
		m_curCharacter = 0;
		m_characters.push_back(CharacterInfo(L"", Character()));
		m_characters[0].second.setSlot(1, 1);

		m_displayer.setFont(stdFont);
		m_displayer.setColor(sf::Color::White);
		m_displayer.setString("mode: \nvoice: \nmusic: ");

		m_currentItem = Action::invalidItem;

		m_characterVertex.resize(5);
		m_characterVertex.setPrimitiveType(sf::LinesStrip);
		for(std::size_t i = 0; i < m_characterVertex.getVertexCount(); i++)
		{
			m_characterVertex[i].color = sf::Color::Red;
		}

		updateCharacterVertex();
	}



	void Editor::loadStaticData()
	{
		if(!stdFont.loadFromFile(FONT_PATH + std::string("CANON.ttf")))
		{
			std::cerr<< "Unable to load CANON.ttf\n";
		}
	}


	void Editor::handleAction(Action &action)
	{
		m_currentItem = action.aItem;
		switch(action.aItem)
		{
			case Action::character:
				handleCharacter(action);
				break;
			case Action::text:
				handleText(action);
				break;
			case Action::voice:
				handleVoice(action);
				break;
			case Action::music:
				handleMusic(action);
				break;
			default:
				break;
		}


	}



	void Editor::handleCharacter(Action &action)
	{
		//select the Character / slot we want
		bool slotsNeedsUpdates = false;
		while(action.h > 0)
		{
			m_curCharacter++;
			if(m_curCharacter >= m_characters.size())
			{
				m_characters.push_back(CharacterInfo(L"", Character()));
				slotsNeedsUpdates = true;
			}
			action.h--;
		}
		while(action.h < 0)
		{
			if(m_curCharacter == 0)
			{
				if(!m_characters.empty())
				{
					m_characters.pop_back();
					slotsNeedsUpdates = true;
				}
				else
				{
					m_curCharacter--;
				}
			}
			else
			{
				m_curCharacter--;
			}
			
			action.h++;
		}
		if(slotsNeedsUpdates)
		{
			for(size_t i = 0; i < m_characters.size(); i++)
			{
				m_characters[i].second.setSlot(i+1, m_characters.size());
			}
		}

		if(action.v > 0)
		{	
			//aliases to simplify the reading
			std::wstring &curFile(m_characters[m_curCharacter].first);
			Character &curCharacter(m_characters[m_curCharacter].second);


			curFile = selectFile(L"Select a character file");
			curFile = CHARACTER_PATH + m_characters[m_curCharacter].first;

			curCharacter.setTexture(Scene::requestCharacterTexture(curFile));
			/*std::string file(curFile.begin(), curFile.end());

			//load the texture only if needed
			texMap::iterator it;
			it = Scene::charactersTextures.find(curFile);
			if(it != Scene::charactersTextures.end())
			{
				curCharacter.setTexture(it->second);
			}
			else
			{
				//load the texture if not already done
				sf::Texture tex;
				tex.loadFromFile(file);
				Scene::charactersTextures[curFile] = tex;
				curCharacter.setTexture(Scene::charactersTextures[curFile]);
			}*/
		}
	}

	void Editor::handleText(Action &action)
	{
		if(!action.textBuffer.isEmpty())
		{
			//std::cout<< "unsigned int : "<< static_cast<unsigned int>(action.textBuffer[0])<< "\n";


			for(std::size_t i = 0; i < action.textBuffer.getSize(); i++)
			{
				wchar_t c = action.textBuffer[i];
				switch(c)
				{
					case 8: //delete
					{
						if(!m_text.empty())
						{
							m_text.pop_back();
						}
						break;
					}
					case 27: //echap
						break;
					case 13: //enter
						m_text += L'\n';
						break;
					default:
						m_text += action.textBuffer[i];
						break;

				}
			}

			//std::locale::global(std::locale(""));
			//std::wcout.imbue(std::locale(""));
			//std::wcout<< action.textBuffer.toWideString()<< "\n";
		}
	}

	void Editor::handleVoice(Action &action)
	{
		if(action.v > 0)
		{
			m_voiceFile = selectFile(L"Select a voice file");
			m_voiceFile = VOICE_PATH + m_voiceFile;
			std::string file(m_voiceFile.begin(), m_voiceFile.end());
			m_voice.stop();
			m_voice.openFromFile(file);
			m_voice.play();
		}
		else if(action.v < 0)
		{
			m_voice.stop();
			m_voiceFile.clear();
		}
	}

	void Editor::handleMusic(Action &action)
	{
		if(action.v > 0)
		{
			m_musicFile = selectFile(L"Select a music file");
			m_musicFile = MUSIC_PATH + m_musicFile;
			std::string file(m_musicFile.begin(), m_musicFile.end());
			m_music.stop();
			m_music.openFromFile(file);
			m_music.play();
			m_music.setLoop(true);
		}
		else if(action.v < 0)
		{
			m_music.stop();
			m_musicFile.clear();
		}
	}




	void Editor::updateDisplayers()
	{
		updateCharacterVertex();

		sf::String displayerString;
		displayerString += "mode: ";
		displayerString += toString(m_currentItem);
		displayerString += "\n";
		displayerString += "voice: ";
		displayerString += m_voiceFile;
		displayerString += "\n";
		displayerString += "music: ";
		displayerString += m_musicFile;

		m_displayer.setString(displayerString);
	}


	void Editor::updateCharacterVertex()
	{
		//verify that we are correctly selecting a character
		if(m_characters.size() - m_curCharacter > m_characters.size())
		{
			return;
		}
		

		sf::FloatRect bounds;
		bounds = m_characters[m_curCharacter].second.getGlobalBounds();

		//If there is no sprite : draw a vertical line to indicate what slot is currently selected
		if(bounds.width <= 1.)
		{
			m_characterVertex[0].position.x = m_characters[m_curCharacter].second.getPosition().x;
			m_characterVertex[0].position.y = 0.;
			
			m_characterVertex[1].position.x = m_characterVertex[0].position.x;
			m_characterVertex[1].position.y = WINDOW_SIZE.y;

			for(std::size_t i = 2; i < m_characterVertex.getVertexCount(); i++)
			{
				m_characterVertex[i].position = m_characterVertex[1].position;
			}

			return;
		}

		m_characterVertex[0].position.x = bounds.left;
		m_characterVertex[0].position.y = bounds.top;

		m_characterVertex[1].position.x = bounds.left + bounds.width;
		m_characterVertex[1].position.y = bounds.top;

		m_characterVertex[2].position.x = bounds.left + bounds.width;
		m_characterVertex[2].position.y = bounds.top + bounds.height;

		m_characterVertex[3].position.x = bounds.left;
		m_characterVertex[3].position.y = bounds.top + bounds.height;

		m_characterVertex[4] = m_characterVertex[0];
	}





	void Editor::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for(size_t i = 0; i < m_characters.size(); i++)
		{
			target.draw(m_characters[i].second, states);
		}
		tstream.clear();
		tstream<< m_text;


		target.draw(m_displayer);
		target.draw(m_characterVertex);

		//std::cout<< m_curCharacter<< " : "<< m_characters.size()<<"\n";
	}


} //namespace edit


