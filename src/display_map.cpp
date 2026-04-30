//
// Created by Alex on 18/01/2026.
//

#include "display_map.hpp"
#include "trainer_tile.hpp"

/*
 * Constructor
 */
Display_Map::Display_Map(sf::RenderWindow* window, sf::Font* font, player_position_t* player_pos, std::vector<std::unique_ptr<Tile>>* map, int* size, int* view_size)
{
    this->window = window;
    this-> font = font;
    this->player_pos = player_pos;
    this->map = map;
    this->size[0] = size[0];
    this->size[1] = size[1];
    this->view_size = view_size;

    // Define filenames
    std::string grass = "grass.png";
    std::string tall_grass = "tallGrass.png";
    std::string rock = "rock.png";
    std::string broken_rock = "brokenRock.png";

    std::string pokecenter1 = "PokeCenter1.png";
    std::string pokecenter2 = "PokeCenter2.png";
    std::string pokecenter3 = "PokeCenter3.png";
    std::string pokecenter4 = "PokeCenter4.png";
    std::string pokecenter5 = "PokeCenter5.png";
    std::string pokecenter6 = "PokeCenter6.png";
    std::string pokecenter7 = "PokeCenter7.png";
    std::string pokecenter8 = "PokeCenter8.png";
    std::string pokecenter9 = "PokeCenter9.png";
    std::string pokecenter10 = "PokeCenter10.png";
    std::string pokecenter11 = "PokeCenter11.png";
    std::string pokecenter12 = "PokeCenter12.png";
    std::string pokecenter13 = "PokeCenter13.png";
    std::string pokecenter14 = "PokeCenter14.png";
    std::string pokecenter15 = "PokeCenter15.png";
    std::string pokecenter16 = "PokeCenter16.png";

    std::string player_up = "playerUp.png";
    std::string player_down = "playerDown.png";
    std::string player_left = "playerLeft.png";
    std::string player_right = "playerRight.png";

    std::string trainer = "trainer1.png";

    std::string empty_texture = "empty_texture";

    // Add textures to unordered map
    loaded_textures.emplace(grass, sf::Texture{});
    loaded_textures.emplace(tall_grass, sf::Texture{});
    loaded_textures.emplace(rock, sf::Texture{});
    loaded_textures.emplace(broken_rock, sf::Texture{});

    loaded_textures.emplace(pokecenter1, sf::Texture{});
    loaded_textures.emplace(pokecenter2, sf::Texture{});
    loaded_textures.emplace(pokecenter3, sf::Texture{});
    loaded_textures.emplace(pokecenter4, sf::Texture{});
    loaded_textures.emplace(pokecenter5, sf::Texture{});
    loaded_textures.emplace(pokecenter6, sf::Texture{});
    loaded_textures.emplace(pokecenter7, sf::Texture{});
    loaded_textures.emplace(pokecenter8, sf::Texture{});
    loaded_textures.emplace(pokecenter9, sf::Texture{});
    loaded_textures.emplace(pokecenter10, sf::Texture{});
    loaded_textures.emplace(pokecenter11, sf::Texture{});
    loaded_textures.emplace(pokecenter12, sf::Texture{});
    loaded_textures.emplace(pokecenter13, sf::Texture{});
    loaded_textures.emplace(pokecenter14, sf::Texture{});
    loaded_textures.emplace(pokecenter15, sf::Texture{});
    loaded_textures.emplace(pokecenter16, sf::Texture{});

    loaded_textures.emplace(player_up, sf::Texture{});
    loaded_textures.emplace(player_down, sf::Texture{});
    loaded_textures.emplace(player_left, sf::Texture{});
    loaded_textures.emplace(player_right, sf::Texture{});

    loaded_textures.emplace(trainer, sf::Texture{});

    loaded_textures.emplace(empty_texture, sf::Texture{});



    // Load image files
    loaded_textures.at(grass).loadFromFile("./assets/sprites/map_sprites/"+grass);
    loaded_textures.at(tall_grass).loadFromFile("./assets/sprites/map_sprites/"+tall_grass);
    loaded_textures.at(rock).loadFromFile("./assets/sprites/map_sprites/"+rock);
    loaded_textures.at(broken_rock).loadFromFile("./assets/sprites/map_sprites/"+broken_rock);

    loaded_textures.at(pokecenter1).loadFromFile("./assets/sprites/map_sprites/"+pokecenter1);
    loaded_textures.at(pokecenter2).loadFromFile("./assets/sprites/map_sprites/"+pokecenter2);
    loaded_textures.at(pokecenter3).loadFromFile("./assets/sprites/map_sprites/"+pokecenter3);
    loaded_textures.at(pokecenter4).loadFromFile("./assets/sprites/map_sprites/"+pokecenter4);
    loaded_textures.at(pokecenter5).loadFromFile("./assets/sprites/map_sprites/"+pokecenter5);
    loaded_textures.at(pokecenter6).loadFromFile("./assets/sprites/map_sprites/"+pokecenter6);
    loaded_textures.at(pokecenter7).loadFromFile("./assets/sprites/map_sprites/"+pokecenter7);
    loaded_textures.at(pokecenter8).loadFromFile("./assets/sprites/map_sprites/"+pokecenter8);
    loaded_textures.at(pokecenter9).loadFromFile("./assets/sprites/map_sprites/"+pokecenter9);
    loaded_textures.at(pokecenter10).loadFromFile("./assets/sprites/map_sprites/"+pokecenter10);
    loaded_textures.at(pokecenter11).loadFromFile("./assets/sprites/map_sprites/"+pokecenter11);
    loaded_textures.at(pokecenter12).loadFromFile("./assets/sprites/map_sprites/"+pokecenter12);
    loaded_textures.at(pokecenter13).loadFromFile("./assets/sprites/map_sprites/"+pokecenter13);
    loaded_textures.at(pokecenter14).loadFromFile("./assets/sprites/map_sprites/"+pokecenter14);
    loaded_textures.at(pokecenter15).loadFromFile("./assets/sprites/map_sprites/"+pokecenter15);    
    loaded_textures.at(pokecenter16).loadFromFile("./assets/sprites/map_sprites/"+pokecenter16);


    loaded_textures.at(player_up).loadFromFile("./assets/sprites/map_sprites/"+player_up);
    loaded_textures.at(player_down).loadFromFile("./assets/sprites/map_sprites/"+player_down);
    loaded_textures.at(player_left).loadFromFile("./assets/sprites/map_sprites/"+player_left);
    loaded_textures.at(player_right).loadFromFile("./assets/sprites/map_sprites/"+player_right);

    loaded_textures.at(trainer).loadFromFile("./assets/sprites/map_sprites/"+trainer);

    sf::Image img;
    img.create(1,1, sf::Color::Transparent);
    loaded_textures.at(empty_texture).loadFromImage(img);

    // Instantiate Player & Trainers Sprites
    player_sprites.push_back(sf::Sprite(loaded_textures.at(player_up)));
    player_sprites.push_back(sf::Sprite(loaded_textures.at(player_down)));
    player_sprites.push_back(sf::Sprite(loaded_textures.at(player_left)));
    player_sprites.push_back(sf::Sprite(loaded_textures.at(player_right)));



    // Applying Scaling
    player_sprites[0].setScale(SCALE_TILE, SCALE_TILE);
    player_sprites[1].setScale(SCALE_TILE, SCALE_TILE);
    player_sprites[2].setScale(SCALE_TILE, SCALE_TILE);
    player_sprites[3].setScale(SCALE_TILE, SCALE_TILE);

}

