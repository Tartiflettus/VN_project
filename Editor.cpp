#include "Editor.hpp"
#include "edit.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "TextBoxStream.hpp"

#include <iostream>


namespace edit
{

	Editor::Editor()
	{
		m_curCharacter = 0;
		m_characters.push_back(CharacterInfo(L"", Character()));
		m_characters[0].second.setSlot(1, 1);
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
		}
		else if(action.v < 0)
		{
			m_music.stop();
			m_musicFile.clear();
		}
	}



	void Editor::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for(size_t i = 0; i < m_characters.size(); i++)
		{
			target.draw(m_characters[i].second, states);
		}
		tstream.clear();
		tstream<< m_text;

		//std::cout<< m_curCharacter<< " : "<< m_characters.size()<<"\n";
	}


} //namespace edit


