/*
 * Capacites.hpp
 *
 *  Created on: 12 Dec 2025
 *      Author: lucas
 */

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include <string>
#include <ostream>
#include <iostream>
#include <array>
#include <unordered_map>

#include <stdexcept> // To signal errors
#include <sqlite3.h>

#define NBR_TYPES	19
// Added NONE to offset ids values to match with ids in the DB
enum Category {
	NULL_CATEGORY,
	PHYSICAL,
	SPECIAL,
	EFFECT
};

enum Type {
	NULL_TYPE,NORMAL,FIRE,WATER,ELECTRIC,GRASS,ICE,FIGHTING,POISON,GROUND,FLYING,PSYCHIC,BUG,ROCK,GHOST,DRAGON,DARK,STEEL,FAIRY
};

enum Stat {
	NULL_STAT,ATTACK,DEFENSE,SP_ATTACK,SP_DEFENSE,SPEED
};

enum Buff_Target {
	NULL_TARGET,SELF,OPPONENT
};

constexpr float type_bonus[NBR_TYPES][NBR_TYPES] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
													{1,1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1,1,0.5,1},
													{1,1,0.5,0.5,1,2,2,1,1,1,1,1,2,0.5,1,0.5,1,2,1},
													{1,1,2,0.5,1,0.5,1,1,1,2,1,1,1,2,1,0.5,1,1,1},
													{1,1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5,1,1,1},
													{1,1,0.5,2,1,0.5,1,1,0.5,2,0.5,1,0.5,2,1,0.5,1,0.5,1},
													{1,1,0.5,0.5,1,2,0.5,1,1,2,2,1,1,1,1,2,1,0.5,1},
													{1,2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1,2,2,0.5},
													{1,1,1,1,1,2,1,1,0.5,0.5,1,1,1,0.5,0.5,1,1,0,2},
													{1,1,2,1,2,0.5,1,1,2,1,0,1,0.5,2,1,1,1,2,1},
													{1,1,1,1,0.5,2,1,2,1,1,1,1,2,0.5,1,1,1,0.5,1},
													{1,1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1,0,0.5,1},
													{1,1,0.5,1,1,2,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5,0.5},
													{1,1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1,1,0.5,1},
													{1,0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5,1,1},
													{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5,0},
													{1,1,1,1,1,1,1,0.5,1,1,1,2,1,1,2,1,0.5,1,0.5},
													{1,1,0.5,0.5,0.5,1,2,1,1,1,1,1,1,2,1,1,1,0.5,2},
													{1,1,0.5,1,1,1,1,2,0.5,1,1,1,1,1,1,2,2,0.5,1}};

float getTypeBonus(Type attack_type, Type defense_type1, Type defense_type2);

class Move
{
private:
	int id, base_power, buff;
	float precision;
	Category category;
	Type type;
	Stat stat;
	Buff_Target buff_target;
	std::string name;

public:
	// Constructors
	Move();
	Move(sqlite3* db, int id);
	Move(sqlite3* db, std::string &name);

	// Destructor
	virtual ~Move();

	// Getters
	int 			getId();
	std::string& 	getName();
	int 			getBasePower();
	float			getPrecision();
	Category 		getCategory();
	Type 			getType();
	int 			getBuff();
	Stat 			getStat();
	Buff_Target 	getBuffTarget();

	// Methods
	bool isEmpty(); // 0:NotEmpty and 1:Empty
};

#endif /* MOVE_HPP_ */