/*
 * Getters
 */
player_position_t* Display_Map::getPlayerPos()
{
    return player_pos;
}

std::unordered_map<std::string, sf::Texture>* Display_Map::getLoadedTextures()
{
	return &loaded_textures;
}

sf::Texture* Display_Map::getBaseTexture(std::string filename)
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

sf::Texture* Display_Map::getObjectTexture(Object object)
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

/*
 * Setters
 */
void Display_Map::setSize(int nrows, int ncols)
{
    this->size[0] = nrows;
    this->size[1] = ncols;
}
/*
void Display_Map::setViewSize(int ylim_low, int ylim_high, int xlim_low, int xlim_high)
{
    this->view_size[0] = ylim_low;
    this->view_size[1] = ylim_high;
    this->view_size[2] = xlim_low;
    this->view_size[3] = xlim_high;
}*/

/*
 * Drawing methods
 */
void Display_Map::drawTile(int idx)
{
    this->window->draw(this->sprites.at(idx));
}

void Display_Map::drawPlayer()
{
	//std::cout << "Pos : (" << this->player_pos->x << ", " << this->player_pos->x << ")" << std::endl;
	int x = this->player_pos->x - this->view_size[2];
	int y = this->player_pos->y - this->view_size[0];
	this->player_sprites[this->player_pos->facing].setPosition(x * SCALE_TILE * TILE_SIZE, y * SCALE_TILE * TILE_SIZE - 3);
	this->window->draw(this->player_sprites[this->player_pos->facing]);
}

