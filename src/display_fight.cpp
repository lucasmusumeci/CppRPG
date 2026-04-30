/*
 * display.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: lucas
 */

#include <display_fight.hpp>

/*
 * Constructor
 */
Display_Fight::Display_Fight(sf::RenderWindow* window, sf::Font* font, Trainer* player, Trainer* opponent)
: window(window),
  font(font),
  player(player),
  opponent(opponent)
{
	// Define filenames
	std::string battleground = "battleground.png";
	std::string player_uibox = "playerBattleUIbox.png";
	std::string opponent_uibox = "opponentBattleUIbox.png";
	std::string HPbar_green = "HPbar_green.png";
	std::string HPbar_yellow = "HPbar_yellow.png";
	std::string HPbar_red = "HPbar_red.png";
	std::string cursor = "cursor.png";
	std::string red_cross = "redCross.png";

	// HP bars names (no fixed texture so not a filename)
	std::string player_HPbar = "player_HPbar";
	std::string opponent_HPbar = "opponent_HPbar";

	// Empty texture
	std::string empty_texture = "empty_texture";

	// Add textures to unordered map
	loaded_textures.emplace(battleground, sf::Texture{});
	loaded_textures.emplace(player_uibox, sf::Texture{});
	loaded_textures.emplace(opponent_uibox, sf::Texture{});
	loaded_textures.emplace(HPbar_green, sf::Texture{});
	loaded_textures.emplace(HPbar_yellow, sf::Texture{});
	loaded_textures.emplace(HPbar_red, sf::Texture{});
	loaded_textures.emplace(cursor, sf::Texture{});
	loaded_textures.emplace(empty_texture, sf::Texture{});
	loaded_textures.emplace(red_cross, sf::Texture{});

	// Load image files
	loaded_textures.at(battleground).loadFromFile("./assets/sprites/"+battleground);
	loaded_textures.at(player_uibox).loadFromFile("./assets/sprites/"+player_uibox);
	loaded_textures.at(opponent_uibox).loadFromFile("./assets/sprites/"+opponent_uibox);
	loaded_textures.at(HPbar_green).loadFromFile("./assets/sprites/"+HPbar_green);
	loaded_textures.at(HPbar_yellow).loadFromFile("./assets/sprites/"+HPbar_yellow);
	loaded_textures.at(HPbar_red).loadFromFile("./assets/sprites/"+HPbar_red);
	loaded_textures.at(cursor).loadFromFile("./assets/sprites/"+cursor);
	loaded_textures.at(empty_texture).create(1, 1);
	loaded_textures.at(red_cross).loadFromFile("./assets/sprites/"+red_cross);

	// Instanciate sprites
    loaded_sprites.emplace(battleground, sf::Sprite(loaded_textures.at(battleground)));
    loaded_sprites.emplace(player_uibox, sf::Sprite(loaded_textures.at(player_uibox)));
    loaded_sprites.emplace(opponent_uibox, sf::Sprite(loaded_textures.at(opponent_uibox)));
    loaded_sprites.emplace(player_HPbar, sf::Sprite(loaded_textures.at(HPbar_green)));
    loaded_sprites.emplace(opponent_HPbar, sf::Sprite(loaded_textures.at(HPbar_green)));
    loaded_sprites.emplace(cursor, sf::Sprite(loaded_textures.at(cursor)));
    loaded_sprites.emplace(empty_texture, sf::Sprite(loaded_textures.at(empty_texture)));
    loaded_sprites.emplace(red_cross, sf::Sprite(loaded_textures.at(red_cross)));

	// Compute scaling
	float scaleX_battleground = 800.0f / loaded_textures.at(battleground).getSize().x;
	float scaleY_battleground = 600.0f / loaded_textures.at(battleground).getSize().y;
	float scaleX_player_uibox = 380.0f / loaded_textures.at(player_uibox).getSize().x;
	float scaleY_player_uibox = 120.0f / loaded_textures.at(player_uibox).getSize().y;
	float scaleX_opponent_uibox = 380.0f / loaded_textures.at(opponent_uibox).getSize().x;
	float scaleY_opponent_uibox = 100.0f / loaded_textures.at(opponent_uibox).getSize().y;
	float scaleX_player_HPbar = 159.0f / loaded_textures.at(HPbar_green).getSize().x;
	float scaleY_player_HPbar = 17.0f / loaded_textures.at(HPbar_green).getSize().y;
	float scaleX_opponent_HPbar = 159.0f / loaded_textures.at(HPbar_green).getSize().x;
	float scaleY_opponent_HPbar = 17.0f / loaded_textures.at(HPbar_green).getSize().y;
	float scaleX_cursor = 50.0f / loaded_textures.at(cursor).getSize().x;
	float scaleY_cursor = 50.0f / loaded_textures.at(cursor).getSize().y;

	// Apply scaling
	loaded_sprites.at(battleground).setScale(scaleX_battleground, scaleY_battleground);
	loaded_sprites.at(player_uibox).setScale(scaleX_player_uibox, scaleY_player_uibox);
	loaded_sprites.at(opponent_uibox).setScale(scaleX_opponent_uibox, scaleY_opponent_uibox);
	loaded_sprites.at(player_HPbar).setScale(scaleX_player_HPbar, scaleY_player_HPbar);
	loaded_sprites.at(opponent_HPbar).setScale(scaleX_opponent_HPbar, scaleY_opponent_HPbar);
	loaded_sprites.at(cursor).setScale(scaleX_cursor, scaleY_cursor);

	// Set position
	loaded_sprites.at(battleground).setPosition(0, 0);
	loaded_sprites.at(player_uibox).setPosition(420, 450);
	loaded_sprites.at(opponent_uibox).setPosition(0, 50);
	loaded_sprites.at(player_HPbar).setPosition(612, 511);
	loaded_sprites.at(opponent_HPbar).setPosition(154, 115);
}

