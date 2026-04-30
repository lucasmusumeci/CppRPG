/*
 * trainer.cpp
 *
 *  Created on: 16 Dec 2025
 *      Author: lucas
 */

#include "trainer.hpp"

bool isBuffObject(Object object)
{
	switch(object)
	{
	case ATTACK_PLUS: return 1;
	case DEFENSE_PLUS: return 1;
	case SP_ATTACK_PLUS: return 1;
	case SP_DEFENSE_PLUS: return 1;
	case SPEED_PLUS: return 1;
	default: return 0;
	}
}

Stat getStatBuffObject(Object object)
{
	Stat stat;
	switch(object)
	{
	case ATTACK_PLUS: 		stat=ATTACK; break;
	case DEFENSE_PLUS: 		stat=DEFENSE; break;
	case SP_ATTACK_PLUS: 	stat=SP_ATTACK; break;
	case SP_DEFENSE_PLUS: 	stat=SP_DEFENSE; break;
	case SPEED_PLUS: 		stat=SPEED; break;
	default: 				stat=NULL_STAT; break;
	}
	return stat;
}

/*
 * Constructors
 */
Trainer::Trainer()
{
	name = "Default trainer";
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++) {team[i] = Pkmn();}
	index_active_pkmn = -1;
	money = STARTING_MONEY;
	wild_pkmn = false;
}

Trainer::Trainer(sqlite3* db, std::vector<int> pkmn_ids, std::string name, int money)
{
	this->name = name;
	int size = pkmn_ids.size();
	// Add the matching pokemons to the team
	for(int i=0 ; i<std::min(size,MAX_TEAM_SIZE) ; i++) {team[i] = Pkmn(db, pkmn_ids[i]);}
	// Fill the rest with empty pokemons
	for(int i=size ; i<MAX_TEAM_SIZE ; i++) {team[i] = Pkmn();}
	// If at least one real pokemon
	if(size) index_active_pkmn = 0;
	else index_active_pkmn = -1;
	this->money = money;
	wild_pkmn = false;
}


Trainer::Trainer(sqlite3* db, std::vector<std::string> pkmn_names, std::string name, int money)
{
	this->name = name;
	int size = pkmn_names.size();
	// Add the matching pokemons to the team
	for(int i=0 ; i<std::min(size,MAX_TEAM_SIZE) ; i++) {team[i] = Pkmn(db, pkmn_names[i]);}
	// Fill the rest with empty pokemons
	for(int i=size ; i<MAX_TEAM_SIZE ; i++) {team[i] = Pkmn();}
	// If at least one real pokemon
	if(size) index_active_pkmn = 0;
	else index_active_pkmn = -1;
	this->money = money;
	wild_pkmn = false;
}

Trainer::Trainer(sqlite3* db, int id_preset)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Name, Id_Pokemon_Preset1, Id_Pokemon_Preset2, Id_Pokemon_Preset3, Id_Pokemon_Preset4,"
    				  " Id_Pokemon_Preset5, Id_Pokemon_Preset6, Money, Nbr_MAX_POTION, Nbr_HYPER_POTION, Nbr_SUPER_POTION, Nbr_POTION"
    				  " FROM trainer_preset WHERE Id = ?;";
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
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
    	{
    		int id_pkmn_preset = sqlite3_column_int(stmt, i+1);
    		if(id_pkmn_preset > 0)
    		{
    			this->team[i] = Pkmn(db, id_pkmn_preset, true);
    		}
    		else
    		{
    			this->team[i] = Pkmn();
    		}
    	}
    	this->money = sqlite3_column_int(stmt, 7);
    	this->addObject(POTION_MAX, sqlite3_column_int(stmt, 8));
    	this->addObject(HYPER_POTION, sqlite3_column_int(stmt, 9));
    	this->addObject(SUPER_POTION, sqlite3_column_int(stmt, 10));
    	this->addObject(POTION, sqlite3_column_int(stmt, 11));
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No pokemon with this id in database");
    }

    sqlite3_finalize(stmt);
    index_active_pkmn = 0;
    wild_pkmn = false;
}

