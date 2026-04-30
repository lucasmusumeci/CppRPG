/*
 * map.cpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#include "map.hpp"

/*
 * Constructor
 */
Map::Map(sf::RenderWindow* window, sf::Font* font, Trainer* player, sqlite3* db)
	: size{3,4},
	  view_size{0, 3, 0, 4},
	  player_pos{2,1,RIGHT},
	  display_map(window, font, &player_pos, &map, size, view_size)
{
	// Player
	pplayer = player;

	this->db = db;

	// Display
	pwindow = window;
	pfont = font;

	// Map
	std::string map_filename = "./assets/maps/big_map_demo.txt";
	generateStaticMapFromFile(map_filename);
	display_map.setSize(size[0], size[1]); // Update size for new map

	// Update view size for new map
	int nb_tile_in_row = pwindow->getSize().y / (SCALE_TILE * TILE_SIZE);
	(size[0] <= nb_tile_in_row) ? (view_size[1] = size[0]) : (view_size[1] = nb_tile_in_row);
	int nb_tile_in_col = pwindow->getSize().x / (SCALE_TILE * TILE_SIZE);
	(size[1] <= nb_tile_in_col) ? (view_size[3] = size[1]) : (view_size[3] = nb_tile_in_col);
	//display_map.setViewSize(view_size[0], view_size[1], view_size[2], view_size[3]);

	display_map.generateSpriteVector();
}

/*
 * Destructor
 */
Map::~Map()
{

}

/*
 * Getters
 */

Display_Map* Map::getDisplay()
{
	return &display_map;
}

/*
 * Setters
 */
void Map::setSize(int nrows, int ncols)
{
	this->size[0] = nrows;
	this->size[1] = ncols;
}

/*
 * Methods
 */
void Map::moveUp()
{
	// Find index of the tile up
	// y points down so up is negative
	int idx = (this->player_pos.y - 1) * this->size[1] + this->player_pos.x;
	if (this->player_pos.y-1 < 0 || this->player_pos.y-1 >= this->size[0])
	{
		// Player on border trying to move outside map
		std::cout << "Can't move outside map !" << std::endl;
	}
	else if (!this->map[idx]->isWalkable())
	{
		// Tile is not walkable
		std::cout << "Can't go on this tile" << std::endl;
	}
	else
	{
		// Can go on the tile
		// Update Player position
		this->player_pos.y--;

		// Update view_size if needed
		if (this->view_size[0] > 0 && this->player_pos.y - this->view_size[0] <= DISPLAY_MARGIN -1)
		{
			this->view_size[0]--;
			this->view_size[1]--;
		}


		// Call Tile's onEnter fuction
		this->map[idx]->onEnter(pwindow, pfont, pplayer, db);
	}
	this->player_pos.facing = UP;
}

void Map::moveDown()
{
	// Find index of the tile down
	// y points down so down is positive
	int idx = (this->player_pos.y + 1) * this->size[1] + this->player_pos.x;
	if (this->player_pos.y+1 < 0 || this->player_pos.y+1 >= this->size[0])
	{
		// Player on border trying to move outside map
		std::cout << "Can't move outside map !" << std::endl;
	}
	else if (!this->map[idx]->isWalkable())
	{
		// Tile is not walkable
		std::cout << "Can't go on this tile" << std::endl;
	}
	else
	{
		// Can go on the tile
		// Update Player position
		this->player_pos.y++;

		// Update view_size if needed
		if (this->view_size[1] < size[0]  && this->view_size[1] - this->player_pos.y <= DISPLAY_MARGIN)
		{
			this->view_size[0]++;
			this->view_size[1]++;
		}

		// Call Tile's onEnter fuction
		this->map[idx]->onEnter(pwindow, pfont, pplayer, db);
	}
	this->player_pos.facing = DOWN;
}

void Map::moveLeft()
{
	// Find index of the tile left
	int idx = this->player_pos.y * this->size[1] + this->player_pos.x - 1;
	if (this->player_pos.x-1 < 0 || this->player_pos.x-1 >= this->size[1])
	{
		// Player on border trying to move outside map
		std::cout << "Can't move outside map !" << std::endl;
	}
	else if (!this->map[idx]->isWalkable())
	{
		// Tile is not walkable
		std::cout << "Can't go on this tile" << std::endl;
	}
	else
	{
		// Can go on the tile
		// Update Player position
		this->player_pos.x--;

		// Update view_size if needed
		if (this->view_size[2] > 0 && this->player_pos.x - this->view_size[2] <= DISPLAY_MARGIN - 1)
		{
			this->view_size[2]--;
			this->view_size[3]--;
		}

		// Call Tile's onEnter fuction
		this->map[idx]->onEnter(pwindow, pfont, pplayer, db);
	}
	this->player_pos.facing = LEFT;
}

void Map::moveRight()
{
	// Find index of the tile right
	int idx = this->player_pos.y * this->size[1] + this->player_pos.x + 1;
	if (this->player_pos.x+1 < 0 || this->player_pos.x+1 >= this->size[1])
	{
		// Player on border trying to move outside map
		std::cout << "Can't move outside map !" << std::endl;
	}
	else if (!this->map[idx]->isWalkable())
	{
		// Tile is not walkable
		std::cout << "Can't go on this tile" << std::endl;
	}
	else
	{
		// Can go on the tile
		// Update Player position
		this->player_pos.x++;

		// Update view_size if needed
		if (this->view_size[3] < size[1]  && this->view_size[3] - this->player_pos.x <= DISPLAY_MARGIN)
		{
			this->view_size[2]++;
			this->view_size[3]++;
		}

		// Call Tile's onEnter fuction
		this->map[idx]->onEnter(pwindow, pfont, pplayer, db);
	}
	this->player_pos.facing = RIGHT;
}