void Display_Map::drawTrainers()
{
	int x, y, idx;

	for (trainer_sprite_t trainer: this->trainers_sprites) {

		x = trainer.x - this->view_size[2];
		y = trainer.y - this->view_size[0];

		idx = trainer.y * size[1] + trainer.x;
		if (dynamic_cast<Trainer_Tile*>(this->map->at(idx).get()))
		{
			Trainer_Tile* tile = dynamic_cast<Trainer_Tile*>(this->map->at(idx).get());
			if (!tile->getTrainerKO())
			{
				trainer.sprite.setPosition(x * SCALE_TILE * TILE_SIZE, y * SCALE_TILE * TILE_SIZE - 3);
				this->window->draw(trainer.sprite);
			}
		}
	}
}

void Display_Map::drawMap()
{
//    for (int i = 0; i < this->size[0]*this->size[1]; ++i)
//    {
//        this->drawTile(i);
//    }
	int idx;
	for (int y = view_size[0]; y < view_size[1]; ++y)
	{
		for (int x = view_size[2]; x < view_size[3]; ++x)
		{
			idx = y * size[1] + x;
			this->drawTile(idx);
		}
	}
}

void Display_Map::drawMenuBackground()
{
	sf::Texture* tex_menu_bg = getBaseTexture("menu.png");
	sf::Sprite menu_bg(*tex_menu_bg);
	float scaleX_menu_bg = 800.0f / tex_menu_bg->getSize().x;
	float scaleY_menu_bg = 800.0f / tex_menu_bg->getSize().y;
	menu_bg.setScale(scaleX_menu_bg, scaleY_menu_bg);
	menu_bg.setPosition(0, 0);
	window->draw(menu_bg);
}

void Display_Map::drawCursorAtPos(Point point)
{
	std::string cursor_name = "cursor.png";
	sf::Sprite cursor;
	cursor.setTexture(*getBaseTexture(cursor_name));
	float scaleX_cursor = 50.0f / loaded_textures.at(cursor_name).getSize().x;
	float scaleY_cursor = 50.0f / loaded_textures.at(cursor_name).getSize().y;
	cursor.setScale(scaleX_cursor, scaleY_cursor);
	cursor.setPosition(point.x,point.y);
	window->draw(cursor);
}


/*
 * Display methods
 */
void Display_Map::displayMap()
{
	this->updateSpritesPos();
	this->window->clear();
    this->drawMap();
    this->drawPlayer();
    this->drawTrainers();
    this->window->display();
}

/*
 * Other methods
 */