Trainer::Trainer(sqlite3* db, std::string trainer_name)
{
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT Name, Id_Pokemon_Preset1, Id_Pokemon_Preset2, Id_Pokemon_Preset3, Id_Pokemon_Preset4,"
    				  " Id_Pokemon_Preset5, Id_Pokemon_Preset6, Money, Nbr_MAX_POTION, Nbr_HYPER_POTION, Nbr_SUPER_POTION, Nbr_POTION"
    				  " FROM trainer_preset WHERE Name = ?;";
    // Prepare the statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare SQL statement");
    }
    // Bind parameter (const char*) => need to cast
    sqlite3_bind_text(stmt, 1, trainer_name.c_str(),-1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
    	this->name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
    	{
    		int id_pkmn_preset = sqlite3_column_int(stmt, i+1);
    		if(id_pkmn_preset > 0)
    		{
    			this->team[i] = Pkmn(db, id_pkmn_preset, true);
    		}
    		else
    		{
    			this->team[i] = Pkmn();
    		}
    	}
    	this->money = sqlite3_column_int(stmt, 7);
    	this->addObject(POTION_MAX, sqlite3_column_int(stmt, 8));
    	this->addObject(HYPER_POTION, sqlite3_column_int(stmt, 9));
    	this->addObject(SUPER_POTION, sqlite3_column_int(stmt, 10));
    	this->addObject(POTION, sqlite3_column_int(stmt, 11));
    }
    else
    {
    	sqlite3_finalize(stmt);
    	throw std::runtime_error("No pokemon with this id in database");
    }

    sqlite3_finalize(stmt);
    index_active_pkmn = 0;
    wild_pkmn = false;
}

Trainer::Trainer(sqlite3* db, int pkmn_preset, bool wild_pkmn)
{
	// Add the matching pokemons to the team
	this->team[0] = Pkmn(db, pkmn_preset, true);
	this->name = this->team[0].getName();
	// Fill the rest with empty pokemons
	for(int i=1 ; i<MAX_TEAM_SIZE ; i++) {this->team[i] = Pkmn();}
	// If at least one real pokemon
	index_active_pkmn = 0;
	this->money = 0;
	this->wild_pkmn = wild_pkmn;
}

/*
 * Destructor
 */
Trainer::~Trainer()
{
	//std::cout << "Trainer " << name << " was destroyed" << std::endl;
}

/*
 * Getters
 */
std::string Trainer::getName()
{
	return name;
}

Pkmn* Trainer::getPkmn(int index)
{
	return &team[index];
}

int Trainer::getIndexActivePkmn()
{
	return index_active_pkmn;
}

Pkmn* Trainer::getActivePkmn()
{
	return &team[index_active_pkmn];
}

std::unordered_map<Object, int> Trainer::getObjectBag()
{
	return object_bag;
}

int Trainer::getCount(Object object)
{
	if (object_bag.find(object) == object_bag.end()) return 0;
	return object_bag[object];
}

int Trainer::getObjectBagSize()
{
	int size=0;
    for (const auto& [id, count] : object_bag)
    {
    	if(count>0) size++;
    }
    return size;
}

int Trainer::getMoney()
{
	return money;
}

/*
 * Setters
 */
int Trainer::setIndexActivePkmn(int index)
{
	if(team[index].isNULL()) return 1;
	if(team[index].isKO()) return 2;
	getActivePkmn()->resetAllBuffs(); // Reset all buffs when switching pkmns
	index_active_pkmn =  index;
	return 0;
}

/*
 * Methods
 */
bool Trainer::addPkmn(sqlite3* db, int pkmn_id)
{
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		if(team[i].isNULL())
		{
			team[i] = Pkmn(db, pkmn_id);
			return 0;
		}
	}
	std::cout << "Team is full" << std::endl;
	return 1;
}

bool Trainer::addPkmn(sqlite3* db, std::string pkmn_name)
{
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		if(team[i].isNULL())
		{
			team[i] = Pkmn(db, pkmn_name);
			return 0;
		}
	}
	std::cout << "Team is full" << std::endl;
	return 1;
}

void Trainer::addMoney(int money)
{
	this->money += money;
}

void Trainer::addObject(Object object, int count)
{
	// If present in unordered map
	if (object_bag.find(object) == object_bag.end())
	{
		object_bag.emplace(object, count);
	}
	else
	{
		object_bag[object] += count;
	}
}

