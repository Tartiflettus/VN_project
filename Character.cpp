#include "Character.hpp"
#include "constants.hpp"



Character::Character()
{
}



void Character::setTexture(const sf::Texture &texture)
{
	sf::Sprite::setTexture(texture);
	
	//Set origin at the center of the sprite
	sf::FloatRect rect = getGlobalBounds();
	setOrigin(rect.width/2, rect.height);

	setScale(0.5, 0.5);
}



void Character::setSlot(unsigned int pos, unsigned int size)
{
	m_nbSlots = size;
	m_slot = pos;

	if(m_nbSlots == 0)
	{
		return;
	}

	float posSlot = WINDOW_SIZE.x / (m_nbSlots + 1);
	//sf::Vector2f curPosY = getPosition().y;

	setPosition(posSlot*m_slot, WINDOW_SIZE.y);
}



std::pair<unsigned int, unsigned int> Character::getSlot() const
{
	return std::pair<unsigned int, unsigned int>(m_slot, m_nbSlots);
}