/*
 * Destructor
 */
Display_Fight::~Display_Fight()
{

}

/*
 * Getters
 */
sf::RenderWindow* Display_Fight::getWindow()
{
	return window;
}

sf::Font* Display_Fight::getFont()
{
	return font;
}

Trainer* Display_Fight::getPlayer()
{
	return player;
}

Trainer* Display_Fight::getOpponent()
{
	return opponent;
}

std::unordered_map<std::string, sf::Texture>* Display_Fight::getLoadedTextures()
{
	return &loaded_textures;
}

std::unordered_map<std::string, sf::Sprite>* Display_Fight::getLoadedSprites()
{
	return &loaded_sprites;
}

sf::Texture* Display_Fight::getBaseTexture(std::string filename)
{
    auto* textures = getLoadedTextures();

    auto [it, inserted] = textures->try_emplace(filename);
    if (inserted)
    {
        if (!it->second.loadFromFile("./assets/sprites/" + filename))
            throw std::runtime_error("Failed to load texture: " + filename);
    }
    return &(it->second);
}

sf::Sprite* Display_Fight::getBaseSprite(std::string filename)
{
	auto* sprites = getLoadedSprites();

    auto it = sprites->find(filename);
    if (it == sprites->end()) {
    	sprites->emplace(filename, sf::Sprite(*getBaseTexture(filename)));
    }
    return &(sprites->at(filename));
}

sf::Sprite* Display_Fight::getHPbarSprite(bool target)
{
	sf::Sprite* sprite;
	if(target) // Opponent
	{
		sprite = getBaseSprite("opponent_HPbar");
	}
	else // Player
	{
		sprite = getBaseSprite("player_HPbar");
	}
	return sprite;
}

sf::Texture* Display_Fight::getPkmnTexture(std::string filename)
{
    auto* textures = getLoadedTextures();

    auto [it, inserted] = textures->try_emplace(filename);
    if (inserted)
    {
        if (!it->second.loadFromFile("./assets/sprites/pkmn_sprites/" + filename))
            throw std::runtime_error("Failed to load texture: " + filename);
    }
    return &(it->second);
}

sf::Sprite* Display_Fight::getPkmnSprite(std::string filename)
{
	auto* sprites = getLoadedSprites();

    auto it = sprites->find(filename);
    if (it == sprites->end()) {
    	sprites->emplace(filename, sf::Sprite(*getPkmnTexture(filename)));
    }
    return &(sprites->at(filename));
}

sf::Texture* Display_Fight::getObjectTexture(Object object)
{
	std::string filename;
	switch(object)
	{
	case NULL_OBJECT: break;
	case POTION: 			filename="Potion.png"; 			break;
	case SUPER_POTION: 		filename="SuperPotion.png"; 	break;
	case HYPER_POTION: 		filename="HyperPotion.png"; 	break;
	case POTION_MAX: 		filename="PotionMax.png"; 		break;
	case ATTACK_PLUS: 		filename="AttackPlus.png"; 		break;
	case DEFENSE_PLUS: 		filename="DefensePlus.png"; 	break;
	case SP_ATTACK_PLUS: 	filename="SpAttackPlus.png"; 	break;
	case SP_DEFENSE_PLUS: 	filename="SpDefensePlus.png"; 	break;
	case SPEED_PLUS: 		filename="SpeedPlus.png"; 		break;
	case RAPPEL: 			filename="Rappel.png"; 			break;
	case RAPPEL_MAX: 		filename="RappelMax.png"; 		break;
	}

    auto* textures = getLoadedTextures();

    auto [it, inserted] = textures->try_emplace(filename);
    if (inserted)
    {
        if (!it->second.loadFromFile("./assets/sprites/object_sprites/" + filename))
            throw std::runtime_error("Failed to load texture: " + filename);
    }
    return &(it->second);
}