void Trainer::removeObject(Object object, int count)
{
	auto pair = object_bag.find(object);
	// If present in unordered map
	if (pair != object_bag.end())
	{
		// Can't go lower than 0
		pair->second = std::max(0, pair->second - count);
	}
}

int Trainer::isObjectUnusable(Object object, int pkmn_index)
{
	Pkmn* pkmn = getPkmn(pkmn_index);
	if(pkmn->isNULL()) return 5;
	// You don't have this object
	if(!getCount(object)) return 1;
	switch(object)
	{
	case NULL_OBJECT: break;
	case POTION:
		if(pkmn->isKO()) return 2;
		break;
	case SUPER_POTION:
		if(pkmn->isKO()) return 2;
		break;
	case HYPER_POTION:
		if(pkmn->isKO()) return 2;
		break;
	case POTION_MAX:
		if(pkmn->isKO()) return 2;
		break;
	case ATTACK_PLUS:
		if(pkmn_index != index_active_pkmn) return 4;
		break;
	case DEFENSE_PLUS:
		if(pkmn_index != index_active_pkmn) return 4;
		break;
	case SP_ATTACK_PLUS:
		if(pkmn_index != index_active_pkmn) return 4;
		break;
	case SP_DEFENSE_PLUS:
		if(pkmn_index != index_active_pkmn) return 4;
		break;
	case SPEED_PLUS:
		if(pkmn_index != index_active_pkmn) return 4;
		break;
	case RAPPEL: // Only works when the pkmn is KO
		if(!pkmn->isKO()) return 3;
		break;
	case RAPPEL_MAX: // Only works when the pkmn is KO
		if(!pkmn->isKO()) return 3;
	}
	return 0;
}

int Trainer::useObject(Object object, int pkmn_index)
{
	Pkmn* pkmn = getPkmn(pkmn_index);
	if(pkmn->isNULL()) return 4;
	// You don't have this object
	if(!getCount(object)) return 1;
	switch(object)
	{
	case NULL_OBJECT: break;
	case POTION:
		if(pkmn->isKO()) return 2;
		pkmn->heal(20);
		break;
	case SUPER_POTION:
		if(pkmn->isKO()) return 2;
		pkmn->heal(60);
		break;
	case HYPER_POTION:
		if(pkmn->isKO()) return 2;
		pkmn->heal(120);
		break;
	case POTION_MAX:
		if(pkmn->isKO()) return 2;
		pkmn->heal(9999);
		break;
	case ATTACK_PLUS:
		if(pkmn->isKO()) return 2;
		pkmn->addBuff(ATTACK,2);
		break;
	case DEFENSE_PLUS:
		if(pkmn->isKO()) return 2;
		pkmn->addBuff(DEFENSE,2);
		break;
	case SP_ATTACK_PLUS:
		if(pkmn->isKO()) return 2;
		pkmn->addBuff(SP_ATTACK,2);
		break;
	case SP_DEFENSE_PLUS:
		if(pkmn->isKO()) return 2;
		pkmn->addBuff(SP_DEFENSE,2);
		break;
	case SPEED_PLUS:
		if(pkmn->isKO()) return 2;
		pkmn->addBuff(SPEED,2);
		break;
	case RAPPEL: // Only works when the pkmn is KO
		if(!pkmn->isKO()) return 3;
		pkmn->revive(0.5);
		break;
	case RAPPEL_MAX: // Only works when the pkmn is KO
		if(!pkmn->isKO()) return 3;
		pkmn->revive(1.0);
	}
	removeObject(object, 1);
	return 0;
}

Object Trainer::hasPotion()
{
	if(getCount(POTION_MAX)) 	return POTION_MAX;
	if(getCount(HYPER_POTION)) 	return HYPER_POTION;
	if(getCount(SUPER_POTION)) 	return SUPER_POTION;
	if(getCount(POTION)) 		return POTION;
	return NULL_OBJECT;
}

bool Trainer::hasLost()
{
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		if(!getPkmn(i)->isNULL() && !getPkmn(i)->isKO()) return 0;
	}
	return 1;
}

bool Trainer::isWild()
{
	return wild_pkmn;
}


