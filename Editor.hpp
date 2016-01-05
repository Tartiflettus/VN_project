/*
* Interface to easily edit a .scen file.
*/
#ifndef DEF_EDITOR_HPP
#define DEF_EDITOR_HPP

#include "AtomicScene.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Audio/Music.hpp>
#include "SceneTypes.hpp"
#include "FileLoader.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "edit.hpp"
#include <SFML/Graphics/VertexArray.hpp>


namespace sf
{
	class RenderTarget;
}



namespace edit
{
	class Action;

	class Editor: public sf::Drawable
	{
		public:
			typedef std::pair<std::wstring, Character> CharacterInfo;
			typedef std::list<std::pair<std::wstring, Character> > CharacterList;
			typedef std::vector<std::pair<std::wstring, Character> > CharacterArray;


			Editor();

			void handleAction(Action &action);

			void handleCharacter(Action &action);
			void handleText(Action &action);
			void handleVoice(Action &action);
			void handleMusic(Action &action);


			void updateDisplayers();
			void updateCharacterVertex();


			static void loadStaticData();

			static sf::Font stdFont;

		protected:
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			Action::item m_currentItem;

			CharacterArray m_characters;
			size_t m_curCharacter;

			
			std::wstring m_text;

			sf::Music m_voice;
			std::wstring m_voiceFile;

			sf::Music m_music;
			std::wstring m_musicFile;


			//displayers
			mutable sf::Text m_displayer;
			sf::VertexArray m_characterVertex;
	};

} //namespace edit



#endif //DEF_EDITOR_HPP

