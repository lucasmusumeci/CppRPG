/*
 * tile.hpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#ifndef INC_TILE_HPP_
#define INC_TILE_HPP_

#include "SFML/Graphics.hpp"

#include "trainer.hpp"

class Tile
{
private:
	bool walkable;
	std::string texture_name;
	char char_to_print;

protected:
	void setWalkable(bool w);
	void setCharToPrint(char c);
	void setTextureName(std::string t);

public:
	// Destructor
	virtual ~Tile();

	// Getters
	std::string getTextureName();
	char getCharToPrint();

	// Methods
	bool isWalkable();

	// Virtual Methods
	virtual void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db) = 0;
	virtual void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db) = 0;
};



#endif /* INC_TILE_HPP_ */
