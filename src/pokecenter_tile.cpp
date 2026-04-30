/*
 * pokecenter_tile.cpp
 *
 *  Created on: 21 janv. 2026
 *      Author: mea
 */

#include "pokecenter_tile.hpp"

/*
 * Constructors
 */
Pokecenter_Tile::Pokecenter_Tile(std::string filename)
{
	setWalkable(false);
	setCharToPrint('P');
	setTextureName(filename);
}


/*
 * Destructor
 */
Pokecenter_Tile::~Pokecenter_Tile()
{

}

/*
 * Getters
 */


/*
 * Methods
 */
void Pokecenter_Tile::onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	// Cannot enter in Pokecenter Tile
}

void Pokecenter_Tile::onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
		player->getPkmn(i)->setHP(player->getPkmn(i)->getMaxHP()); // Full heal every pokemon
	}
	std::cout << "Pokemon Healed !" << std::endl;
}


