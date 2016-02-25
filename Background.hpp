#ifndef DEF_BACKGROUND_HPP
#define DEF_BACKGROUND_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <memory>


const std::wstring BACKGROUND_PATH = std::wstring(L"gameData/images/backgrounds/");


typedef sf::Sprite Background;
typedef std::shared_ptr<Background> BackgroundPtr;


#endif //DEF_BACKGROUND_HPP
