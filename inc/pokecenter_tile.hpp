/*
 * pokecenter_tile.hpp
 *
 *  Created on: 21 janv. 2026
 *      Author: mea
 */

#ifndef INC_POKECENTER_TILE_HPP_
#define INC_POKECENTER_TILE_HPP_

#include "tile.hpp"
#include "pkmn.hpp"

class Pokecenter_Tile : public Tile
{
private:


public:
	// Constructor
	Pokecenter_Tile(std::string texturename);

	// Destructor
	virtual ~Pokecenter_Tile();

	// Getters

	// Methods
	void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
	void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
};



#endif /* INC_POKECENTER_TILE_HPP_ */
