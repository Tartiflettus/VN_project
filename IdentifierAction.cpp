#include "IdentifierAction.hpp"
#include "AtomicScene.hpp"
#include "FileLoader.hpp"
#include "ScenarioSyntaxError.hpp"
#include "SceneTypes.hpp"
#include "Scene.hpp"
#include <iostream>
#include <algorithm>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Music.hpp"
#include "Voice.hpp"
#include "ScenarioSelector.hpp"
#include "Background.hpp"

#include "assertsOn.hpp"
#include <cassert>


IdentifierAction::IdentifierAction()
{
}



IdentifierAction::~IdentifierAction()
{
}



#ifdef _WIN32 //stof and other funtions are not available yet on windows

#include <sstream>

namespace std
{
	unsigned long stoul(const std::wstring& string)
	{
		std::wstringstream s(string);
		unsigned long tmp;
		s>>tmp;
		return tmp;
	}
	
	float stof(const std::wstring& string)
	{
		std::wstringstream s(string);
		float tmp;
		s>>tmp;
		return tmp;
	}
}

#endif



std::vector<std::wstring> extractArgs(const std::wstring &str, std::size_t &pos, wchar_t start, wchar_t end)
{
	//assert(str.size() >= 2 && str[pos] == start);
	std::size_t posStart = pos;
	std::vector<std::wstring> args;
	std::wstring currentArg;


	//find where the args starts
	for( ; pos < str.size() && str[pos] != start; pos++)
	{
	}
	pos++;
	if(pos >= str.size()) //no starting point has been found
	{
		//throw ScenarioSyntaxError(ScenarioSyntaxError::missingBlockStart);
		pos = posStart; //place the cursor at the first position after the end : where we started
		return args;
	}

	
	//aborted when end found
	for( ; pos < str.size(); pos++)
	{
		if(str[pos] == L' ' || str[pos] == L'\n')
		{
			if(!currentArg.empty())
			{
				args.push_back(currentArg);

			}
			currentArg.clear();
		}
		else if(str[pos] == end)
		{
			pos++; //place the cursor at the first position after the end
			if(!currentArg.empty())
			{
				args.push_back(currentArg);
			}
			break;
		}
		else //if we are indeed inspecting an argument
		{
			currentArg += str[pos];
		}
	}

	return args;
}




std::wstring firstArg(const std::wstring &str,std::size_t &pos, wchar_t start, wchar_t end)
{
	std::size_t posStart;
	std::wstring ans;

	posStart = str.find(start, pos);
	if(posStart == std::wstring::npos) //not found
	{
		return std::wstring();
	}

	pos = posStart + 1;
	
	//search the first argument from its start to its end
	std::size_t posArgEnd;
	posArgEnd = str.find_first_of(std::wstring(L" \n") + wchar_t(end), pos);

	if(posArgEnd == std::wstring::npos || str[posArgEnd] == end)
	{
		return std::wstring();
	}

	ans.resize(posArgEnd - pos);
	std::copy(str.begin() + pos, str.begin() + posArgEnd, ans.begin());

	//std::cout<< posArgEnd - pos<< "\n";
	
	pos = posArgEnd;
	return ans;
}





IdentifierCharacter::IdentifierCharacter()
{
}


void IdentifierCharacter::operator()(AtomicScene &scene)
{
	std::cout<< "character found\n";
	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();
	//std::cout<< "<<\n";

	std::vector<std::wstring> args = extractArgs(block, cur, L'{', L'}');
	//std::cout<< ">>\n";

	if(args.empty()) //if no argument : that means we get the old version
	{
		scene.addCharacter(std::unique_ptr<Character>());
		scene.setCursorPos(cur);
		return;
	}

	std::shared_ptr<Character> newChar(new Character());
	
	if(args.size() >= 1 && args[0].rfind(L".png", args[0].size()) != std::wstring::npos)
	{
		sf::Texture& tex = Scene::requestCharacterTexture(args[0]);
		newChar->setTexture(tex);
	}
	if(args.size() >= 4)
	{
		if(args[1] == L"pos")
		{
			newChar->setPosition(std::stof(args[2]), std::stof(args[3]));
		}
		else if(args[1] == L"slot")
		{
			newChar->setSlot(std::stoul(args[2]), std::stoul(args[3]));
		}
	}


	scene.addCharacter(newChar);

	scene.setCursorPos(cur);
}



