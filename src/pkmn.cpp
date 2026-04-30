/*
 * pkmn.cpp
 *
 *  Created on: 15 Dec 2025
 *      Author: lucas
 */

#include "pkmn.hpp"

// To avoid recreating an already existing move
std::unordered_map<int, Move*> existing_moves;


/*
 * Constructors
 */
Pkmn::Pkmn()
{
	this->id = 0;
	this->max_hp = 0;
	this->hp = 0;
	this->attack = 1;
	this->defense = 1;
	this->sp_attack = 1;
	this->sp_defense = 1;
	this->speed = 1;
	this->name = "MissingNo.";
	this->type1 = NULL_TYPE;
	this->type2 = NULL_TYPE;
	for(int i=0 ; i<SIZE_BUFFS ; i++) {this->buffs[i]=STAT_BUFF_NEUTRAL;}
	// We always create at the beggining of the main the "Empty Move" so then we just pass the adress of the instance
	for(int i=0 ; i<MOVE_SLOTS ; i++) {this->moves[i]=existing_moves[INDEX_EMPTY_MOVE];}
}

Pkmn::Pkmn(sqlite3* db, int id)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Id,Name,HP,Attack,Defense,Sp_Attack,Sp_Defense,Speed,Id_Type1,Id_Type2 FROM pokemon WHERE Id = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (id)
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->id = sqlite3_column_int(stmt, 0);
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    	this->max_hp = sqlite3_column_int(stmt, 2);
    	this->hp = sqlite3_column_int(stmt, 2);
    	this->attack = sqlite3_column_int(stmt, 3);
    	this->defense = sqlite3_column_int(stmt, 4);
    	this->sp_defense = sqlite3_column_int(stmt, 5);
    	this->sp_attack = sqlite3_column_int(stmt, 6);
    	this->speed = sqlite3_column_int(stmt, 7);
    	this->type1 = static_cast<Type>(sqlite3_column_int(stmt, 8));
    	this->type2 = static_cast<Type>(sqlite3_column_int(stmt, 9));
    	for(int i=0 ; i<6 ; i++) {this->buffs[i]=STAT_BUFF_NEUTRAL;}
    	// We always create at the beggining of the main the "Empty Move" so then we just pass the adress of the instance
    	for(int i=0 ; i<MOVE_SLOTS ; i++) {this->moves[i]=existing_moves[INDEX_EMPTY_MOVE];}
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No pokemon with this id in database");
    }

    sqlite3_finalize(stmt);
}

Pkmn::Pkmn(sqlite3* db, std::string &name)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Id,Name,HP,Attack,Defense,Sp_Attack,Sp_Defense,Speed,Id_Type1,Id_Type2 FROM pokemon WHERE Name = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (const char*) => need to cast
    sqlite3_bind_text(stmt, 1, name.c_str(),-1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->id = sqlite3_column_int(stmt, 0);
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    	this->max_hp = sqlite3_column_int(stmt, 2);
    	this->hp = sqlite3_column_int(stmt, 2);
    	this->attack = sqlite3_column_int(stmt, 3);
    	this->defense = sqlite3_column_int(stmt, 4);
    	this->sp_defense = sqlite3_column_int(stmt, 5);
    	this->sp_attack = sqlite3_column_int(stmt, 6);
    	this->speed = sqlite3_column_int(stmt, 7);
    	this->type1 = static_cast<Type>(sqlite3_column_int(stmt, 8));
    	this->type2 = static_cast<Type>(sqlite3_column_int(stmt, 9));
    	for(int i=0 ; i<6 ; i++) {this->buffs[i]=STAT_BUFF_NEUTRAL;}
    	// We always create at the beggining of the main the "Empty Move" so then we just pass the adress of the instance
    	for(int i=0 ; i<MOVE_SLOTS ; i++) {this->moves[i]=existing_moves[INDEX_EMPTY_MOVE];}
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No pokemon with this name in database");
    }

    sqlite3_finalize(stmt);
}

