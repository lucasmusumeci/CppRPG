/*
 * pkmn.hpp
 *
 *  Created on: 15 Dec 2025
 *      Author: lucas
 */

#ifndef PKMN_HPP_
#define PKMN_HPP_

#include <utility_functions.hpp>
#include "move.hpp"

#define STAT_BUFF_NEUTRAL 	6
#define MOVE_SLOTS		  	4
#define MAX_BUFF		  	6
#define SIZE_BUFFS			6
#define INDEX_EMPTY_MOVE	0
#define COEF_DMG_CALC		0.2
#define MAX_PKMN_PRESET_ID  32

class Pkmn
{
private:
	constexpr static std::array<float, 2*MAX_BUFF+1> buff_coef = {1.0/4, 2.0/7, 1.0/3, 2.0/5,
	 	 	 	  	  	  	  	  	  	  	  	  	  	 	 	   1.0/2, 2.0/3, 1.0, 1.5,
																   2.0, 2.5, 3.0, 3.5, 4.0};
	int id,max_hp,hp,attack,defense,sp_attack,sp_defense,speed;
	std::string name;
	Type type1, type2;
	int buffs[SIZE_BUFFS]; // Index match STAT enum's (0:NULL; 1:Attack; 2:Defense; ...)
						   // Values match buff_coef index (from 0 to 13)
	Move* moves[MOVE_SLOTS];
public:
	// Constructors
	Pkmn();
	Pkmn(sqlite3* db, int id);
	Pkmn(sqlite3* db, std::string &name);
	// Constructors from presets in DB -> bool preset to have != types as regular constructors
	Pkmn(sqlite3* db, int id_preset, bool preset); // Create the pkmn and add the moves from the id_preset in the DB
	Pkmn(sqlite3* db, std::string &name, bool preset); // Create the pkmn and add the moves from the first preset of this pkmn in the DB

	// Destructor
	virtual ~Pkmn();

	// Getters
	int 			getId();
	int				getMaxHP();
	int				getHP();
	int 			getAttack();
	int 			getDefense();
	int 			getSpecialAttack();
	int 			getSpecialDefense();
	int 			getSpeed();
	std::string& 	getName();
	Type 			getType1();
	Type 			getType2();
	int 			getBuff(Stat stat);
	Move* 			getMoveByIndex(int index);
	float			getHPratio();	// returns hp/max_hp
	float 			getEffectiveStat(Stat stat);

	// Setters
	void 	setHP(int hp);

	// Methods
	int 	addBuff(Stat stat, int buff); // 0:OK ; -1:Can't go lower ; 1:Can't go higher
	void	resetAllBuffs(); // Reset to default value
	int 	learnMove(sqlite3* db, int id); // 0:OK ; 1:No empty slot ; 2:Already learned
	int 	learnMove(sqlite3* db, std::string name);
	int 	findMove(int id); // index:found ; -1:Not found
	int 	findMove(std::string name);
	bool 	forgetMove(int id); // 0:OK ; 1:Not OK
	bool 	forgetMove(std::string name);
	bool	isKO(); // 0:Not KO ; 1:KO
	bool    isNULL(); // 0:Not NULL pkmn ; 1:NULL pkmn
	bool 	heal(int hp); // 0:Healed ; 1:KO
	bool	revive(float hp_coef);	// hp_coef : coef of hp_max restored ; 0:Revived ; 1:NOT KO
	void 	damage(int hp);
	float	STAB(Move* move); // 1:not same type ; 1.5:same type
	float	typeAdvantage(Pkmn* pkmn_opponent); // Gives an idea of the type disadvantage the pkmn has against another one [1/8;8]
	char	findSelfBuffMoves(); // sets bits0:3 to 1 if move0:3 is an EFFECT move with SELF target and adds to number of buff move into bits4:7
	int 	calculateDamage(Pkmn* opponent, int move_index);
	int		findBestDamageMove(Pkmn* opponent_pkmn); // -1:no dmg move ; index:best dmg move

	// Always specify an opponent even for self buff
	// -1:Empty move ; 0:OK ; 1:Dodged
	int 	useMove(Pkmn* opponent, int move_index);
};

#endif /* PKMN_HPP_ */
