/*
 * display.hpp
 *
 *  Created on: 2 Jan 2026
 *      Author: lucas
 */

#ifndef INC_DISPLAY_FIGHT_HPP_
#define INC_DISPLAY_FIGHT_HPP_

#include "trainer.hpp"
#include <locale>
#include <codecvt>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <thread>
#include <chrono>
#include <stdlib.h>

#define SCALE_OPPONENT_PKMN 3.5f
#define SCALE_PLAYER_PKMN 	4

enum Action {
	ATTAQUE, POKEMONS, SAC, FUIR, CLOSE_GAME
};

class Display_Fight
{
private:
	sf::RenderWindow* window;
	sf::Font* font;
	Trainer* player;
	Trainer* opponent;
	std::unordered_map<std::string, sf::Texture> loaded_textures; // string=filename
	std::unordered_map<std::string, sf::Sprite>  loaded_sprites;  // string=name
public:
	// Constructor
	Display_Fight(sf::RenderWindow* window, sf::Font* font, Trainer* player, Trainer* opponent);
	// Destructor
	~Display_Fight();
	// Getters
	sf::RenderWindow* getWindow();
	sf::Font* getFont();
	Trainer* getPlayer();
	Trainer* getOpponent();
	std::unordered_map<std::string, sf::Texture>* getLoadedTextures();
	std::unordered_map<std::string, sf::Sprite>*  getLoadedSprites();

	// Texture and sprite getters
	sf::Texture* getBaseTexture(std::string filename); // Find base texture into unordered map or add it if not into it yet
	sf::Sprite*  getBaseSprite(std::string filename); // Find base sprite into unordered map or add it if not into it yet
	sf::Texture* getPkmnTexture(std::string filename); // Find pkmn texture into unordered map or add it if not into it yet
	sf::Sprite*  getPkmnSprite(std::string filename); // Find pkmn sprite into unordered map or add it if not into it yet
	sf::Texture* getObjectTexture(Object object); 	  // Find object texture into unordered map or add it if not into it yet
	sf::Sprite*  getObjectSprite(Object object); // Find object sprite into unordered map or add it if not into it yet
	sf::Sprite*  getHPbarSprite(bool target); //0:trainer ; 1:opponent

	// Setters
	void setWindow(sf::RenderWindow* window);
	void setFont(sf::Font* font);
	void setPlayer(Trainer* player);
	void setOpponent(Trainer* opponent);
	// Drawing methods
	void drawFightingScreen();
	void drawDialogbox();
	void drawMenuBackground();
	void drawHPbar(); // update both HP bars and draw then onto window
	void drawHPbar(bool target);//update target HP bars and draw then onto window -> 0:trainer ; 1:opponent
	void drawPkmn(); // update and draw both pkmn
	void drawPkmn(bool target); // update and draw both pkmn
	void drawCursorAtPos(Point point); // update cursor pos and draw it
	void drawDialog(std::string text);
	void drawMoveEffect(Move* move, Pkmn* opponent);
	void drawBuffEffect(Move* move, Pkmn* target);

	// Display methods
	void displayFightingScreen(); // display the fighting screen
	void displayDialog(int duration_ms, std::string text);
	void displayFightingDialog(int duration_ms, std::string text); // Same as above but draw fighting screen
	void displayMoveEffect(Move* move, Pkmn* opponent);
	void displayBuffEffect(Move* move, Pkmn* target, int old_buff_index);
	void displayBuffEffect(Object object, Pkmn* target, int old_buff_index);
	// Get user input methods
	Action chooseAction(); // Return Action
	int    chooseMove(); // Return move_index -1:Escape or window closed
	int    choosePkmn(); // Return Pkmn_index -1:Escape or window closed
	Object chooseObject(); // Return Object NULL_OBJECT:Escape
	// Other methods
	sf::Color   typeColor(Type type); // Get the matching color for a given type
	std::string objectName(Object object);
	std::string statName(Stat stat);
	std::string femininObject(Object object);
	void updateHPbarTexture(bool target); //0:trainer ; 1:opponent

	// Insert a pattern every n char to format text
	std::string wrapText(const std::string& input, std::string pattern, std::size_t maxLineLength = 35);
};

#endif /* INC_DISPLAY_FIGHT_HPP_ */