sf::Sprite* Display_Fight::getObjectSprite(Object object)
{
	std::string filename;
	switch(object)
	{
	case NULL_OBJECT: break;
	case POTION: 			filename="Potion.png"; 			break;
	case SUPER_POTION: 		filename="SuperPotion.png"; 	break;
	case HYPER_POTION: 		filename="HyperPotion.png"; 	break;
	case POTION_MAX: 		filename="PotionMax.png"; 		break;
	case ATTACK_PLUS: 		filename="AttackPlus.png"; 		break;
	case DEFENSE_PLUS: 		filename="DefensePlus.png"; 	break;
	case SP_ATTACK_PLUS: 	filename="SpAttackPlus.png"; 	break;
	case SP_DEFENSE_PLUS: 	filename="SpDefensePlus.png"; 	break;
	case SPEED_PLUS: 		filename="SpeedPlus.png"; 		break;
	case RAPPEL: 			filename="Rappel.png"; 			break;
	case RAPPEL_MAX: 		filename="RappelMax.png"; 		break;
	}

	auto* sprites = getLoadedSprites();

    auto it = sprites->find(filename);
    if (it == sprites->end()) {
    	sprites->emplace(filename, sf::Sprite(*getObjectTexture(object)));
    }
    return &(sprites->at(filename));
}

/*
 * Setters
 */
void Display_Fight::setWindow(sf::RenderWindow* window)
{
	this->window = window;
}

void Display_Fight::setFont(sf::Font* font)
{
	this->font = font;
}

void Display_Fight::setPlayer(Trainer* player)
{
	this->player = player;
}

void Display_Fight::setOpponent(Trainer* opponent)
{
	this->opponent = opponent;
}


/*
 * Drawing methods
 */
void Display_Fight::drawFightingScreen()
{
	Pkmn* player_pkmn = player->getActivePkmn();
	Pkmn* opponent_pkmn = opponent->getActivePkmn();

	// Text
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;
    sf::Text txt_HP;
    sf::Text txt_max_HP;
    sf::Text txt_player_pkmn;
    sf::Text txt_opponent_pkmn;
    txt_HP.setFont(*font);
    txt_max_HP.setFont(*font);
    txt_player_pkmn.setFont(*font);
    txt_opponent_pkmn.setFont(*font);
    txt_HP.setString(std::to_string(player_pkmn->getHP()));
    txt_max_HP.setString(std::to_string(player_pkmn->getMaxHP()));
    txt_player_pkmn.setString(to_wstring.from_bytes(player_pkmn->getName()));
    txt_opponent_pkmn.setString(to_wstring.from_bytes(opponent_pkmn->getName()));
    txt_HP.setCharacterSize(20);
    txt_max_HP.setCharacterSize(20);
    txt_player_pkmn.setCharacterSize(25);
    txt_opponent_pkmn.setCharacterSize(25);
    txt_HP.setFillColor(sf::Color::Black);
    txt_max_HP.setFillColor(sf::Color::Black);
    txt_player_pkmn.setFillColor(sf::Color::Black);
    txt_opponent_pkmn.setFillColor(sf::Color::Black);

	// Set position
	txt_HP.setPosition(640, 535);
	txt_max_HP.setPosition(720, 535);
	txt_player_pkmn.setPosition(470, 470);
	txt_opponent_pkmn.setPosition(30, 70);

	// Draw and Display
	window->draw(*getBaseSprite("battleground.png"));
	window->draw(*getBaseSprite("playerBattleUIbox.png"));
	window->draw(*getBaseSprite("opponentBattleUIbox.png"));
	drawPkmn();
	drawHPbar();
	window->draw(txt_HP);
	window->draw(txt_max_HP);
	window->draw(txt_player_pkmn);
	window->draw(txt_opponent_pkmn);
}

void Display_Fight::drawDialogbox()
{
	sf::Texture* tex_dialogbox = getBaseTexture("dialogbox.png");
	sf::Sprite dialogbox(*tex_dialogbox);
	float scaleX_dialogbox = 800.0f / tex_dialogbox->getSize().x;
	float scaleY_dialogbox = 200.0f / tex_dialogbox->getSize().y;
	dialogbox.setScale(scaleX_dialogbox, scaleY_dialogbox);
	dialogbox.setPosition(0, 600);
	window->draw(dialogbox);
}

void Display_Fight::drawMenuBackground()
{
	sf::Texture* tex_menu_bg = getBaseTexture("menu.png");
	sf::Sprite menu_bg(*tex_menu_bg);
	float scaleX_menu_bg = 800.0f / tex_menu_bg->getSize().x;
	float scaleY_menu_bg = 800.0f / tex_menu_bg->getSize().y;
	menu_bg.setScale(scaleX_menu_bg, scaleY_menu_bg);
	menu_bg.setPosition(0, 0);
	window->draw(menu_bg);
}

void Display_Fight::drawHPbar()
{
	updateHPbarTexture(0);
	updateHPbarTexture(1);
	window->draw(*getBaseSprite("player_HPbar"));
	window->draw(*getBaseSprite("opponent_HPbar"));
}

void Display_Fight::drawHPbar(bool target)
{
	if(target)
	{
		updateHPbarTexture(1);
		window->draw(*getBaseSprite("opponent_HPbar"));
	}
	else
	{
		updateHPbarTexture(0);
		window->draw(*getBaseSprite("player_HPbar"));
	}
}

