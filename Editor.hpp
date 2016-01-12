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
#include "editTypes.hpp"
#include <SFML/Graphics/VertexArray.hpp>


namespace sf
{
	class RenderTarget;
}



namespace edit
{
	class Editor: public sf::Drawable
	{
		public:
			typedef std::pair<std::wstring, Character> CharacterInfo;
			typedef std::list<std::pair<std::wstring, Character> > CharacterList;
			typedef std::vector<std::pair<std::wstring, Character> > CharacterArray;

			
			Editor() = delete;
			Editor(std::size_t& number, sf::Music& voice, sf::Music& music);
			/* Editor(const Editor& editor); */


			void setNumber(std::size_t &number);


			void handleAction(Action &action);

			void handleCharacter(Action &action);
			void handleText(Action &action);
			void handleVoice(Action &action);
			void handleMusic(Action &action);


			void updateDisplayers();
			void updateCharacterVertex();
			void updateCharacterDisplayer();


			void saveToStream(std::wofstream& stream);
			void saveCharacter(std::size_t pos, std::wofstream& stream);
			void saveText(std::wofstream& stream);
			void saveVoice(std::wofstream& stream);
			void saveMusic(std::wofstream& stream);

			static void loadStaticData();

			static sf::Font stdFont;

		protected:
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			Action::item m_currentItem;

			CharacterArray m_characters;
			size_t m_curCharacter;

			
			std::wstring m_text;

			sf::Music *m_voice;
			std::wstring m_voiceFile;

			sf::Music *m_music;
			std::wstring m_musicFile;

			std::size_t *m_number;


			//displayers
			sf::Text m_displayer;
			sf::VertexArray m_characterVertex;
			sf::Text m_characterDisplayer;
	};

} //namespace edit



#endif //DEF_EDITOR_HPP