Pkmn::Pkmn(sqlite3* db, int id_preset, bool preset)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT pokemon.Id, pokemon.Name, pokemon.HP, pokemon.Attack, pokemon.Defense, pokemon.Sp_Attack, pokemon.Sp_Defense,"
    				  " pokemon.Speed, pokemon.Id_Type1, pokemon.Id_Type2, pokemon_preset.Id_Move1, pokemon_preset.Id_Move2,"
    				  " pokemon_preset.Id_Move3, pokemon_preset.Id_Move4"
    				  " FROM pokemon_preset"
    				  " INNER JOIN pokemon ON pokemon_preset.Id_Pokemon=pokemon.Id"
    				  " WHERE pokemon_preset.Id = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (id)
    sqlite3_bind_int(stmt, 1, id_preset);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->id = sqlite3_column_int(stmt, 0);
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    	this->max_hp = sqlite3_column_int(stmt, 2);
    	this->hp = sqlite3_column_int(stmt, 2);
    	this->attack = sqlite3_column_int(stmt, 3);
    	this->defense = sqlite3_column_int(stmt, 4);
    	this->sp_defense = sqlite3_column_int(stmt, 5);
    	this->sp_attack = sqlite3_column_int(stmt, 6);
    	this->speed = sqlite3_column_int(stmt, 7);
    	this->type1 = static_cast<Type>(sqlite3_column_int(stmt, 8));
    	this->type2 = static_cast<Type>(sqlite3_column_int(stmt, 9));
    	for(int i=0 ; i<6 ; i++) {this->buffs[i]=STAT_BUFF_NEUTRAL;}
    	// We always create at the beginning of the main the "Empty Move" so then we just pass the address of the instance
    	for(int i=0 ; i<MOVE_SLOTS ; i++) {this->moves[i]=existing_moves[INDEX_EMPTY_MOVE];}
    	for(int i=0 ; i<MOVE_SLOTS ; i++) {learnMove(db, sqlite3_column_int(stmt, i+10));}
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No pokemon with this id in database");
    }

    sqlite3_finalize(stmt);
}

/*
 * Destructor
 */
Pkmn::~Pkmn()
{
	//std::cout << "Pokémon " << name << " was destroyed" << std::endl;
}


/*
 * Getters
 */
int Pkmn::getId()
{
    return id;
}

int Pkmn::getMaxHP()
{
    return max_hp;
}

int Pkmn::getHP()
{
    return hp;
}

int Pkmn::getAttack()
{
    return attack;
}

int Pkmn::getDefense()
{
    return defense;
}

int Pkmn::getSpecialAttack()
{
    return sp_attack;
}

int Pkmn::getSpecialDefense()
{
    return sp_defense;
}

int Pkmn::getSpeed()
{
    return speed;
}

std::string& Pkmn::getName()
{
    return name;
}

Type Pkmn::getType1()
{
    return type1;
}

Type Pkmn::getType2()
{
    return type2;
}

int Pkmn::getBuff(Stat stat)
{
    return buffs[static_cast<int>(stat)];
}

Move* Pkmn::getMoveByIndex(int index){
	return moves[index];
}

float Pkmn::getHPratio()
{
	return ( hp / float(max_hp) );
}

/*
 * Setters
 */
void Pkmn::setHP(int hp) {
    this->hp = hp;
}


/*
 * Methods
 */

int Pkmn::addBuff(Stat stat, int buff) {
	int stat_index = static_cast<int>(stat);
    this->buffs[stat_index] += buff;
    if(this->buffs[stat_index]>12)
    	{
    	this->buffs[stat_index]=12;
    	return 1;
    	}
    else if (this->buffs[stat_index]<0)
    	{
    	this->buffs[stat_index]=0;
    	return -1;
    	}
    return 0;
}

void Pkmn::resetAllBuffs()
{
	for(int i=0 ; i<6 ; i++) {this->buffs[i]=STAT_BUFF_NEUTRAL;}
}

float Pkmn::getEffectiveStat(Stat stat)
{
	float value;
	switch(stat)
	{
	case NULL_STAT:
		value = 0.0;
		break;
	case ATTACK:
		value = getAttack();
		break;
	case DEFENSE:
		value = getDefense();
		break;
	case SP_ATTACK:
		value = getSpecialAttack();
		break;
	case SP_DEFENSE:
		value = getSpecialDefense();
		break;
	case SPEED:
		value = getSpeed();
		break;
	}
	return value * buff_coef[buffs[static_cast<int>(stat)]];
}

