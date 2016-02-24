#include "FileLoader.hpp"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TextBoxStream.hpp"
#include <string>
#include <SFML/Window/Event.hpp>


std::wstring getBlock(std::wifstream &scenario, wchar_t start, wchar_t end)
{
	std::wstring currentBlock;
	bool found = false;
	wchar_t c;
	//find the first block
	do
	{
		c = scenario.get();
		if(c == start)
		{
			found = true;
		}
	} while(!scenario.eof() && !found);
	if(scenario.eof())
	{
		return std::wstring();
	}

	currentBlock += start;
	found = false;
	//get all the block
	do
	{
		c = scenario.get();
		currentBlock += c;
		if(c == end)
		{
			found = true;
		}
	} while(!scenario.eof() && !found);

	return currentBlock;

}





std::wstring getBlock(const std::wstring &scenario, std::size_t &pos, wchar_t start, wchar_t end)
{
	std::size_t posStart;
	posStart = scenario.find(start, pos);

	//no start found
	if(posStart == std::wstring::npos)
	{
		return std::wstring();
	}

	std::size_t posEnd;
	posEnd = scenario.find(end, posStart);

	//no end found
	if(posEnd == std::wstring::npos)
	{
		return std::wstring();
	}

	std::wstring ans;
	ans = scenario.substr(posStart, posEnd - posStart + 1);
	pos = posEnd + 1;

	return ans;
}







std::wstring::size_type findPrefix(const std::wstring &str, const std::wstring &prefix, std::wstring::size_type pos)
{
	unsigned int i = 0;
	bool match = true;
	while(i + pos < str.size() && i < prefix.size() && match)
	{
		match = str[i + pos] == prefix[i];

		i++;
	}

	//Match only if all characters were the same and all prefix has been tested
	if(i == prefix.size() && match)
	{
		return pos + i;
	}
	return std::wstring::npos;
}





/*std::wstring getPrefix(const std::wstring &str)
{
	std::wstring prefix;
	bool endFound = false;
	for(int i = 0; i < str.size() && !endFound; i++)
	{
		if(str[i] == ' ' || str[i] == '\n')
		{
			endFound = true;
		}
		else
		{
			prefix += str[i];
		}
	}
}*/





std::wstring cutPath(const std::wstring &str)
{
	size_t posStart = str.rfind(L'/');
	if(posStart == std::wstring::npos)
	{
		return str;
	}
	return str.substr(posStart + 1, str.size());
}


std::string cutPath(const std::string &str)
{
	size_t posStart = str.rfind('/');
	if(posStart == std::wstring::npos)
	{
		return str;
	}
	return str.substr(posStart + 1, str.size());
}





std::wstring selectFile(const std::wstring& message)
{
	/*std::wcout<< message<< "\n? ";

	std::wstring ans;
	std::wcin>> ans;
	return ans;*/

	std::wstring currentString;
	std::wstring textBuffer;
	TextBoxStream curStream(sf::FloatRect(0, 0, 400, 100));

	sf::RenderWindow window(sf::VideoMode(400, 100), message);
	sf::Event event;

	while(true)
	{
		textBuffer.clear();
		curStream.clear();
		if(window.waitEvent(event))
		{
			if(event.type == sf::Event::Closed ||(
						event.type == sf::Event::KeyPressed &&
						(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Return)))
			{
				return currentString;
			}
			else if(event.type == sf::Event::TextEntered)
			{
				textBuffer += event.text.unicode;
			}
		}


		for(std::size_t i = 0; i < textBuffer.size(); i++)
		{
			wchar_t c = textBuffer[i];
			switch(c)
			{
				case 8: //delete
					{
						if(!currentString.empty())
						{
							currentString.pop_back();
						}
						break;
					}
				case 27: //echap
					break;
				case 13: //enter
					currentString += L'\n';
					break;
				default:
					currentString += textBuffer[i];
					break;

			}
		}

		window.clear(sf::Color::Black);

		curStream<< currentString;
		window.draw(curStream);
		
		window.display();
	}
}




