/*
 * fight.cpp
 *
 *  Created on: 23 Dec 2025
 *      Author: lucas
 */

#include "fight.hpp"

/*
 * Constructors
 */
Fight::Fight(sf::RenderWindow* window, sf::Font* font, Trainer* player, Trainer* opponent)
	: player(player),
	  opponent(opponent),
	  display(window, font, player, opponent)
{
}

/*
 * Destructor
 */
Fight::~Fight()
{

}

/*
 * Getters
 */
Trainer* Fight::getPlayer()
{
	return player;
}

Trainer* Fight::getOpponent()
{
	return opponent;
}

Display_Fight* Fight::getDisplay()
{
	return &display;
}

Pkmn* Fight::getPlayerPkmn()
{
	return player->getActivePkmn();
}

Pkmn* Fight::getOpponentPkmn()
{
	return opponent->getActivePkmn();
}

/*
 * Methods
 */
bool Fight::speedTest()
{
	if(getPlayerPkmn()->getEffectiveStat(SPEED) == getOpponentPkmn()->getEffectiveStat(SPEED))
	{
		return ( drawProbability() >= 0.5f );
	}
	else
	{
		return ( getPlayerPkmn()->getEffectiveStat(SPEED) > getOpponentPkmn()->getEffectiveStat(SPEED) );
	}
}