// Check if not already learned or already existing in unordered map
int Pkmn::learnMove(sqlite3* db, int id)
{
	// Check if not already learned
	if(findMove(id) != -1)
	{
		std::cout << "Move n°" << id << " is already learned" << std::endl;
		return 2;
	}
	// Find first empty move
	for(int i=0 ; i<MOVE_SLOTS ; i++)
	{
		if(moves[i]->isEmpty())
		{
			// Only create an instance of the move if id not present in the unordered map
			if (existing_moves.find(id) == existing_moves.end()) {
				Move* addr = new Move(db, id);
				existing_moves.emplace(id, addr);
			}
			moves[i] = existing_moves[id];
			return 0;
		}
	}
	std::cout << "Couldn't learn move n°" << id << " because there is no empty slot left" << std::endl;
	return 1;
}

int Pkmn::learnMove(sqlite3* db, std::string name)
{
	// Check if not already learned
	if(findMove(name) != -1)
	{
		std::cerr << name << " is already learned" << std::endl;
		return 2;
	}
	// Find first empty move
	for(int i=0 ; i<MOVE_SLOTS ; i++)
	{
		int id;
		if(moves[i]->isEmpty())
		{
			// SQL statement to get the move id
			sqlite3_stmt* stmt = nullptr;
			const char* sql = "SELECT Id FROM move WHERE Name = ?;";
		    // Prepare the statement
		    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
		    {
		        throw std::runtime_error("Failed to prepare SQL statement");
		    }
		    // Bind parameter (const char*) => need to cast
		    sqlite3_bind_text(stmt, 1, name.c_str(),-1, SQLITE_STATIC);

		    int rc = sqlite3_step(stmt);
		    if (rc == SQLITE_ROW)
		    {
		    	id = sqlite3_column_int(stmt, 0);
		    }
		    else
		    {
		    	throw std::runtime_error("No matching result");
		    }

		    // Only create an instance of the move if id not present in the unordered map
			if (existing_moves.find(id) == existing_moves.end()) {
				Move* addr = new Move(db, id);
				existing_moves.emplace(id, addr);
			}
			moves[i] = existing_moves[id];
			return 0;
		}
	}
	std::cerr << "Couldn't learn move" << name << "because there is no empty slot left" << std::endl;
	return 1;
}

int Pkmn::findMove(int id){
	for(int i=0; i<MOVE_SLOTS ; i++)
	{
		if(moves[i]->getId() == id) return i;
	}
	return -1;
}

int Pkmn::findMove(std::string name){
	for(int i=0; i<MOVE_SLOTS ; i++)
	{
		if(moves[i]->getName() == name) return i;
	}
	return -1;
}

bool Pkmn::forgetMove(int id)
{
	int index = findMove(id);
	if(index >= 0 && index<4)
	{
		moves[index] = existing_moves[INDEX_EMPTY_MOVE];
		return 0;
	}
	return 1;
}

bool Pkmn::forgetMove(std::string name)
{
	int index = findMove(name);
	if(index >= 0 && index<4)
	{
		moves[index] = existing_moves[INDEX_EMPTY_MOVE];
		return 0;
	}
	return 1;
}

bool Pkmn::isKO()
{
	return !getHP();
}

bool Pkmn::isNULL()
{
	return !getId();
}

bool Pkmn::heal(int hp)
{
	if(isKO()) return 1;
	this->hp = std::min(max_hp,this->hp+hp);
	return 0;
}

bool Pkmn::revive(float hp_coef)
{
	if(!isKO()) return 1;
	this->hp = (int)(hp_coef*max_hp);
	return 0;
}
void Pkmn::damage(int hp)
{
	this->hp = std::max(0,this->hp-hp);
}

float Pkmn::STAB(Move* move)
{
	if(move->getType() == getType1() || move->getType() == getType2()) return 1.5f;
	return 1.0f;
}

float Pkmn::typeAdvantage(Pkmn* pkmn_opponent)
{
	float coef = getTypeBonus(getType1(), pkmn_opponent->getType1(), pkmn_opponent->getType2());
	if(getType2()!=NULL_TYPE) coef = coef * getTypeBonus(getType2(), pkmn_opponent->getType1(), pkmn_opponent->getType2());
	return coef;
}

