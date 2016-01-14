/*
* A Scene is a set of AtomicScenes, with preloaded data
*/
#ifndef DEF_SCENE_HPP
#define DEF_SCENE_HPP


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Audio/Music.hpp>
#include <map> //fileName -> texture
#include <string>
#include <memory> //smart pointers
#include <list>
#include <queue> //queue of AtomicScenes to make a full scene
#include <fstream>
#include "Character.hpp"
#include "Text.hpp"
#include "AtomicScene.hpp"
#include "SceneTypes.hpp"
#include "TextBoxStream.hpp"


namespace sf
{
	class RenderTarget;
}


class Character;




class Scene: public sf::Drawable
{
	public:
		//types////////////////////////////////////

		typedef std::queue<AtomicScene> AtomScens;

		Scene();
		~Scene();
		
		void loadFromStream(std::wifstream &stream);
		void loadFromString(const std::wstring &string);
		
		static std::map<std::wstring, sf::Texture> charactersTextures;
		static sf::Texture& requestCharacterTexture(const std::wstring& file);

		void loadNextAtomicScene();

		bool empty() const;

		//apply all "apply_physics" functions of the members
		void apply_physics();

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		void firstUpdate();
		void updateCharacters();
		void updateCharacters(CharactersPtrList &previousCharacters);
		void updateText();
		void updateMusic();
		void updateVoice();


		AtomScens m_atomicScenes;

		CharactersPtrList m_characters;
		CharactersPtrList m_previousCharacters;



		sf::Music m_music;

		sf::Music m_voice;

		//Text m_text;
		mutable bool m_textUpdated;
		//TextBoxStream m_textStream;
	};



#endif //DEF_SCENE_HPP