void Display_Fight::drawPkmn()
{
	Pkmn* player_pkmn = getPlayer()->getActivePkmn();
	Pkmn* opponent_pkmn = getOpponent()->getActivePkmn();

	if(!player_pkmn->isKO())
	{
		sf::Sprite* sprite_player_pkmn   = getPkmnSprite(player_pkmn->getName() + "_back.png");
		sf::Vector2 player_pkmn_size = getPkmnTexture(player_pkmn->getName() + "_back.png")->getSize();
		sprite_player_pkmn->setScale(SCALE_PLAYER_PKMN, SCALE_PLAYER_PKMN);
		sprite_player_pkmn->setPosition(210 - 0.5*SCALE_PLAYER_PKMN*player_pkmn_size.x, 595 - SCALE_PLAYER_PKMN*player_pkmn_size.y);
		window->draw(*sprite_player_pkmn);
	}

	if(!opponent_pkmn->isKO())
	{
		sf::Sprite* sprite_opponent_pkmn = getPkmnSprite(opponent_pkmn->getName() + "_front.png");
		sf::Vector2 opponent_pkmn_size = getPkmnTexture(opponent_pkmn->getName() + "_front.png")->getSize();
		sprite_opponent_pkmn->setScale(SCALE_OPPONENT_PKMN, SCALE_OPPONENT_PKMN);
		sprite_opponent_pkmn->setPosition(620 - 0.5*SCALE_PLAYER_PKMN*opponent_pkmn_size.x, 420 - SCALE_PLAYER_PKMN*opponent_pkmn_size.y);
		window->draw(*sprite_opponent_pkmn);
	}
}

void Display_Fight::drawPkmn(bool target)
{
	if(target)
	{
		Pkmn* opponent_pkmn = getOpponent()->getActivePkmn();
		sf::Texture* tex_opponent_pkmn = getPkmnTexture(opponent_pkmn->getName() + "_front.png");
		sf::Sprite* sprite_opponent_pkmn = getPkmnSprite("opponent_pkmn");
		sprite_opponent_pkmn->setPosition(620 - 0.5*SCALE_PLAYER_PKMN*tex_opponent_pkmn->getSize().x, 420 - SCALE_PLAYER_PKMN*tex_opponent_pkmn->getSize().y);
		window->draw(*sprite_opponent_pkmn);
	}
	else
	{
		Pkmn* player_pkmn = getPlayer()->getActivePkmn();
		sf::Texture* tex_player_pkmn = getPkmnTexture(player_pkmn->getName() + "_back.png");
		sf::Sprite* sprite_player_pkmn   = getPkmnSprite("player_pkmn");
		sprite_player_pkmn->setPosition(210 - 0.5*SCALE_PLAYER_PKMN*tex_player_pkmn->getSize().x, 595 - SCALE_PLAYER_PKMN*tex_player_pkmn->getSize().y);
		window->draw(*sprite_player_pkmn);
	}
}

void Display_Fight::drawCursorAtPos(Point point)
{
	sf::Sprite* cursor = getBaseSprite("cursor.png");
	cursor->setPosition(point.x,point.y);
	window->draw(*cursor);
}

void Display_Fight::drawDialog(std::string text)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;
	sf::Text txt;
	txt.setFont(*font);
	txt.setString(to_wstring.from_bytes(wrapText(text, "\n\n")));
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::Black);
	txt.setPosition(50, 640);
	drawDialogbox();
	window->draw(txt);
}

void Display_Fight::drawMoveEffect(Move* move, Pkmn* opponent)
{
	if(move->getCategory() != EFFECT)
	{
		float coef = getTypeBonus(move->getType(),opponent->getType1(),opponent->getType2());
		if(coef < 0.01) 		drawDialog("Cela n'affecte pas " + opponent->getName());
		else if(coef < 0.26) 	drawDialog("C'est très peu efficace...");
		else if(coef < 0.51) 	drawDialog("Ce n'est pas très efficace...");
		else if(coef > 1.99) 	drawDialog("C'est super efficace !");
		else if(coef > 3.99) 	drawDialog("C'est hyper efficace !");
	}
}

/*
 * Display methods
 */
void Display_Fight::displayFightingScreen()
{
	drawDialogbox();
	drawFightingScreen();
	window->display();
}

void Display_Fight::displayDialog(int duration_ms, std::string text)
{
	drawDialog(text);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms)); // sleep 1s
}

void Display_Fight::displayFightingDialog(int duration_ms, std::string text)
{
	drawFightingScreen();
	drawDialog(text);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms)); // sleep 1s
}

void Display_Fight::displayMoveEffect(Move* move, Pkmn* opponent)
{
	drawFightingScreen();
	if(move->getCategory() != EFFECT)
	{
		float coef = getTypeBonus(move->getType(),opponent->getType1(),opponent->getType2());
		if(coef < 0.01) 		displayDialog(2000, "Cela n’affecte pas " + opponent->getName());
		else if(coef < 0.26) 	displayDialog(2000, "C'est très peu efficace...");
		else if(coef < 0.51) 	displayDialog(2000, "Ce n'est pas très efficace...");
		else if(coef > 1.99) 	displayDialog(2000, "C'est super efficace !");
		else if(coef > 3.99) 	displayDialog(2000, "C'est hyper efficace !");
	}
}

