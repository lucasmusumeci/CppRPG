/*
 * wall_tile.hpp
 *
 *  Created on: 17 janv. 2026
 *      Author: Alex
 */

#ifndef INC_WALL_TILE_HPP_
#define INC_WALL_TILE_HPP_

#include "tile.hpp"

class Wall_Tile : public Tile
{
private:
	bool breakable;

public:
	// Constructor
	Wall_Tile();

	// Destructor
	virtual ~Wall_Tile();

	// Getters

	// Methods
	bool isBreakable();
	void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
	void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
};



#endif /* INC_WALL_TILE_HPP_ */