void Map::interact()
{
	int idx;
	switch (this->player_pos.facing) {
		case UP:
			idx = (this->player_pos.y - 1) * this->size[1] + this->player_pos.x;
			break;
		case DOWN:
			idx = (this->player_pos.y + 1) * this->size[1] + this->player_pos.x;
			break;
		case LEFT:
			idx = this->player_pos.y * this->size[1] + this->player_pos.x - 1;
			break;
		case RIGHT:
			idx = this->player_pos.y * this->size[1] + this->player_pos.x + 1;
			break;
		default:
			break;
	}
	this->map[idx]->onInteract(pwindow, pfont, pplayer, db);
	this->display_map.updateTileSprite(idx);
}

void Map::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code) {
			case sf::Keyboard::Up:
				this->moveUp();
				break;
			case sf::Keyboard::Down:
				this->moveDown();
				break;
			case sf::Keyboard::Left:
				this->moveLeft();
				break;
			case sf::Keyboard::Right:
				this->moveRight();
				break;
			case sf::Keyboard::E:
				this->interact();
				break;
			case sf::Keyboard::S:
				getDisplay()->openShop(pplayer);
				break;
			default:
				break;
		}
	}

}

/*
 * '#' -> Wall_Tile
 * '"' -> Grass_Tile
 * '.' -> Empty_Tile
 * Default -> Empty_Tile
 */
std::unique_ptr<Tile> Map::createTileFromChar(char c)
{
	switch (c) {
		case '.':
			return std::make_unique<Empty_Tile>();
			break;
		case '#':
			return std::make_unique<Wall_Tile>();
			break;
		case '"':
			return std::make_unique<Grass_Tile>();
			break;
		case 'T':
			return std::make_unique<Trainer_Tile>();
			break;
		case '1':
			return std::make_unique<Pokecenter_Tile>("PokeCenter1.png");
			break;
		case '2':
			return std::make_unique<Pokecenter_Tile>("PokeCenter2.png");
			break;
		case '3':
			return std::make_unique<Pokecenter_Tile>("PokeCenter3.png");
			break;
		case '4':
			return std::make_unique<Pokecenter_Tile>("PokeCenter4.png");
			break;
		case '5':
			return std::make_unique<Pokecenter_Tile>("PokeCenter5.png");
			break;
		case '6':
			return std::make_unique<Pokecenter_Tile>("PokeCenter6.png");
			break;
		case '7':
			return std::make_unique<Pokecenter_Tile>("PokeCenter7.png");
			break;
		case '8':
			return std::make_unique<Pokecenter_Tile>("PokeCenter8.png");
			break;
		case '9':
			return std::make_unique<Pokecenter_Tile>("PokeCenter9.png");
			break;
		case 'a':
			return std::make_unique<Pokecenter_Tile>("PokeCenter10.png");
			break;
		case 'b':
			return std::make_unique<Pokecenter_Tile>("PokeCenter11.png");
			break;
		case 'c':
			return std::make_unique<Pokecenter_Tile>("PokeCenter12.png");
			break;
		case 'd':
			return std::make_unique<Pokecenter_Tile>("PokeCenter13.png");
			break;
		case 'e':
			return std::make_unique<Pokecenter_Tile>("PokeCenter14.png");
			break;
		case 'f':
			return std::make_unique<Pokecenter_Tile>("PokeCenter15.png");
			break;
		case 'g':
			return std::make_unique<Pokecenter_Tile>("PokeCenter16.png");
			break;
		default:
			std::cerr << "Unknown tile char : " << c << std::endl;
			return std::make_unique<Empty_Tile>();
			break;
	}
}

void Map::generateStaticMapFromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open map file: " << filename << std::endl;
	}

	this->map.clear();

	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file, line))
	{
		if (!line.empty() && line.back() == '\r')
			line.pop_back(); // Windows failsafe

		if (!line.empty())
			lines.push_back(line);
	}

	if (lines.empty())
	{
		std::cerr << "Map file is empty" << std::endl;
	}

    int rows = lines.size();
    int cols = lines[0].size();

    // Verify that every line has the same size
    for (std::string l : lines)
    {
        if ((int)(l.size()) != cols)
        {
            std::cerr << "Map file is not rectangular" << std::endl;
        }
    }

    size[0] = rows;
    size[1] = cols;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            map.push_back(createTileFromChar(lines[y][x]));
            // if lines[y][x] == T -> trainer_pos
        }
    }
}

void Map::DisplayInConsole()
{
	int map_size = this->size[0] * this->size[1];
	for (int i = 0; i < map_size; ++i) {
		// Check if player on tile
		if (i == (this->player_pos.y * this->size[1] + this->player_pos.x))
		{
			std::cout << "*"; // Char for player
		}
		else
		{
			std::cout << this->map[i]->getCharToPrint();
		}

		if ((i+1) % this->size[1] == 0)
		{
			std::cout << std::endl;
		}
	}
}