void Display_Fight::displayBuffEffect(Move* move, Pkmn* target, int old_buff_index)
{
	drawFightingScreen();
	std::string variation;
	std::string pluriel;
	int amount = move->getBuff();
	int index_total = old_buff_index + amount;
	Stat stat = move->getStat();

	if(index_total > 2*MAX_BUFF) // Goes over the max
	{
		amount = 2*MAX_BUFF - old_buff_index;
	}
	else if(index_total < 0) // Goes under the min
	{
		amount = - old_buff_index;
	}

	if(amount)
	{
		if(amount > 0)
		{
			variation = "augmente";
		}
		else
		{
			variation = "diminue";
		}
		if(abs(amount) > 1) pluriel = "s";
		displayDialog(2000, statName(stat) + " de " + target->getName() + " " + variation + " de " + std::to_string(abs(amount)) + " rang" + pluriel);
	}

	if(index_total >= 2*MAX_BUFF) // Goes over the max
	{
		displayDialog(2000, statName(stat) + " de " + target->getName() + " ne peut plus augmenter");
	}
	else if(index_total <= 0) // Goes under the min
	{
		displayDialog(2000, statName(stat) + " de " + target->getName() + " ne peut plus diminuer");
	}
}

void Display_Fight::displayBuffEffect(Object object, Pkmn* target, int old_buff_index)
{
	drawFightingScreen();
	std::string variation;
	std::string pluriel;
	int amount = 2;
	int index_total = old_buff_index + amount;
	Stat stat = getStatBuffObject(object);

	if(index_total > 2*MAX_BUFF) // Goes over the max
	{
		amount = 2*MAX_BUFF - old_buff_index;
	}
	else if(index_total < 0) // Goes under the min
	{
		amount = - old_buff_index;
	}

	if(amount)
	{
		if(amount > 0)
		{
			variation = "augmente";
		}
		else
		{
			variation = "diminue";
		}
		if(abs(amount) > 1) pluriel = "s";
		displayDialog(2000, statName(stat) + " de " + target->getName() + " " + variation + " de " + std::to_string(abs(amount)) + " rang" + pluriel);
	}

	if(index_total >= 2*MAX_BUFF) // Goes over the max
	{
		displayDialog(2000, statName(stat) + " de " + target->getName() + " ne peut plus augmenter");
	}
	else if(index_total <= 0) // Goes under the min
	{
		displayDialog(2000, statName(stat) + " de " + target->getName() + " ne peut plus diminuer");
	}
}

/*
 * Get user input methods
 */
Action Display_Fight::chooseAction()
{
	const int SIZE_X = 2;
	const int SIZE_Y = 2;
	Point coord_cur[SIZE_Y][SIZE_X] = {
	    { {50, 640}, {395, 640} },
	    { {50, 720}, {395, 720} }
	};
	int x = 0;
	int y = 0;

	// Text
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;
    sf::Text txt_attaques;
    sf::Text txt_pokemons;
    sf::Text txt_sac;
    sf::Text txt_fuir;
    txt_attaques.setFont(*font);
    txt_pokemons.setFont(*font);
    txt_sac.setFont(*font);
    txt_fuir.setFont(*font);
    txt_attaques.setString("ATTAQUES");
    txt_pokemons.setString(to_wstring.from_bytes("POKÉMONS"));
    txt_sac.setString("SAC");
    txt_fuir.setString("FUIR");
    txt_attaques.setCharacterSize(25);
    txt_pokemons.setCharacterSize(25);
    txt_sac.setCharacterSize(25);
    txt_fuir.setCharacterSize(25);
    txt_attaques.setFillColor(sf::Color::Black);
    txt_pokemons.setFillColor(sf::Color::Black);
    txt_sac.setFillColor(sf::Color::Black);
    txt_fuir.setFillColor(sf::Color::Black);
    txt_attaques.setStyle(sf::Text::Bold);
    txt_pokemons.setStyle(sf::Text::Bold);
    txt_sac.setStyle(sf::Text::Bold);
    txt_fuir.setStyle(sf::Text::Bold);

	// Positions
	txt_attaques.setPosition(50 + coord_cur[0][0].x, 10 + coord_cur[0][0].y);
	txt_pokemons.setPosition(50 + coord_cur[0][1].x, 10 + coord_cur[0][1].y);
	txt_sac.setPosition(50 + coord_cur[1][0].x, 10 + coord_cur[1][0].y);
	txt_fuir.setPosition(50 + coord_cur[1][1].x, 10 +coord_cur[1][1].y);

	// First time to have something on screen
	drawFightingScreen();
	drawDialogbox();
	drawCursorAtPos(coord_cur[y][x]);
	window->draw(txt_attaques);
	window->draw(txt_pokemons);
	window->draw(txt_sac);
	window->draw(txt_fuir);
	window->display();

	while(window->isOpen())
	{
		bool update_window = false;
        sf::Event event;
        while (window->pollEvent(event))
        {
        	// Close window
            if (event.type == sf::Event::Closed)
                window->close();

            // Move cursor
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
            	if(x<SIZE_X-1) x++;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            {
            	if(x>0) x--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
            {
            	if(y>0) y--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
            {
            	if(y<SIZE_Y-1) y++;
            	update_window = true;
            }

            // Confirm choice
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter));
            	return static_cast<Action>(SIZE_X*y + x);
            }
        }

        if(update_window)
        {
        	drawFightingScreen();
        	drawDialogbox();
    		drawCursorAtPos(coord_cur[y][x]);
    		window->draw(txt_attaques);
    		window->draw(txt_pokemons);
    		window->draw(txt_sac);
    		window->draw(txt_fuir);
    		window->display();
        }

	}
	return CLOSE_GAME; // Just to avoid warning
}

