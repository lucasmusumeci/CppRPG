/*
 * fight.hpp
 *
 *  Created on: 23 Dec 2025
 *      Author: lucas
 */

#ifndef FIGHT_HPP_
#define FIGHT_HPP_

#include "display_fight.hpp"

class Fight
{
private:
	Trainer* player;
	Trainer* opponent;
	Display_Fight display;
public:
	// Constructor
	Fight(sf::RenderWindow* window, sf::Font* font, Trainer* player, Trainer* opponent);

	// Destructor
	~Fight();

	// Getters
	Trainer* getPlayer();
	Trainer* getOpponent();
	Display_Fight* getDisplay();
	// Shortcuts to get active Pkmns
	Pkmn* 	 getPlayerPkmn();
	Pkmn*	 getOpponentPkmn();

	// Methods
	bool speedTest(); // 0:Player's Pkmn slower ; 1:Player's Pkmn faster ; If tie -> 50%:0 ; 50%:1
	int turn(); // 0:OK ; -1:Something went wrong with player choice (or window closed)
	int findBestPkmnId(Trainer* trainer, Pkmn* opponent_pkmn, float active_score, float* max_score); // return id best pick ; store score at pointer address (the lower, the better)
	int battleUntilEnd(); // stop when someone lose -> -1:error ; 0:player won ; 1:opponent won
	void playerWonReward(); // Add opponent's money to player money
	void playerLostPenalty(float penalty); // Lose penalty*player money
	void resetAllBuffs(); // Called at the end of a fight
};

#endif /* FIGHT_HPP_ */
