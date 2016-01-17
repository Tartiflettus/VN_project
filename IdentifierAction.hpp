/*
* These fonctors that will be used to perform dynamic actions depending on wich identifier has been detected
*/
#ifndef DEF_IDENTIFIERACTION_HPP
#define DEF_IDENTIFIERACTION_HPP

#include <vector>
#include <string>





const std::wstring CHARACTER_PATH = std::wstring(L"gameData/images/characters/");





class AtomicScene;


class IdentifierAction
{
	public:
		IdentifierAction();
		virtual ~IdentifierAction();

		virtual void operator()(AtomicScene &scene) = 0;
};




std::vector<std::wstring> extractArgs(const std::wstring &str,std::size_t &pos, wchar_t start = L'{', wchar_t end = L'}');


std::wstring firstArg(const std::wstring &str,std::size_t &pos, wchar_t start = L'{', wchar_t end = L'}');



class IdentifierCharacter: public IdentifierAction
{
	public:
		IdentifierCharacter();

		virtual void operator()(AtomicScene &scene);
};


class IdentifierMusic: public IdentifierAction
{
	public:
		IdentifierMusic();

		virtual void operator()(AtomicScene &scene);
};



class IdentifierSound: public IdentifierAction
{
	public:
		IdentifierSound();

		virtual void operator()(AtomicScene &scene);
};



class IdentifierVoice: public IdentifierAction
{
	public:
		IdentifierVoice();

		virtual void operator()(AtomicScene &scene);
};


class IdentifierText: public IdentifierAction
{
	public:
		IdentifierText();

		virtual void operator()(AtomicScene &scene);
};


class IdentifierButton: public IdentifierAction
{
	public:
		IdentifierButton();

		virtual void  operator()(AtomicScene &scene);
};


class IdentifierSelector: public IdentifierAction
{
	public:
		IdentifierSelector();

		virtual void operator()(AtomicScene& scene);
};


class IdentifierBackground: public IdentifierAction
{
	public:
		IdentifierBackground();

		virtual void operator()(AtomicScene& scene);
};



#endif //DEF_IDENTIFIERACTION_HPP