int Fight::turn()
{
	// --- Bot action choice ---
	Action bot_action;
	bool bot_valid_action = false;
	//int bot_valid_target =  false;
	int bot_move_index_chosen;
	int bot_pkmn_index_chosen;

	// Bot object selection (can only use potion type objects to heal only the active pokemon)
	Object bot_object_chosen = opponent->hasPotion();
	if(!bot_valid_action && bot_object_chosen!=NULL_OBJECT)
	{
		float roll = drawProbability();
		if(getOpponentPkmn()->getHPratio() < 0.25f  &&  roll < 0.2f)
		{
			bot_action = SAC;
			bot_valid_action = true;
		}
		else if(getOpponentPkmn()->getHPratio() < 0.5f  &&  roll < 0.1f)
		{
			bot_action = SAC;
			bot_valid_action = true;
		}
	}

	// Bot can switch pkmn if type disadvantage
	float active_score = getOpponentPkmn()->typeAdvantage(getPlayerPkmn()); // The higher, the better
	if(!bot_valid_action)
	{
		float max_score;
		int best_pkmn_id = findBestPkmnId(opponent, getPlayerPkmn(), active_score, &max_score);

		// The better the pick, the greater the chance to switch
		float score_ratio = max_score/active_score;
		if(best_pkmn_id != getOpponent()->getIndexActivePkmn())
		{
			float roll = drawProbability();
			if(score_ratio >= 8.0)
			{
				bot_action = POKEMONS;
			}
			else if(score_ratio >= 4.0  &&  roll < 0.7f)
			{
				bot_action = POKEMONS;
			}
			else if(score_ratio >= 2.0  &&  roll < 0.4f)
			{
				bot_action = POKEMONS;
			}

			// Confirms bot choice only if it rolled successfully
			if(bot_action == POKEMONS)
			{
				bot_pkmn_index_chosen = best_pkmn_id;
				bot_valid_action = true;
			}

		}

	}

	// Otherwise the bot picks an attack from it's active pkmn
	if(!bot_valid_action)
	{
		bot_action = ATTAQUE;

		// Stat buff move
		char buff_moves = getOpponentPkmn()->findSelfBuffMoves(); // 0:No buff move ; bits0:3 = position and bits4:7 = count
		char pos_count = (8*sizeof(buff_moves))/2;
		char count = buff_moves >> pos_count;
		float HPratio = getOpponentPkmn()->getHPratio();
		if((HPratio > 0.7f) && ((drawProbability()*HPratio) > (1.0f - 0.6f)) && buff_moves)
		{
			char roll = drawRandint(0, count);
			char nbr = 0;
			for(int i=0 ; i<MOVE_SLOTS ; i++)
			{
				if((buff_moves & (1 << (i+pos_count))) >> (i+pos_count)) nbr++;

				if(nbr == roll)
				{
					bot_move_index_chosen = i;
					bot_valid_action = true;
					break;
				}
			}
		}

		// Find the best damage move
		if(!bot_valid_action)
		{
			int index = getOpponentPkmn()->findBestDamageMove(getPlayerPkmn());
			if(index != -1)
			{
				bot_move_index_chosen = index;
				bot_valid_action = true;
			}
		}

		// If there is no dmg move we just pick the first move available
		if(!bot_valid_action)
		{
			for(int i=0 ; i<MOVE_SLOTS ; i++)
			{
				if(!getOpponentPkmn()->getMoveByIndex(i)->isEmpty())
				{
					bot_move_index_chosen = i;
					bot_valid_action = true;
				}
			}
		}


	}

	if(!bot_valid_action) throw std::runtime_error("Problem with bot's action selection");



	// --- Player action choice ---
	Action player_action;
	bool player_valid_action = false;
	int player_valid_target =  false;
	int player_move_index_chosen;
	int player_pkmn_index_chosen;
	Object player_object_chosen;

	while(!player_valid_action && display.getWindow()->isOpen())
	{
		player_action = display.chooseAction();
		switch(player_action)
		{
		case ATTAQUE:
			player_move_index_chosen = display.chooseMove();
			if(player_move_index_chosen == -1)
			{
				if(!display.getWindow()->isOpen()) return -1; // Window got closed
			}
			else
			{
				player_valid_action = true;
			}
			break;

		case POKEMONS:
			player_pkmn_index_chosen = display.choosePkmn();
			if(player_pkmn_index_chosen == -1)
			{
				if(!display.getWindow()->isOpen()) return -1;
			}
			else
			{
				if(player->getPkmn(player_pkmn_index_chosen)->isKO())
				{
					display.displayDialog(1500, "Ce pokémon ne peut pas être envoyé au combat car il est K.O.");
				}
				else
				{
					player_valid_action = true;
				}
			}
			break;

		case SAC:

			while(!player_valid_target  && display.getWindow()->isOpen())
			{
				player_object_chosen = display.chooseObject();
				if(player_object_chosen == NULL_OBJECT)
				{
					if(!display.getWindow()->isOpen()) return -1;
					else break;
				}
				else
				{
					if(isBuffObject(player_object_chosen)) // Has to be active pkmn for buff objects
					{
						player_pkmn_index_chosen = player->getIndexActivePkmn();
						player_valid_target = true;
						player_valid_action = true;
					}
					else
					{
						player_pkmn_index_chosen = display.choosePkmn();
						int object_unusable = player->isObjectUnusable(player_object_chosen, player_pkmn_index_chosen);
						if(player_pkmn_index_chosen != -1) // User chose a pkmn
						{
							display.drawFightingScreen();
							switch(object_unusable)
							{
							case 0: // Usable
								player_valid_target = true;
								player_valid_action = true;
								break;
							case 1: // No item left
								display.displayDialog(2000, "Vous n'avez plus aucun exemplaire de cet objet");
								break;
							case 2: // Can't use bc KO
								display.displayDialog(2000, "L'objet ne peut pas être utilisé car le pokémon sélectioné est K.O.");
								break;
							case 3: // Can't use bc NOT KO
								display.displayDialog(2000, "Un rappel ne peut pas être utilisé sur un pokémon non K.O.");
								break;
							case 4:	// Can only use buff object on active pkmn
								display.displayDialog(2000, "Un object Stat + ne que qu'être utilisé sur le pokémon actif");
								break;
							default:
								break;
							}
						}
					}
				}
			}
			break;
		case FUIR:
			display.displayDialog(2000, "Fuir... C'est pour les lâches !!");
			break;
		case CLOSE_GAME:
			return -1;
			break;
		}
	}
	// --- Action usage in the right order ---
	// Object usage
	if(player_action == SAC)
	{
		display.drawFightingScreen();
		Stat stat = getStatBuffObject(player_object_chosen); // Only used for buff objects
		int old_buff_index = getPlayerPkmn()->getBuff(stat);
		display.displayDialog(2000, "Vous utilisez un" + display.femininObject(player_object_chosen) + " "
				+ display.objectName(player_object_chosen) + " sur " + getPlayer()->getPkmn(player_pkmn_index_chosen)->getName());
		getPlayer()->useObject(player_object_chosen, player_pkmn_index_chosen);
		// If buff object -> show effect
		if(stat != NULL_STAT)
		{
			display.drawFightingScreen();
			display.displayBuffEffect(player_object_chosen, getPlayer()->getPkmn(player_pkmn_index_chosen), old_buff_index);
		}
		display.displayFightingScreen();
	}
	if(bot_action == SAC)
	{
		display.drawFightingScreen();
		Stat stat = getStatBuffObject(bot_object_chosen);
		int old_buff_index = getOpponentPkmn()->getBuff(stat);
		display.displayDialog(2000, getOpponent()->getName() + " utilise un" + display.femininObject(bot_object_chosen) + " "
				+ display.objectName(bot_object_chosen) + " sur " + getOpponentPkmn()->getName());
		getOpponent()->useObject(bot_object_chosen, getOpponent()->getIndexActivePkmn());
		// If buff object -> show effect
		if(stat != NULL_STAT)
		{
			display.drawFightingScreen();
			display.displayBuffEffect(bot_object_chosen, getOpponent ()->getPkmn(bot_pkmn_index_chosen), old_buff_index);
		}
		display.displayFightingScreen();
	}

	// Pkmn switch
	if(player_action == POKEMONS)
	{
		display.drawFightingScreen();
		display.displayDialog(2000, "Vous envoyez " + getPlayer()->getPkmn(player_pkmn_index_chosen)->getName() + " au combat");
		getPlayer()->setIndexActivePkmn(player_pkmn_index_chosen);
		display.displayFightingScreen();
	}
	if(bot_action == POKEMONS)
	{
		display.drawFightingScreen();
		display.displayDialog(2000, getOpponent()->getName() + " envoie " + getOpponent()->getPkmn(bot_pkmn_index_chosen)->getName() + " au combat");
		getOpponent()->setIndexActivePkmn(bot_pkmn_index_chosen);
		display.displayFightingScreen();
	}

	// Speedtest to know who is faster to attack first
	if(speedTest())
	{
		// Player's pkmn faster
		if(player_action == ATTAQUE)
		{
			Move* player_move = getPlayerPkmn()->getMoveByIndex(player_move_index_chosen);
			display.displayFightingDialog(2000, getPlayerPkmn()->getName() + " utilise " + player_move->getName());

			// Memorize stat before buff (used to draw the buff message later)
			int old_buff_index;
			switch(player_move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				old_buff_index = getPlayerPkmn()->getBuff(player_move->getStat());
				break;

			case OPPONENT:
				old_buff_index = getOpponentPkmn()->getBuff(player_move->getStat());
				break;
			}

			// Use move
			if(getPlayerPkmn()->useMove(getOpponentPkmn(),player_move_index_chosen) == 1)
			{
				// Dodged
				display.displayFightingDialog(2000, getOpponentPkmn()->getName() + " évite l'attaque");
			}
			else
			{
				display.displayMoveEffect(player_move, getOpponentPkmn());
				switch(player_move->getBuffTarget())
				{
				case NULL_TARGET: break;

				case SELF:
					display.displayBuffEffect(player_move, getPlayerPkmn(), old_buff_index);
					break;

				case OPPONENT:
					if(!getOpponentPkmn()->isKO())
					{
						display.displayBuffEffect(player_move, getOpponentPkmn(), old_buff_index);
					}
					break;
				}

				// Switch pkmn if KOed
				if(getOpponentPkmn()->isKO() && !getOpponent()->hasLost())
				{
					bot_action = FUIR; // To skip his attack turn
					display.drawFightingScreen();
					display.displayDialog(2000, getOpponentPkmn()->getName() + " est K.O.");
					float max_score = 0;
					int best_pkmn_id = findBestPkmnId(getOpponent(), getPlayerPkmn(), 0, &max_score);
					display.drawFightingScreen();
					display.displayDialog(2000, getOpponent()->getName() + " envoie " + getOpponent()->getPkmn(best_pkmn_id)->getName() + " au combat");
					getOpponent()->setIndexActivePkmn(best_pkmn_id);
					display.displayFightingScreen();
				}
				else if(getOpponent()->hasLost()) bot_action = FUIR; // To skip his attack turn
			}
		}

		if(bot_action == ATTAQUE)
		{
			Move* opponent_move = getOpponentPkmn()->getMoveByIndex(bot_move_index_chosen);
			display.displayFightingDialog(2000, getOpponentPkmn()->getName() + " utilise " + opponent_move->getName());

			// Memorize stat before buff (used to draw the buff message later)
			int old_buff_index;
			switch(opponent_move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				old_buff_index = getOpponentPkmn()->getBuff(opponent_move->getStat());
				break;

			case OPPONENT:
				old_buff_index = getPlayerPkmn()->getBuff(opponent_move->getStat());
				break;
			}

			// Use move
			if(getOpponentPkmn()->useMove(getPlayerPkmn(),bot_move_index_chosen) == 1)
			{
				// Dodged
				display.displayFightingDialog(2000, getPlayerPkmn()->getName() + " évite l'attaque");
			}
			else
			{
				display.displayMoveEffect(opponent_move, getPlayerPkmn());
				switch(opponent_move->getBuffTarget())
				{
				case NULL_TARGET: break;

				case SELF:
					display.displayBuffEffect(opponent_move, getOpponentPkmn(), old_buff_index);
					break;

				case OPPONENT:
					display.displayBuffEffect(opponent_move, getPlayerPkmn(), old_buff_index);
					break;
				}

				// Switch pkmn if KOed
				if(getPlayerPkmn()->isKO() && !getPlayer()->hasLost())
				{
					display.drawFightingScreen();
					display.displayDialog(2000, getPlayerPkmn()->getName() + " est K.O.");
					if(!getPlayer()->hasLost())
					{
						display.drawFightingScreen();
						display.displayDialog(2000, "Quel pokémon voulez-vous envoyer au combat ?");
						int next_pkmn_index = display.choosePkmn();
						Pkmn* pkmn_chosen = player->getPkmn(next_pkmn_index);
						while( (next_pkmn_index == -1 || pkmn_chosen->isKO()) && display.getWindow()->isOpen())
						{
							if(pkmn_chosen->isKO() && next_pkmn_index != -1)
							{
								display.drawFightingScreen();
								display.displayDialog(1500, "Ce pokémon ne peut pas être envoyé au combat car il est K.O.");
							}
							next_pkmn_index = display.choosePkmn();
							pkmn_chosen = player->getPkmn(next_pkmn_index);
						}


						display.drawFightingScreen();
						display.displayDialog(2000, "Vous envoyez " + pkmn_chosen->getName() + " au combat");
						getPlayer()->setIndexActivePkmn(next_pkmn_index);
						display.displayFightingScreen();
					}
				}
			}
		}
	}
	else
	{
		// Opponent's pkmn faster
		if(bot_action == ATTAQUE)
		{
			Move* opponent_move = getOpponentPkmn()->getMoveByIndex(bot_move_index_chosen);
			display.displayFightingDialog(2000, getOpponentPkmn()->getName() + " utilise " + opponent_move->getName());

			// Memorize stat before buff (used to draw the buff message later)
			int old_buff_index;
			switch(opponent_move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				old_buff_index = getOpponentPkmn()->getBuff(opponent_move->getStat());
				break;

			case OPPONENT:
				old_buff_index = getPlayerPkmn()->getBuff(opponent_move->getStat());
				break;
			}

			// Use move
			if(getOpponentPkmn()->useMove(getPlayerPkmn(),bot_move_index_chosen) == 1)
			{
				// Dodged
				display.displayFightingDialog(2000, getPlayerPkmn()->getName() + " évite l'attaque");
			}
			else
			{
				display.displayMoveEffect(opponent_move, getPlayerPkmn());
				switch(opponent_move->getBuffTarget())
				{
				case NULL_TARGET: break;

				case SELF:
					display.displayBuffEffect(opponent_move, getOpponentPkmn(), old_buff_index);
					break;

				case OPPONENT:
					display.displayBuffEffect(opponent_move, getPlayerPkmn(), old_buff_index);
					break;
				}

				// Switch pkmn if KOed
				if(getPlayerPkmn()->isKO() && !getPlayer()->hasLost())
				{
					player_action = FUIR; // To skip his attack turn
					display.drawFightingScreen();
					display.displayDialog(2000, getPlayerPkmn()->getName() + " est K.O.");
					if(!getPlayer()->hasLost())
					{
						display.drawFightingScreen();
						display.displayDialog(2000, "Quel pokémon voulez-vous envoyer au combat ?");
						int next_pkmn_index = display.choosePkmn();
						Pkmn* pkmn_chosen = player->getPkmn(next_pkmn_index);
						while( (next_pkmn_index == -1 || pkmn_chosen->isKO()) && display.getWindow()->isOpen())
						{
							if(pkmn_chosen->isKO() && next_pkmn_index != -1)
							{
								display.drawFightingScreen();
								display.displayDialog(1500, "Ce pokémon ne peut pas être envoyé au combat car il est K.O.");
							}
							next_pkmn_index = display.choosePkmn();
							pkmn_chosen = player->getPkmn(next_pkmn_index);
						}


						display.drawFightingScreen();
						display.displayDialog(2000, "Vous envoyez " + pkmn_chosen->getName() + " au combat");
						getPlayer()->setIndexActivePkmn(next_pkmn_index);
						display.displayFightingScreen();
					}
				}
			}
		}

		if(player_action == ATTAQUE)
		{
			Move* player_move = getPlayerPkmn()->getMoveByIndex(player_move_index_chosen);
			display.displayFightingDialog(2000, getPlayerPkmn()->getName() + " utilise " + player_move->getName());

			// Memorize stat before buff (used to draw the buff message later)
			int old_buff_index;
			switch(player_move->getBuffTarget())
			{
			case NULL_TARGET: break;

			case SELF:
				old_buff_index = getPlayerPkmn()->getBuff(player_move->getStat());
				break;

			case OPPONENT:
				old_buff_index = getOpponentPkmn()->getBuff(player_move->getStat());
				break;
			}

			// Use move
			if(getPlayerPkmn()->useMove(getOpponentPkmn(),player_move_index_chosen) == 1)
			{
				// Dodged
				display.displayFightingDialog(2000, getOpponentPkmn()->getName() + " évite l'attaque");
			}
			else
			{
				display.displayMoveEffect(player_move, getOpponentPkmn());
				switch(player_move->getBuffTarget())
				{
				case NULL_TARGET: break;

				case SELF:
					display.displayBuffEffect(player_move, getPlayerPkmn(), old_buff_index);
					break;

				case OPPONENT:
					display.displayBuffEffect(player_move, getOpponentPkmn(), old_buff_index);
					break;
				}

				// Switch pkmn if KOed
				if(getOpponentPkmn()->isKO() && !getOpponent()->hasLost())
				{
					display.drawFightingScreen();
					display.displayDialog(2000, getOpponentPkmn()->getName() + " est K.O.");
					float max_score = 0;
					int best_pkmn_id = findBestPkmnId(getOpponent(), getPlayerPkmn(), 0, &max_score);
					display.drawFightingScreen();
					display.displayDialog(2000, getOpponent()->getName() + " envoie " + getOpponent()->getPkmn(best_pkmn_id)->getName() + " au combat");
					getOpponent()->setIndexActivePkmn(best_pkmn_id);
					display.displayFightingScreen();
				}
			}
		}
	}
	return 0;
}