void Display_Map::generateSpriteVector()
{
	// Tile Sprites
    int x,y;
    static int trainer_idx = 0;
    for (int i = 0; i < this->size[0]*this->size[1]; ++i)
    {
        x = i % this->size[1];
        y = i / this->size[1];

        this->sprites.push_back(sf::Sprite(this->loaded_textures.at(this->map->at(i)->getTextureName())));
        this->sprites.at(i).setScale(SCALE_TILE, SCALE_TILE);
        this->sprites.at(i).setPosition(x * SCALE_TILE * TILE_SIZE, y * SCALE_TILE * TILE_SIZE);

        if (dynamic_cast<Trainer_Tile*>(this->map->at(i).get()))
        {
        	// Is a Trainer Tile
        	Trainer_Tile* tile = dynamic_cast<Trainer_Tile*>(this->map->at(i).get());
        	trainer_sprite_t trainer= {sf::Sprite(this->loaded_textures.at(tile->getTrainerTextureName())), x, y};
        	this->trainers_sprites.push_back(trainer);
        	this->trainers_sprites.at(trainer_idx).sprite.setScale(SCALE_TILE, SCALE_TILE);
        	trainer_idx++;
        }
	}

}

void Display_Map::updateTileSprite(int idx)
{
	this->sprites.at(idx).setTexture(this->loaded_textures.at(this->map->at(idx)->getTextureName()));

	int x = idx % this->size[1];
	int y = idx / this->size[1];
	if (dynamic_cast<Trainer_Tile*>(this->map->at(idx).get()))
	{
		Trainer_Tile* tile = dynamic_cast<Trainer_Tile*>(this->map->at(idx).get());
		for (trainer_sprite_t trainer_sprite: this->trainers_sprites) {
			if (trainer_sprite.x == x && trainer_sprite.y == y)
			{
				trainer_sprite.sprite.setTexture(this->loaded_textures.at(tile->getTrainerTextureName()));
			}
		}
	}
}

void Display_Map::updateSpritesPos()
{
	int x,y;
	for (int i = 0; i < this->size[0]*this->size[1]; ++i)
	{
		x = i % this->size[1];
		y = i / this->size[1];

		this->sprites.at(i).setPosition((x - this->view_size[2]) * SCALE_TILE * TILE_SIZE, (y - this->view_size[0]) * SCALE_TILE * TILE_SIZE);
	}
}