char Pkmn::findSelfBuffMoves()
{
	char out = 0;
	char count = 0;
	for(int i=0 ; i<MOVE_SLOTS ; i++)
	{
		Move* move_i = getMoveByIndex(i);
		if(!move_i->isEmpty()  &&  move_i->getCategory() == EFFECT  &&  move_i->getBuffTarget() == SELF)
		{
			out |= (1 << i);
			count++;
		}
	}
	out |= (count << ((8*sizeof(out))/2));
	return out;
}

int Pkmn::calculateDamage(Pkmn* opponent, int move_index)
{
	Move* move = getMoveByIndex(move_index);
	int dmg;
	switch(move->getCategory())
	{
	case NULL_CATEGORY: return -1;

	case PHYSICAL:
		// Damage calculation and application to opponent
		dmg = COEF_DMG_CALC * move->getBasePower() * (getEffectiveStat(ATTACK)/opponent->getEffectiveStat(DEFENSE)) *
				  STAB(move) * getTypeBonus(move->getType(), opponent->getType1(), opponent->getType2());
		break;

	case SPECIAL:
		// Damage calculation and application to opponent
		dmg = COEF_DMG_CALC * move->getBasePower() * (getEffectiveStat(SP_ATTACK)/opponent->getEffectiveStat(SP_DEFENSE)) *
				  STAB(move) * getTypeBonus(move->getType(), opponent->getType1(), opponent->getType2());
		break;

	case EFFECT: return -1;
	}

	return dmg;
}

int	Pkmn::findBestDamageMove(Pkmn* opponent_pkmn)
{
	float max_score = -1;
	int index = -1;
	for(int i=0 ; i<MOVE_SLOTS ; i++)
	{
		// Gives an idea of the strength of a move
		float score_i = calculateDamage(opponent_pkmn,i) * getMoveByIndex(i)->getPrecision();
		if(score_i > max_score)
		{
			max_score = score_i;
			index = i;
		}
	}
	return index;
}

/*
 * Using moves
 */
int Pkmn::useMove(Pkmn* opponent, int move_index)
{
	Move* move = getMoveByIndex(move_index);
	switch(move->getCategory())
	{
	case NULL_CATEGORY: return -1;

	case PHYSICAL:
		if(drawProbability() > move->getPrecision())
		{
			// Dodged
			return 1;
		}
		else
		{
			// Damage calculation and application to opponent
			int dmg = COEF_DMG_CALC * move->getBasePower() * (getEffectiveStat(ATTACK)/opponent->getEffectiveStat(DEFENSE)) *
					  STAB(move) * getTypeBonus(move->getType(), opponent->getType1(), opponent->getType2());
			opponent->damage(dmg);

			// Apply effect
			switch(move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				addBuff(move->getStat(), move->getBuff());
				break;

			case OPPONENT:
				opponent->addBuff(move->getStat(), move->getBuff());
				break;
			}
		}
		break;

	case SPECIAL:
		if(drawProbability() > move->getPrecision())
		{
			// Dodged
			return 1;
		}
		else
		{
			// Damage calculation and application to opponent
			int dmg = COEF_DMG_CALC * move->getBasePower() * (getEffectiveStat(SP_ATTACK)/opponent->getEffectiveStat(SP_DEFENSE)) *
					  STAB(move) * getTypeBonus(move->getType(), opponent->getType1(), opponent->getType2());
			opponent->damage(dmg);

			// Apply effect
			switch(move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				addBuff(move->getStat(), move->getBuff());
				break;

			case OPPONENT:
				opponent->addBuff(move->getStat(), move->getBuff());
				break;
			}
		}
		break;

	case EFFECT:
		// Apply effect
		switch(move->getBuffTarget())
		{
		case NULL_TARGET: break;

		case SELF:
			addBuff(move->getStat(), move->getBuff());
			break;

		case OPPONENT:
			if(!opponent->isKO() && drawProbability() > move->getPrecision())
			{
				// Dodged
				return 1;
			}
			else
			{
				// Apply buff to opponent
				opponent->addBuff(move->getStat(), move->getBuff());
			}
			break;
		}
		break;

	}
	return 0;
}



