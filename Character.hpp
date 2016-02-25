/*
* Definition of a character, an object that represents a ... character, with special properties
* adapted to the way he must act.
*/
#ifndef DEF_CHARACTER_HPP
#define DEF_CHARACTER_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <utility>
#include <string>


class Character: public sf::Sprite
{
	public:
		Character();

		void setTexture(const sf::Texture &texture);




		//place the character depending of the number of slots on an atomic scene
		void setSlot(unsigned int pos, unsigned int size);
		std::pair<unsigned int, unsigned int> getSlot() const;

	private:
		unsigned int m_nbSlots;
		unsigned int m_slot;
};




#endif //DEF_CHARACTER_HPP

