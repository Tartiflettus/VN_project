#ifndef DEF_SCENETYPES_HPP
#define DEF_SCENETYPES_HPP

#include <list>
#include <memory>
#include "Character.hpp"
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <set>
#include "Button.hpp"

typedef std::vector<Button> ButtonArray;

typedef std::list<std::shared_ptr<Character> > CharactersPtrList;

typedef std::map<std::wstring, sf::Texture> texMap;

typedef std::set<std::wstring> nameSet;

#endif //DEF_SCENETYPES_HPP

