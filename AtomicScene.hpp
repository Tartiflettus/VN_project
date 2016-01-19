/*
* An atomic scene starts with the user pressing a "next" button, and ends withe user pressing it again to see the next one.
*/
#ifndef DEF_ATOMICSCENE_HPP
#define DEF_ATOMICSCENE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map> //identifiers / how to act on AtomicScene
#include <memory> //smart pointers
#include "IdentifierAction.hpp"
//#include "Scene.hpp"
#include "SceneTypes.hpp"
#include "Text.hpp"
#include "Music.hpp"
#include "Voice.hpp"
#include "Background.hpp"
#include <utility> //pair
#include "ScenarioSelector.hpp"



typedef std::map<std::wstring, int> VarMap;



extern VarMap varMap;



class Scene;


class AtomicScene
{
	public:
		//types////////////////////////////////////
		//friend class IdentifierAction;
		typedef std::map<std::wstring, std::unique_ptr<IdentifierAction> > IdAction;
		typedef IdAction::iterator IdActionIterator;


		AtomicScene(const std::wstring &filePiece);

		
		//static functions/////////////////////////
		static void loadStaticData();

		//accessors
		std::wstring getCurrentBlock() const;

		std::wstring::size_type getCursorPos() const;
		void setCursorPos(std::wstring::size_type pos);

		void addCharacter(const std::shared_ptr<Character> &character);
		CharactersPtrList getCharacters() const;

		void setText(const Text &text);
		Text getText() const;

		//void setName(const std::wstring &string);
		std::wstring getName() const;

		void setVoice(const Voice &voice);
		Voice getVoice() const;

		
		void setMusic(const Music &music);
		Music getMusic() const;

		void addButton(const Button& button);
		ButtonArray getButtons() const;

		void addSelector(const ScenarioSelector& selector);
		SelectorArray getSelectors() const;

		void setBackground(const BackgroundPtr& bg);
		BackgroundPtr getBackground() const;
	

	private:
		static std::map<std::wstring, std::unique_ptr<IdentifierAction> > m_identifierArray;


		CharactersPtrList m_characters;
		
		Text m_text;

		Music m_music;

		Voice m_voice;

		ButtonArray m_buttons;

		SelectorArray m_selectors;

		BackgroundPtr m_bg;

		std::wstring m_currentBlock;
		std::wstring::size_type m_cursorPos;

		//std::wstring m_name;

		
		//return the first character after the identifier, or npos if not found
		std::wstring::size_type actIf(IdAction &identifiers, const std::wstring &filePiece, std::wstring::size_type pos);

};






#endif //DEF_ATOMICSCENE_HPP