int Fight::findBestPkmnId(Trainer* trainer, Pkmn* opponent_pkmn, float active_score, float* max_score)
{
	// Finds the best pokemon in the team to face the player's pkmn
	*max_score = active_score;
	int best_pkmn_id = trainer->getIndexActivePkmn();
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		Pkmn* pkmn_i = trainer->getPkmn(i);
		if(!pkmn_i->isNULL() && !pkmn_i->isKO())
		{
			float score = pkmn_i->typeAdvantage(opponent_pkmn)+1; // +1 to avoid sending a K.O. pkmn
			if(score > *max_score)
			{
				*max_score = score;
				best_pkmn_id = i;
			}
		}
	}
	return best_pkmn_id;
}

int Fight::battleUntilEnd()
{
	bool player_lost = getPlayer()->hasLost();
	bool opponent_lost = getOpponent()->hasLost();
	while(!(player_lost || opponent_lost))
	{
		if(turn() == -1) return -1;
		player_lost = getPlayer()->hasLost();
		opponent_lost = getOpponent()->hasLost();
	}

	resetAllBuffs();

	if(player_lost)
	{
		float penalty = 0.5f;
		display.drawFightingScreen();
		display.displayDialog(2000, "Tous vos pokémons sont K.O. Vous avez perdu...");
		display.drawFightingScreen();
		display.displayDialog(2000, "Vous prenez la fuite en laissant tomber "+std::to_string(penalty*getPlayer()->getMoney())+"$");
		playerLostPenalty(penalty);
		return 1;
	}
	else
	{
		if(getOpponent()->isWild())
		{
			display.drawFightingScreen();
			display.displayDialog(2000, getOpponent()->getName()+" est K.O. Vous avez gagné !");
		}
		else
		{
			display.drawFightingScreen();
			display.displayDialog(2000, "Tous les pokémons de "+getOpponent()->getName()+" sont K.O. Vous avez gagné !");
			display.drawFightingScreen();
			display.displayDialog(2000, "Après une brève mais intense négociation, "+getOpponent()->getName()+" vous fait don de "
										+std::to_string(getOpponent()->getMoney())+"$");
			playerWonReward();
		}
		return 0;
	}
}

void Fight::playerWonReward()
{
	getPlayer()->addMoney(getOpponent()->getMoney());
}

void Fight::playerLostPenalty(float penalty)
{
	getPlayer()->addMoney(-(penalty * getPlayer()->getMoney()));
}

void Fight::resetAllBuffs()
{
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		getPlayer()->getPkmn(i)->resetAllBuffs();
		getOpponent()->getPkmn(i)->resetAllBuffs();
	}
}
