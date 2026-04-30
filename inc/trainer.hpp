/*
 * trainer.hpp
 *
 *  Created on: 16 Dec 2025
 *      Author: lucas
 */

#ifndef TRAINER_HPP_
#define TRAINER_HPP_

#include "pkmn.hpp"
#include <vector>

#define MAX_TEAM_SIZE	6
#define STARTING_MONEY  1000
#define MAX_TRAINER_PRESET_ID	(7)

enum Object {
	NULL_OBJECT, POTION, SUPER_POTION, HYPER_POTION, POTION_MAX,
	ATTACK_PLUS, DEFENSE_PLUS, SP_ATTACK_PLUS, SP_DEFENSE_PLUS, SPEED_PLUS,
	RAPPEL, RAPPEL_MAX
};

bool isBuffObject(Object object);
Stat getStatBuffObject(Object object);

class Trainer
{
private:
	std::string name;
	Pkmn team[MAX_TEAM_SIZE];
	int  index_active_pkmn; // -1:None
	std::unordered_map<Object, int> object_bag;	// Object -> count
	int money;
	bool wild_pkmn;
public:
	// Constructors
	Trainer();
	Trainer(sqlite3* db, std::vector<int> pkmn_ids, std::string name="Random dude", int money=STARTING_MONEY);
	Trainer(sqlite3* db, std::vector<std::string> pkmn_names, std::string name="Random dude", int money=STARTING_MONEY);
	// Constructors from presets in DB
	Trainer(sqlite3* db, int id_preset);
	Trainer(sqlite3* db, int pkmn_preset, bool wild_pkmn);
	Trainer(sqlite3* db, std::string trainer_name);

	// Destructor
	virtual ~Trainer();

	// Getters
	std::string getName();
	Pkmn* getPkmn(int index);
	int   getIndexActivePkmn();
	Pkmn* getActivePkmn();
	std::unordered_map<Object, int> getObjectBag();
	int   getCount(Object object);
	int   getObjectBagSize();
	int   getMoney();

	// Setters
	int setIndexActivePkmn(int index); // 0:OK ; 1:No Pkmn at index ; 2:Pkmn is KO

	// Methods
	bool addPkmn(sqlite3* db, int pkmn_id); // 0:OK ; 1:Team Full
	bool addPkmn(sqlite3* db, std::string pkmn_name);
	void addMoney(int money);
	void addObject(Object object, int count=1);
	void removeObject(Object object, int count=1);
	int  isObjectUnusable(Object object, int pkmn_index); // 0:No ; 1:No item left ; 2:Can't heal KOed pkmn; 3:Can't revive NOT KOed pkmn
														  // 4:Can't buff non active pkmn ; 5:NULL pkmn at index;
	int  useObject(Object object, int pkmn_index); // 0:OK ; 1:No item left ; 2:Can't heal KOed pkmn; 3:Can't revive NOT KOed pkmn
	  	  	  	  	  	  	  	  	  	  	  	   // 4:Can't buff non active pkmn ; 5:NULL pkmn at index;
	Object hasPotion(); // NULL_OBJECT:no type of potion or <Object>:best potion available
	bool hasLost();
	bool isWild(); // 0:regular trainer ; 1:wild pkmn
};

#endif /* TRAINER_HPP_ */
