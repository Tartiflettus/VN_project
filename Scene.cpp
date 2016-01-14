#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "AtomicScene.hpp"
#include "FileLoader.hpp"
#include <string>

#include <iostream>

Scene::Scene()
{
	m_textUpdated = false;
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





void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
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

	target.draw(tstream, states);
	
	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{
		target.draw(m_buttons[i], states);
	}
}




std::map<std::wstring, sf::Texture> Scene::charactersTextures;




sf::Texture& Scene::requestCharacterTexture(const std::wstring& file)
{
	std::string cfile(file.begin(), file.end());

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

	//place the buttons on the screen
	for(std::size_t i = 0; i < m_buttons.size(); i++)
	{

	}
}





