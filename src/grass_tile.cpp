/*
 * grass_tile.cpp
 *
 *  Created on: 17 janv. 2026
 *      Author: Alex
 */


#include <utility_functions.hpp>
#include "grass_tile.hpp"
#include "fight.hpp"

/*
 * Constructors
 */
Grass_Tile::Grass_Tile()
{
	setWalkable(true);
	setCharToPrint('"');
	setTextureName("tallGrass.png");
	this->spawn_chance = 0.1f;
}


/*
 * Destructor
 */
Grass_Tile::~Grass_Tile()
{

}

/*
 * Getters
 */


/*
 * Methods
 */
void Grass_Tile::onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	// Roll for chance of starting a combat
	if (drawProbability() <= this->spawn_chance)
	{
		// Start Fight
		int idx = drawRandint(1, MAX_PKMN_PRESET_ID);
		std::cout << "Wild pokemon id : " << idx << std::endl;
		Trainer opponent = Trainer(db, idx, true);
		Fight fight = Fight(window, font, player, &opponent);
		fight.battleUntilEnd();
		std::cout << "Fight !" << std::endl;
	}
}

void Grass_Tile::onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{

}


