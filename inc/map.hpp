/*
 * map.hpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#ifndef INC_MAP_HPP_
#define INC_MAP_HPP_

#include <fstream>
#include <vector>
#include <memory>

#include "display_map.hpp"
#include "empty_tile.hpp"
#include "wall_tile.hpp"
#include "grass_tile.hpp"
#include "trainer_tile.hpp"
#include "pokecenter_tile.hpp"

#include "fight.hpp"

class Map {
private:
	std::vector<std::unique_ptr<Tile>> map;
	int size[2]; // (Rows, Columns)
	int view_size[4]; // (ylim_low, ylim_high, xlim_low, xlim_high)

	Trainer* pplayer;
	player_position_t player_pos;

	sqlite3* db;

	sf::RenderWindow* pwindow;
	sf::Font* pfont;

	Display_Map display_map;
	// Private Methods
public:

	// Constructor
	Map(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db);

	// Destructor
	virtual ~Map();

	// Getters
	Display_Map* getDisplay();

	// Setters
	void setSize(int nrows, int ncols);

	// Methods
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void interact();
	void handleEvent(sf::Event event);
	std::unique_ptr<Tile> createTileFromChar(char c);
	void generateStaticMapFromFile(std::string filename);

	void DisplayInConsole();
};



#endif /* INC_MAP_HPP_ */
