/*
 * wall_tile.cpp
 *
 *  Created on: 17 janv. 2026
 *      Author: Alex
 */

#include "wall_tile.hpp"

/*
 * Constructors
 */
Wall_Tile::Wall_Tile()
{
	setWalkable(false);
	setCharToPrint('#');
	setTextureName("rock.png");
	this->breakable = true;
}


/*
 * Destructor
 */
Wall_Tile::~Wall_Tile()
{

}

/*
 * Getters
 */


/*
 * Methods
 */
bool Wall_Tile::isBreakable()
{
	return this->breakable;
}

void Wall_Tile::onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	// Nothing to do on enter in Wall Tile
	//std::cout << "Wall Tile onEnter" << std::endl;
}

void Wall_Tile::onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	if (this->isBreakable())
	{
		setWalkable(true);
		setCharToPrint('+');
		setTextureName("brokenRock.png");
	}

}