void Display_Map::openShop(Trainer* player)
{
	const int POS_X_CURSOR = 50;
	const int LINE_SPACING = 65;
	const int MAX_BAG_SIZE = 11; // Adapt this if you add more objects
	Object tab_objects[MAX_BAG_SIZE];
	int y = 0;

	// Objects
	sf::Sprite objects[MAX_BAG_SIZE];
	float scaleX_object = 60.0 / 160;
	float scaleY_objects = 60.0 / 160;
	for(int i = 1; i < static_cast<int>(MAX_BAG_SIZE+1); i++)
	{
			tab_objects[i-1] = static_cast<Object>(i);
			objects[i-1].setTexture(*getObjectTexture(tab_objects[i-1]));
			objects[i-1].setScale(scaleX_object, scaleY_objects);
			objects[i-1].setPosition( 30 + POS_X_CURSOR, 60 + (i-1)*LINE_SPACING);
	}

	// Text
	std::wstring_convert<std::codecvt_utf8<wchar_t>> to_wstring;

	sf::Text txt_sac;
	txt_sac.setFont(*font);
	txt_sac.setString("Sac:");
	txt_sac.setCharacterSize(20);
	txt_sac.setFillColor(sf::Color::Black);
	txt_sac.setPosition(430 + POS_X_CURSOR, 30);

	sf::Text txt_prix;
	txt_prix.setFont(*font);
	txt_prix.setString("Prix:");
	txt_prix.setCharacterSize(20);
	txt_prix.setFillColor(sf::Color::Black);
	txt_prix.setPosition(600 + POS_X_CURSOR, 30);

	sf::Text txt_player_money;
	txt_player_money.setFont(*font);
	txt_player_money.setString(to_wstring.from_bytes("Thune: " + std::to_string(player->getMoney()) + "$"));
	txt_player_money.setCharacterSize(20);
	txt_player_money.setFillColor(sf::Color::Black);
	txt_player_money.setPosition( 50, 30);

	sf::Text txt_objects[MAX_BAG_SIZE];
	sf::Text txt_qty[MAX_BAG_SIZE];
	sf::Text txt_price[MAX_BAG_SIZE];
	for(int i=0 ; i<MAX_BAG_SIZE ; i++)
	{
		txt_objects[i].setFont(*font);
		txt_qty[i].setFont(*font);
		txt_price[i].setFont(*font);
		txt_objects[i].setString(to_wstring.from_bytes(objectName(tab_objects[i])));
		txt_qty[i].setString("X" + std::to_string(player->getCount(tab_objects[i])));
		txt_price[i].setString(std::to_string(objectPrice(tab_objects[i]))+"$");
		txt_objects[i].setCharacterSize(20);
		txt_qty[i].setCharacterSize(20);
		txt_price[i].setCharacterSize(20);
		txt_objects[i].setFillColor(sf::Color::Black);
		txt_qty[i].setFillColor(sf::Color::Black);
		txt_price[i].setFillColor(sf::Color::Black);
		txt_objects[i].setPosition(110 + POS_X_CURSOR, 80 + i*LINE_SPACING);
		txt_qty[i].setPosition(450 + POS_X_CURSOR, 80 + i*LINE_SPACING);
		txt_price[i].setPosition(600 + POS_X_CURSOR, 80 + i*LINE_SPACING);
	}

	// First time to have something on screen
	drawMenuBackground();
	Point cursor_pos = {POS_X_CURSOR, 70 + y*LINE_SPACING};
	drawCursorAtPos(cursor_pos);
	window->draw(txt_sac);
	window->draw(txt_prix);
	for(int i=0 ; i<MAX_BAG_SIZE ; i++)
	{
		window->draw(objects[i]);
		window->draw(txt_objects[i]);
		window->draw(txt_qty[i]);
		window->draw(txt_price[i]);
		window->draw(txt_player_money);
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
				if(y<MAX_BAG_SIZE-1) y++;
				update_window = true;
			}

			// Confirm choice
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
			{
				while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter));
				Object object = tab_objects[y];
				int price = objectPrice(object);
				if(player->getMoney() >= price)
				{
					player->addMoney(-price);
					player->addObject(object);
					update_window = true;
				}

			}

			// Go back to previous menu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
			{
				while(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape));
				return;
			}
		}

		if(update_window)
		{
			drawMenuBackground();
			cursor_pos = {POS_X_CURSOR, 70 + y*LINE_SPACING};
			drawCursorAtPos(cursor_pos);
			window->draw(txt_sac);
			window->draw(txt_prix);
			for(int i=0 ; i<MAX_BAG_SIZE ; i++)
			{
				window->draw(objects[i]);
				window->draw(txt_objects[i]);
				txt_qty[i].setString("X" + std::to_string(player->getCount(tab_objects[i])));
				window->draw(txt_qty[i]);
				window->draw(txt_price[i]);
				txt_player_money.setString(to_wstring.from_bytes("Thune: " + std::to_string(player->getMoney()) + "$"));
				window->draw(txt_player_money);
			}
			window->display();
		}

	}
}

std::string Display_Map::objectName(Object object)
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

int Display_Map::objectPrice(Object object)
{
	switch(object)
	{
	case NULL_OBJECT:		return 0;
	case POTION: 			return 300;
	case SUPER_POTION: 		return 700;
	case HYPER_POTION: 		return 1200;
	case POTION_MAX: 		return 2500;
	case ATTACK_PLUS: 		return 500;
	case DEFENSE_PLUS: 		return 500;
	case SP_ATTACK_PLUS: 	return 500;
	case SP_DEFENSE_PLUS: 	return 500;
	case SPEED_PLUS: 		return 500;
	case RAPPEL: 			return 1500;
	case RAPPEL_MAX: 		return 5000;
	default:                return 0;
	}
}





