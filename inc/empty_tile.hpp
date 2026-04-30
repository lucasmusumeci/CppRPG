/*
 * empty_tile.hpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#ifndef INC_EMPTY_TILE_HPP_
#define INC_EMPTY_TILE_HPP_

#include "tile.hpp"

class Empty_Tile : public Tile
{
private:


public:
	// Constructor
	Empty_Tile();

	// Destructor
	virtual ~Empty_Tile();

	// Getters

	// Methods
	void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
	void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
};




#endif /* INC_EMPTY_TILE_HPP_ */
