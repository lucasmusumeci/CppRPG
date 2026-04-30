/*
 * trainer_tile.hpp
 *
 *  Created on: 19 janv. 2026
 *      Author: Alex
 */

#ifndef INC_TRAINER_TILE_HPP_
#define INC_TRAINER_TILE_HPP_

#include "tile.hpp"
#include "trainer.hpp"

class Trainer_Tile : public Tile
{
private:
	std::string trainer_texture_name;
	bool trainer_KO;

public:
	// Constructor
	Trainer_Tile();

	// Destructor
	virtual ~Trainer_Tile();

	// Getters
	std::string getTrainerTextureName();
	bool getTrainerKO();

	// Setters
	void setTrainerTextureName(std::string new_texture_name);

	// Methods
	void onEnter(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
	void onInteract(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);
};



#endif /* INC_TRAINER_TILE_HPP_ */
