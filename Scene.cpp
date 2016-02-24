#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "AtomicScene.hpp"
#include "FileLoader.hpp"
#include "Background.hpp"
#include <string>

#include <iostream>

#include "assertsOn.hpp"
#include <cassert>



/*#ifdef _WIN32

#include <sstream>
namespace std
{

int stoi(std::wstring s)
{
	int ans;
	std::wstringstream ss;
	ss<< s;
	ss>> ans;
	return ans;
}	
	
}


#endif*/



Scene::Scene()
{
	m_textUpdated = false;
	m_chosen = false;
}


Scene::~Scene()
{
	m_music.stop();
	m_voice.stop();
}



/*void Scene::loadStaticData()
{
}*/


void Scene::loadFromStream(std::wifstream &stream)
{
	while(!m_atomicScenes.empty())
	{
		m_atomicScenes.pop();
	}
	std::wstring currentBlock;

	do
	{
		currentBlock = getBlock(stream, L'[', L']');
		if(currentBlock.size() == 0)
		{
			break;
		}
		m_atomicScenes.push(AtomicScene(currentBlock));
		//std::cout<< m_atomicScenes.empty()<< "\n";
	} while(!stream.eof() && currentBlock.size() > 0);

	firstUpdate();

	std::cout<< "Nombre des scenes atomiques : "<<m_atomicScenes.size()<< "\n";
}



void Scene::loadFromString(const std::wstring &string)
{
	while(!m_atomicScenes.empty())
	{
		m_atomicScenes.pop();
	}
	std::wstring currentBlock;
	std::size_t pos = 0;

	do
	{
		currentBlock = getBlock(string, pos, L'[', L']');
		if(currentBlock.size() == 0)
		{
			break;
		}
		m_atomicScenes.push(AtomicScene(currentBlock));
	} while(currentBlock.size() > 0);

	firstUpdate();

	std::cout<< "Nombre des scenes atomiques : "<<m_atomicScenes.size()<< "\n";
}





void Scene::handleClicks(const ClickArray& clicks)
{
	for(std::size_t i = 0; i < clicks.size(); i++)
	{
		for(std::size_t j = 0; j < m_buttons.size(); j++)
		{
			if(collision(clicks[i], m_buttons[j]))
			{
				std::cout<< "Click detected\n";
				interpret(m_buttons[j].getExpression());
				m_chosen = true;
				//std::cout<< varMap[L"a"]<< "\n";
			}
		}
	}
}




void Scene::handleNextPressed(bool pressed, std::wifstream& stream)
{
	assert(!(m_chosen && m_buttons.empty()));
	
	if((pressed && m_buttons.empty()) || //simply want to continue
		m_chosen) //button clicked
	{
		loadNextAtomicScene();
		if(finished()) //no next file specified
		{
			stream.close();
			stream.open(SCENE_DIRECTORY + getNextScenarioFile());
			loadFromStream(stream);
			m_nextFile.clear();
		}
	}
	m_chosen = false; //no button pressed by default
}




void Scene::interpret(const std::wstring& expr)
{
	std::size_t i;

	std::wstring var;

	//search the variable name
	for(i = 0; i < expr.size(); i++)
	{
		if(L'A' <= expr[i] && expr[i] <= L'z')
		{
			var += expr[i];
		}
		else
		{
			break;
		}
	}

	//assign its value
	if(expr[i] == L'=')
	{
		i++;
		std::wstring value;
		value = expr.substr(i);
		varMap[var] = std::stoi(value);
	}
}



bool Scene::interpretAsBool(const std::wstring& expr)
{
	std::size_t i;

	std::wstring var;

	//search the variable name
	for(i = 0; i < expr.size(); i++)
	{
		if(L'A' <= expr[i] && expr[i] <= L'z')
		{
			var += expr[i];
		}
		else
		{
			break;
		}
	}

	//search what comparison operator is being used
	if(expr.find(L"==") != std::wstring::npos)
	{
		std::size_t posValue = expr.find_first_not_of(L"=<>!", i);
		std::wstring value;
		value = expr.substr(posValue);
		if(varMap[var] == std::stoi(value))
		{
			return true;
		}
	}

	return false;
}



std::string Scene::getNextScenarioFile()
{
	return std::string(m_nextFile.begin(), m_nextFile.end());
}



bool Scene::finished() const
{
	return !m_nextFile.empty();
}



void Scene::prepareForNext()
{
	m_music.stop();
	m_voice.stop();
}




void Scene::setPrior(bool prior)
{
	m_prior = prior;	
}


bool Scene::prior()
{
	return m_prior;
}






void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	//unsigned int cpt = 0;
	for(CharactersPtrList::const_iterator it = m_characters.begin(); it != m_characters.end(); it++)
	{
		target.draw(*(*it), states);
		//cpt++;
	}
	if(!m_textUpdated)
	{
		static int i;
		i++;
		std::cout<< " : "<< i<< " : "<< "\n";
		m_textUpdated = true;
	}
	//std::cout<< cpt<< "\n";

	//target.draw(tstream, states);
	
	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{
		target.draw(m_buttons[i], states);
	}
}




std::map<std::wstring, sf::Texture> Scene::charactersTextures;




sf::Texture& Scene::requestCharacterTexture(const std::wstring& file)
{
	std::string cfile(file.begin(), file.end());
	cfile = std::string(CHARACTER_PATH .begin(), CHARACTER_PATH.end())+ cfile;

	texMap::iterator it;
	it = charactersTextures.find(file);
	if(it != charactersTextures.end())
	{
		return it->second;
	}
	else
	{
		//load the texture if not already done
		sf::Texture tex;
		tex.loadFromFile(cfile);
		charactersTextures[file] = tex;
		return charactersTextures[file];
	}

}