int Display_Fight::chooseMove()
{
	Pkmn* player_pkmn = player->getActivePkmn();

	const int SIZE_X = 2;
	const int SIZE_Y = 2;
	Point coord_cur[SIZE_Y][SIZE_X] = {
	    { {50, 640}, {395, 640} },
	    { {50, 720}, {395, 720} }
	};
	int x = 0;
	int y = 0;

	// Text
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;
	sf::Text txt_moves[MOVE_SLOTS];
	for(int i=0 ; i<MOVE_SLOTS ; i++)
	{
		txt_moves[i].setFont(*font);
		txt_moves[i].setString(to_wstring.from_bytes(player_pkmn->getMoveByIndex(i)->getName()));
		txt_moves[i].setCharacterSize(20);
		txt_moves[i].setFillColor(typeColor(player_pkmn->getMoveByIndex(i)->getType()));
		txt_moves[i].setPosition(45 + coord_cur[i/SIZE_X][i%SIZE_X].x, 9 + coord_cur[i/SIZE_X][i%SIZE_X].y);
	}

	// First time to have something on screen
	drawFightingScreen();
	drawDialogbox();
	drawCursorAtPos(coord_cur[y][x]);
	for(int i=0 ; i<MOVE_SLOTS ; i++) window->draw(txt_moves[i]);
	window->display();

	while(window->isOpen())
	{
		bool update_window = false;
        sf::Event event;
        while (window->pollEvent(event))
        {
        	// Close window
            if (event.type == sf::Event::Closed)
                window->close();

            // Move cursor
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
            	if(x<SIZE_X-1) x++;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            {
            	if(x>0) x--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
            {
            	if(y>0) y--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
            {
            	if(y<SIZE_Y-1) y++;
            	update_window = true;
            }

            // Confirm choice
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter));
            	if(!player_pkmn->getMoveByIndex(SIZE_X*y + x)->isEmpty())
            	{
            		return (SIZE_X*y + x);
            	}
            }

            // Go back to previous menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape));
            	return -1;
            }
        }

        if(update_window)
        {
        	drawFightingScreen();
        	drawDialogbox();
        	drawCursorAtPos(coord_cur[y][x]);
    		for(int i=0 ; i<MOVE_SLOTS ; i++) window->draw(txt_moves[i]);
    		window->display();
        }

	}
	return -1;
}

int Display_Fight::choosePkmn()
{
	const int SIZE_X = 3;
	const int SIZE_Y = 2;
	Point coord_cur[SIZE_Y][SIZE_X] = {
	    { {50, 640}, {300, 640}, {550, 640} },
	    { {50, 720}, {300, 720}, {550, 720} }
	};
	int x = 0;
	int y = 0;

	// Pkmns
	sf::Sprite* pkmns[MAX_TEAM_SIZE];
	float scaleX_pkmn = 70.0 / 32;
	float scaleY_pkmn = 70.0 / 32;
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		Pkmn* pkmn = player->getPkmn(i);
		if(!pkmn->isNULL())
		{
			pkmns[i] = getPkmnSprite(pkmn->getName() + "_mini.png");
		}
		else
		{
			pkmns[i] = getBaseSprite("empty_texture");
		}

		pkmns[i]->setScale(scaleX_pkmn, scaleY_pkmn);
		pkmns[i]->setPosition( 45 + coord_cur[i/SIZE_X][i%SIZE_X].x, -10 + coord_cur[i/SIZE_X][i%SIZE_X].y);
	}

	// Red cross
	sf::Sprite* redCross = getBaseSprite("redCross.png");
	redCross->setScale(scaleX_pkmn, scaleY_pkmn);

	// First time to have something on screen
	drawFightingScreen();
	drawDialogbox();
	drawCursorAtPos(coord_cur[y][x]);
	for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
	{
		window->draw(*pkmns[i]);
		Pkmn* pkmn_i = player->getPkmn(i);
		if(pkmn_i->isKO() && !pkmn_i->isNULL())
		{
			redCross->setPosition( 45 + coord_cur[i/SIZE_X][i%SIZE_X].x, -10 + coord_cur[i/SIZE_X][i%SIZE_X].y);
			window->draw(*redCross);
		}
	}
	window->display();

	while(window->isOpen())
	{
		bool update_window = false;
        sf::Event event;
        while (window->pollEvent(event))
        {
        	// Close window
            if (event.type == sf::Event::Closed)
                window->close();

            // Move cursor
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
            	if(x<SIZE_X-1) x++;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            {
            	if(x>0) x--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
            {
            	if(y>0) y--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
            {
            	if(y<SIZE_Y-1) y++;
            	update_window = true;
            }

            // Confirm choice
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter));
            	if(!player->getPkmn(SIZE_X*y + x)->isNULL())
            	{
                	return (SIZE_X*y + x);
            	}
            }

            // Go back to previous menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape));
            	return -1;
            }
        }

        if(update_window)
        {
        	drawFightingScreen();
        	drawDialogbox();
        	drawCursorAtPos(coord_cur[y][x]);
    		for(int i=0 ; i<MAX_TEAM_SIZE ; i++)
    		{
    			window->draw(*pkmns[i]);
    			Pkmn* pkmn_i = player->getPkmn(i);
    			if(pkmn_i->isKO() && !pkmn_i->isNULL())
    			{
    				redCross->setPosition( 45 + coord_cur[i/SIZE_X][i%SIZE_X].x, -10 + coord_cur[i/SIZE_X][i%SIZE_X].y);
    				window->draw(*redCross);
    			}
    		}
    		window->display();
        }

	}
	return -1;
}

