/*
 * grass_tile.hpp
 *
 *  Created on: 17 janv. 2026
 *      Author: Alex
 */

#ifndef INC_GRASS_TILE_HPP_
#define INC_GRASS_TILE_HPP_

#include "tile.hpp"

class Grass_Tile : public Tile
{
private:
	float spawn_chance;
public:
	// Constructor
	Grass_Tile();

	// Destructor
	virtual ~Grass_Tile();

	// Getters

	// Methods
	void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
	void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
};



#endif /* INC_GRASS_TILE_HPP_ */