Scene::BgTextures Scene::backgroundTextures;

sf::Texture& Scene::requestBgTexture(const std::wstring& file)
{
	std::string cfile(file.begin(), file.end());
	cfile = std::string(BACKGROUND_PATH.begin(), BACKGROUND_PATH.end())+ cfile;

	texMap::iterator it;
	it = backgroundTextures.find(file);
	if(it != backgroundTextures.end())
	{
		return it->second;
	}
	else
	{
		//load the texture if not already done
		sf::Texture tex;
		tex.loadFromFile(cfile);
		backgroundTextures[file] = tex;
		return backgroundTextures[file];
	}
	
}







void Scene::loadNextAtomicScene()
{
	//test if the scene is finished
	if(m_atomicScenes.empty())
	{
		return;
	}


	//copy current characters in previous ones
	m_previousCharacters.clear();
	m_previousCharacters = m_characters;
	m_atomicScenes.pop();

	m_textUpdated = false;
	
	updateCharacters(m_previousCharacters);
	updateText();
	updateMusic();
	updateVoice();
	updateButtons();
	updateSelectors();
}




bool Scene::empty() const
{
	return m_atomicScenes.empty();
}




void apply_physics()
{
}



void Scene::firstUpdate()
{
	updateCharacters();
	updateText();
	updateMusic();
	updateVoice();
	updateButtons();
	updateSelectors();
	updateBackground();
}



void Scene::updateCharacters()
{
	m_previousCharacters.clear();
	m_characters.clear();
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());
	CharactersPtrList currentCharacters(currentScene.getCharacters());

	//std::cout<< currentCharacters.size()<< "\n";

	for(CharactersPtrList::iterator it = currentCharacters.begin(); it != currentCharacters.end(); it++)
	{
		//we must be overwritting in this function
		if(*it)
		{
			m_characters.push_back(
					std::shared_ptr<Character>(new Character(*(*it)) )
					);
		}
		else
		{
			std::cerr<< "Using a \"pass\" instruction with characters at the first AtomicScene\n";
		}
	}



}



void Scene::updateCharacters(CharactersPtrList &previousCharacters)
{
	m_characters.clear();
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());
	CharactersPtrList currentCharacters(currentScene.getCharacters());


	CharactersPtrList::iterator previousIt = previousCharacters.begin();
	bool previousEndReached = false;
	for(CharactersPtrList::iterator it = currentCharacters.begin(); it != currentCharacters.end(); it++)
	{
		//if we just want to load the old one
		if(!(*it) && !previousEndReached/* && (*previousIt)*/)
		{
			m_characters.push_back(
					std::shared_ptr<Character>(new Character(*(*previousIt)) )
					);
		}
		else if((*it))//if we are overwritting
		{
			m_characters.push_back(
					std::shared_ptr<Character>(new Character(*(*it)) )
					);
		}
		previousIt++;
		if(previousIt == previousCharacters.end())
		{
			previousEndReached = true;
		}
	}

}




void Scene::updateText()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());

	Text currentText(currentScene.getText());

	//std::cout<< "plop\n";
	
	if(currentText.append())
	{
		//m_text += currentText;
		tstream<< currentText;
	}
	else
	{
		//m_text = currentText;
		//std::cout<< "plop\n";
		tstream.clear();
		tstream<< currentText;
	}
}




void Scene::updateMusic()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());

	Music currentMusic(currentScene.getMusic());

	if(!currentMusic.empty()) //if we need to change the music
	{
		m_music.stop();
		m_music.openFromFile(currentMusic);
		m_music.play();
		m_music.setLoop(true);
	}
}



void Scene::updateVoice()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());

	Voice currentVoice(currentScene.getVoice());


	if(!currentVoice.empty())
	{
		m_voice.stop();
		m_voice.openFromFile(currentVoice);
		m_voice.play();
	}

	tstream.clearName();
	tstream.setName(currentScene.getName());
}



void Scene::updateButtons()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());

	m_buttons.clear();
	m_buttons = currentScene.getButtons();

	if(!m_buttons.empty())
	{
		setPrior(true);
	}
	else
	{
		setPrior(false);
	}

	//place the buttons on the screen
	float maxWidth = 0;
	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{
		auto bounds = m_buttons[i].getGlobalBounds();

		m_buttons[i].setPosition(0, ((WINDOW_SIZE.y / float(m_buttons.size()+1))*float(i+1)) - (bounds.height/2.) );
		
		if(bounds.width > maxWidth)
		{
			maxWidth = bounds.width;
		}
	}

	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].setWidth(maxWidth);
		m_buttons[i].setPosition( (WINDOW_SIZE.x / 2) - (maxWidth / 2), m_buttons[i].getPosition().y );

	}
}




void Scene::updateSelectors()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());
	SelectorArray curSelectors(currentScene.getSelectors());

	//m_nextFile.clear();
	for(std::size_t i = 0; i < curSelectors.size(); i++)
	{
		if(interpretAsBool(curSelectors[i].getExpression()))
		{
			m_nextFile = curSelectors[i].getScenario();
			prepareForNext();
		}
	}
}



void Scene::updateBackground()
{
	if(m_atomicScenes.empty())
	{
		return;
	}

	AtomicScene& currentScene(m_atomicScenes.front());
	BackgroundPtr curBg(currentScene.getBackground());

	if(curBg) //no calculations if there isn't a new background
	{
		m_background = *curBg;
	}
}





