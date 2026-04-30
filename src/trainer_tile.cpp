/*
 * trainer_tile.cpp
 *
 *  Created on: 19 janv. 2026
 *      Author: Alex
 */

#include "trainer_tile.hpp"
#include "fight.hpp"

/*
 * Constructors
 */
Trainer_Tile::Trainer_Tile()
{
	setWalkable(false);
	setCharToPrint('T');
	setTextureName("grass.png");
	this->trainer_texture_name = "trainer1.png";
	this->trainer_KO = false;
}


/*
 * Destructor
 */
Trainer_Tile::~Trainer_Tile()
{

}

/*
 * Getters
 */
std::string Trainer_Tile::getTrainerTextureName()
{
	return this->trainer_texture_name;
}

bool Trainer_Tile::getTrainerKO()
{
	return this->trainer_KO;
}

/*
 * Setters
 */
void Trainer_Tile::setTrainerTextureName(std::string new_texture_name)
{
	this->trainer_texture_name = new_texture_name;
}

/*
 * Methods
 */
void Trainer_Tile::onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	// Nothing to do on enter in Trainer Tile
}

void Trainer_Tile::onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
{
	if (!this->trainer_KO)
	{
		// Start Fight
		int idx = drawRandint(1, MAX_TRAINER_PRESET_ID);
		std::cout << "Random trainer id : " << idx << std::endl;
		Trainer opponent = Trainer(db, idx);
		Fight fight = Fight(window, font, player, &opponent);
		int winner = fight.battleUntilEnd();
		std::cout << "Fight !" << std::endl;

		if(winner == 0) // Player won
		{
			this->setWalkable(true);
			this->setTrainerTextureName("empty_texture");
			this->trainer_KO = true;
		}
	}
}