IdentifierMusic::IdentifierMusic()
{
}


void IdentifierMusic::operator()(AtomicScene &scene)
{
	std::cout<< "music found\n";

	std::wstring block(scene.getCurrentBlock());
	std::size_t cur = scene.getCursorPos();

	std::vector<std::wstring> args(extractArgs(block, cur));

	Music newMusic;
	if(!args.empty())
	{
		std::wstring fileStr(MUSIC_PATH + args[0]);
		newMusic = std::string(fileStr.begin(), fileStr.end());
		scene.setMusic(newMusic);
	}

	scene.setCursorPos(cur);
}



IdentifierSound::IdentifierSound()
{
}



void IdentifierSound::operator()(AtomicScene &scene)
{
	std::cout<< "sound found\n";
}


IdentifierVoice::IdentifierVoice()
{
}



void IdentifierVoice::operator()(AtomicScene &scene)
{
	std::cout<< "voice found\n";

	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();

	std::vector<std::wstring> args(extractArgs(block, cur, L'{', L'}'));
	
	Voice newVoice;
	
	if(args.size() >= 1 && args[0].rfind(L".ogg", args[0].size()) != std::wstring::npos)
	{
		std::wstring name;

		//from now on, name represents the file to load
		name = VOICE_PATH + args[0];

		newVoice = std::string(name.begin(), name.end());
		
		scene.setVoice(newVoice);
	}

	cur = block.find(L'}', cur);
	scene.setCursorPos(cur);
}




IdentifierText::IdentifierText()
{
}



void IdentifierText::operator()(AtomicScene &scene)
{
	std::cout<< "text found\n";

	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();


	std::wstring arg1 = firstArg(block, cur, L'{', L'}');
	if(arg1.empty()) //no arg found
	{
		scene.setText(Text());
	}
	else
	{
		if(arg1 == L"cl")
		{
			Text text;
			std::size_t posEnd = block.find(L'}', cur);
			text.resize(posEnd - cur);
			std::copy(block.begin()+cur, block.begin()+posEnd, text.begin());
			text.setAppend(false);
			scene.setText(text);
		}
		else if(arg1 == L"app")
		{
			Text text;
			std::size_t posEnd = block.find(L'}', cur);
			text.resize(posEnd - cur);
			std::copy(block.begin()+cur, block.begin()+posEnd, text.begin());
			text.setAppend(true);
			scene.setText(text);
		}
	}

	cur = block.find(L'}', cur) + 1;

	scene.setCursorPos(cur);
}




IdentifierButton::IdentifierButton()
{
}




void  IdentifierButton::operator()(AtomicScene &scene)
{
	std::cout<< "button found\n";

	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();


	std::wstring arg1 = firstArg(block, cur);
	if(!arg1.empty()) //Contains an expression that transforms variables
	{
		std::wstring msg;
		std::size_t posEnd = block.find(L'}', cur);
		msg.resize(posEnd - cur);
		std::copy(block.begin()+cur, block.begin()+posEnd, msg.begin());

		scene.addButton(Button(msg, arg1));
	}


	cur = block.find(L'}', cur) + 1;

	scene.setCursorPos(cur);
}





IdentifierSelector::IdentifierSelector()
{
}



void IdentifierSelector::operator()(AtomicScene& scene)
{
	std::cout<< "selector found\n";

	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();


	std::vector<std::wstring> args(extractArgs(block, cur, L'{', L'}'));
	if(args.size() >= 2)
	{
		//first arg = expr
		ScenarioSelector selector;
		selector.setExpression(args[0]);
		
		//second arg = scenario file
		selector.setScenario(args[1]);

		scene.addSelector(selector);
	}


	//cur = block.find(L'}', cur) + 1;
	scene.setCursorPos(cur);
}





IdentifierBackground::IdentifierBackground()
{
}



void IdentifierBackground::operator()(AtomicScene& scene)
{
	std::cout<< "background found\n";

	std::wstring block = scene.getCurrentBlock();
	std::wstring::size_type cur = scene.getCursorPos();

	
	std::wstring arg1 = firstArg(block, cur);

	if(!arg1.empty())
	{
		BackgroundPtr background = BackgroundPtr(new Background);
		sf::Texture& tex = Scene::requestBgTexture(arg1);
		background->setTexture(tex);
		scene.setBackground(background);
	}


	cur = block.find(L'}', cur) + 1;
	scene.setCursorPos(cur);
}