Object Display_Fight::chooseObject()
{
	const int BAG_SIZE = player->getObjectBagSize();
	const int POS_X_CURSOR = 100;
	const int LINE_SPACING = 65;
	const int MAX_BAG_SIZE = 11; // Adapt this if you add more objects
	Object tab_objects[MAX_BAG_SIZE];
	int y = 0;

	// Objects
	sf::Sprite* objects[BAG_SIZE];
	float scaleX_object = 60.0 / 160;
	float scaleY_objects = 60.0 / 160;
	int index=0;
	for (const auto& [object, count] : player->getObjectBag())
	{
		if(count)
		{
			tab_objects[index] = object;
			objects[index] = getObjectSprite(object);
			objects[index]->setScale(scaleX_object, scaleY_objects);
			objects[index]->setPosition( 50 + POS_X_CURSOR, 40 + index*LINE_SPACING);
			index++;
		}
	}

	// Text
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;
	sf::Text txt_objects[BAG_SIZE];
	sf::Text txt_qty[BAG_SIZE];
	for(int i=0 ; i<BAG_SIZE ; i++)
	{
		txt_objects[i].setFont(*font);
		txt_qty[i].setFont(*font);
		txt_objects[i].setString(to_wstring.from_bytes(objectName(tab_objects[i])));
		txt_qty[i].setString("X" + std::to_string(player->getCount(tab_objects[i])));
		txt_objects[i].setCharacterSize(20);
		txt_qty[i].setCharacterSize(20);
		txt_objects[i].setFillColor(sf::Color::Black);
		txt_qty[i].setFillColor(sf::Color::Black);
		txt_objects[i].setPosition(130 + POS_X_CURSOR, 60 + i*LINE_SPACING);
		txt_qty[i].setPosition(500 + POS_X_CURSOR, 60 + i*LINE_SPACING);
	}

	// First time to have something on screen
	drawMenuBackground();
	Point cursor_pos = {POS_X_CURSOR, 50 + y*LINE_SPACING};
	drawCursorAtPos(cursor_pos);
	for(int i=0 ; i<BAG_SIZE ; i++)
	{
		window->draw(*objects[i]);
		window->draw(txt_objects[i]);
		window->draw(txt_qty[i]);
	}
	window->display();

	while(window->isOpen())
	{
		bool update_window = false;
        sf::Event event;
        while (window->pollEvent(event))
        {
        	// Close window
            if (event.type == sf::Event::Closed)
                window->close();

            // Move cursor
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
            {
            	if(y>0) y--;
            	update_window = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
            {
            	if(y<BAG_SIZE-1) y++;
            	update_window = true;
            }

            // Confirm choice
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter));
            	return tab_objects[y];
            }

            // Go back to previous menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
            {
            	while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape));
            	return NULL_OBJECT;
            }
        }

        if(update_window)
        {
        	drawMenuBackground();
        	cursor_pos = {POS_X_CURSOR, 50 + y*LINE_SPACING};
        	drawCursorAtPos(cursor_pos);
        	for(int i=0 ; i<BAG_SIZE ; i++)
        	{
        		window->draw(*objects[i]);
        		window->draw(txt_objects[i]);
        		window->draw(txt_qty[i]);
        	}
        	window->display();
        }

	}
	return NULL_OBJECT;
}

/*
 * Other methods
 */

