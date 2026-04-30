/*
 * tile.cpp
 *
 *  Created on: 9 janv. 2026
 *      Author: mea
 */

#include "tile.hpp"

/*
 * Constructors
 */


/*
 * Destructor
 */
Tile::~Tile()
{

}


/*
 * Getters
 */
char Tile::getCharToPrint()
{
	return this->char_to_print;
}
std::string Tile::getTextureName()
{
	return this->texture_name;
}


/*
 * Setters
 */
void Tile::setWalkable(bool w)
{
	this->walkable = w;
}

void Tile::setCharToPrint(char c)
{
	this->char_to_print = c;
}

void Tile::setTextureName(std::string t)
{
	this->texture_name = t;
}


/*
 * Methods
 */
bool Tile::isWalkable()
{
	return this->walkable;
}




