/*
 * empty_tile.cpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#include "empty_tile.hpp"

/*
 * Constructors
 */
Empty_Tile::Empty_Tile()
{
	setWalkable(true);
	setCharToPrint('.');
	setTextureName("grass.png");
}


/*
 * Destructor
 */
Empty_Tile::~Empty_Tile()
{

}

/*
 * Getters
 */


/*
 * Methods
 */
void Empty_Tile::onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	// Nothing to do on enter in Empty Tile
	//std::cout << "Empty Tile onEnter" << std::endl;
}

void Empty_Tile::onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{

}