sf::Color Display_Fight::typeColor(Type type)
{
	sf::Color color;
	switch(type)
	{
	case NULL_TYPE: color = sf::Color{ 0, 0, 0, 255 }; 			break;
	case NORMAL: 	color = sf::Color{ 168, 168, 120, 255 }; 	break;
	case FIRE: 		color = sf::Color{ 240, 128, 48, 255 }; 	break;
	case WATER: 	color = sf::Color{ 104, 144, 240, 255 }; 	break;
	case ELECTRIC: 	color = sf::Color{ 248, 208, 48, 255 }; 	break;
	case GRASS: 	color = sf::Color{ 120, 200, 80, 255 }; 	break;
	case ICE: 		color = sf::Color{ 152, 216, 216, 255 }; 	break;
	case FIGHTING: 	color = sf::Color{ 192, 48, 40, 255 }; 		break;
	case POISON: 	color = sf::Color{ 160, 64, 160, 255 }; 	break;
	case GROUND: 	color = sf::Color{ 224, 192, 104, 255 }; 	break;
	case FLYING: 	color = sf::Color{ 168, 144, 240, 255 }; 	break;
	case PSYCHIC: 	color = sf::Color{ 248, 88, 136, 255 }; 	break;
	case BUG: 		color = sf::Color{ 168, 184, 32, 255 }; 	break;
	case ROCK: 		color = sf::Color{ 184, 160, 56, 255 }; 	break;
	case GHOST: 	color = sf::Color{ 112, 88, 152, 255 }; 	break;
	case DRAGON: 	color = sf::Color{ 112, 56, 248, 255 }; 	break;
	case DARK: 		color = sf::Color{ 112, 88, 72, 255 }; 		break;
	case STEEL: 	color = sf::Color{ 184, 184, 208, 255 };	break;
	case FAIRY: 	color = sf::Color{ 238, 153, 172, 255 }; 	break;
	}
	return color;
}

std::string Display_Fight::objectName(Object object)
{
	switch(object)
	{
	case NULL_OBJECT:		return "";
	case POTION: 			return "Potion";
	case SUPER_POTION: 		return "Super Potion";
	case HYPER_POTION: 		return "Hyper Potion";
	case POTION_MAX: 		return "Potion Max";
	case ATTACK_PLUS: 		return "Attaque +";
	case DEFENSE_PLUS: 		return "Défense +";
	case SP_ATTACK_PLUS: 	return "Attaque Spe. +";
	case SP_DEFENSE_PLUS: 	return "Défense Spe. +";
	case SPEED_PLUS: 		return "Vitesse +";
	case RAPPEL: 			return "Rappel";
	case RAPPEL_MAX: 		return "Rappel Max";
	default:                return  "";
	}
}


std::string Display_Fight::statName(Stat stat)
{
	switch(stat)
	{
	case NULL_STAT: 	return "";
	case ATTACK: 		return "L'attaque";
	case DEFENSE: 		return "La défense";
	case SP_ATTACK: 	return "L'attaque spéciale";
	case SP_DEFENSE: 	return "La défense spéciale";
	case SPEED: 		return "La vitesse";
	default: 			return "";
	}
}
void Display_Fight::updateHPbarTexture(bool target)
{
	sf::Sprite* HPbar = getHPbarSprite(target);
	float ratio;  // HP/max_HP ratio
	float coef;   // coef to fix the scaling
	sf::Texture* HPbar_texture;

	if(target)
	{
		ratio = getOpponent()->getActivePkmn()->getHPratio();
	}
	else
	{
		ratio = getPlayer()->getActivePkmn()->getHPratio();
	}

	if(ratio < 0.25f)
	{
		HPbar_texture = getBaseTexture("HPbar_red.png");
		coef = 0.25;
	}
	else if(ratio < 0.5f)
	{
		HPbar_texture = getBaseTexture("HPbar_yellow.png");
		coef = 0.5;
	}
	else
	{
		HPbar_texture = getBaseTexture("HPbar_green.png");
		coef = 1;
	}
	float scaleX_HPbar = coef * ratio * (159.0f / HPbar_texture->getSize().x);
	float scaleY_HPbar = 17.0f / HPbar_texture->getSize().y;
	HPbar->setScale(scaleX_HPbar, scaleY_HPbar);
	HPbar->setTexture(*HPbar_texture);
}

std::string Display_Fight::femininObject(Object object)
{
	if(object == RAPPEL || object == RAPPEL_MAX) return "";
	return "e";
}

std::string Display_Fight::wrapText(const std::string& input, std::string pattern, std::size_t maxLineChar)
{
    std::string result;
    std::size_t lineLength = 0;
    std::size_t lastSpacePos = std::string::npos; // std::string::npos = not a valid position

    for (char c : input)
    {
        result += c;
        lineLength++;

        if (c == ' ') lastSpacePos = result.size() - 1;

        if (lineLength >= maxLineChar)
        {
            if (lastSpacePos != std::string::npos)
            {
            	result.insert(lastSpacePos + 1, pattern);
                lineLength = 0;
                lastSpacePos = std::string::npos;
            }
            else
            {
                result += pattern;
                lineLength = 0;
            }
        }
    }

    return result;
}

