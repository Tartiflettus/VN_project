#include "AtomicScene.hpp"
#include "Scene.hpp"
#include <iostream>
#include "FileLoader.hpp"
#include <SFML/Graphics/Sprite.hpp>

#include "assertsOn.hpp"
#include <cassert>



void AtomicScene::loadStaticData()
{
	m_identifierArray[std::wstring(L"character")] = std::unique_ptr<IdentifierAction>(new IdentifierCharacter);
	m_identifierArray[std::wstring(L"music")] = std::unique_ptr<IdentifierAction>(new IdentifierMusic);
	m_identifierArray[std::wstring(L"voice")] = std::unique_ptr<IdentifierAction>(new IdentifierVoice);
;
	m_identifierArray[std::wstring(L"sound")] = std::unique_ptr<IdentifierAction>(new IdentifierSound);
	m_identifierArray[std::wstring(L"text")] = std::unique_ptr<IdentifierAction>(new IdentifierText);
	m_identifierArray[std::wstring(L"button")] = std::unique_ptr<IdentifierAction>(new IdentifierButton);
	m_identifierArray[std::wstring(L"selector")] = std::unique_ptr<IdentifierAction>(new IdentifierSelector);
	m_identifierArray[std::wstring(L"background")] = std::unique_ptr<IdentifierAction>(new IdentifierBackground);
}


std::map<std::wstring, std::unique_ptr<IdentifierAction> > 
	AtomicScene::m_identifierArray;




VarMap varMap;




AtomicScene::AtomicScene(const std::wstring &filePiece)
{
	//Verify that the given string is right formated
	//assert(filePiece.size() >= 2 && filePiece[0] == '[' && filePiece[filePiece.size() - 1] == ']');
	if(filePiece.size() < 2 || filePiece[0] != '[' || filePiece[filePiece.size() - 1] != ']')
	{
		return;
	}



	m_currentBlock = filePiece;

	std::wstring::size_type cur = 0; //current
	m_cursorPos = 0;
	std::wstring::size_type next = 0;

	//Prepare all the atomic scene elements
	while(m_cursorPos < filePiece.size())
	{
		//Each element handled shall be an identifier. We just need to test each possible identifier
		next = actIf(m_identifierArray, filePiece, m_cursorPos);	

		//prepare next
		//m_cursorPos = (next == std::wstring::npos ? cur + 1 : next);
		if(next == std::wstring::npos)
		{
			m_cursorPos = filePiece.find_first_not_of(L" \n[]", m_cursorPos);
		}
		else //if a match was found
		{
			m_cursorPos = next;
		}
		//std::cout<< m_cursorPos<< "\n";
	}

	//std::cout<< findPrefix(filePiece, m_identifierArray[0], 4)<< "\n";
	//std::cout<< filePiece.size()<< "\n";
}




std::wstring AtomicScene::getCurrentBlock() const
{
	return m_currentBlock;
}




std::wstring::size_type AtomicScene::getCursorPos() const
{
	return m_cursorPos;
}


void AtomicScene::setCursorPos(std::wstring::size_type pos)
{
	m_cursorPos = pos;
}



void AtomicScene::addCharacter(const std::shared_ptr<Character> &character)
{
	m_characters.push_back(character);
}



CharactersPtrList AtomicScene::getCharacters() const
{
	return m_characters;
}




void AtomicScene::setText(const Text &text)
{
	m_text = text;
	//std::cout<< "plop\n";
}



Text AtomicScene::getText() const
{
	//Text tmp(m_text);
	//std::cout<< "plop\n";
	return m_text;
}



/*void AtomicScene::setName(const std::wstring &string)
{
	m_name = string;
}*/


std::wstring AtomicScene::getName() const
{
	std::wstring name(m_voice.begin(), m_voice.end());
	size_t posEnd = name.find(L'_');
	name = name.substr(0, posEnd == std::wstring::npos ? 0 : posEnd);
	return cutPath(name);
}


void AtomicScene::setVoice(const Voice &voice)
{
	m_voice = voice;
}


Voice AtomicScene::getVoice() const
{
	return m_voice;
}





void AtomicScene::setMusic(const Music &music)
{
	m_music = music;
}


Music AtomicScene::getMusic() const
{
	return m_music;
}




void AtomicScene::addButton(const Button& button)
{
	m_buttons.push_back(button);
}

ButtonArray AtomicScene::getButtons() const
{
	return m_buttons;
}




void AtomicScene::addSelector(const ScenarioSelector& selector)
{
	m_selectors.push_back(selector);
}

SelectorArray AtomicScene::getSelectors() const
{
	return m_selectors;
}




void AtomicScene::setBackground(const Background& bg)
{
	m_bg = bg;
}

Background AtomicScene::getBackground() const
{
	return m_bg;
}





std::wstring::size_type AtomicScene::actIf(AtomicScene::IdAction &identifiers, const std::wstring &filePiece, std::wstring::size_type pos)
{
	std::wstring::size_type cur; //current
	m_cursorPos = pos;
	
	for(IdActionIterator it = m_identifierArray.begin(); it != m_identifierArray.end(); it++)
	{
		cur = findPrefix(filePiece, it->first, m_cursorPos);
		if(cur != std::wstring::npos) //match found
		{
			m_cursorPos = cur;
			(*(it->second))(*this); //use the fonctor
			cur = m_cursorPos;
			break;
		}
	}


	return cur;
}

		
		



