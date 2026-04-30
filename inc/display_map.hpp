//
// Created by Alex on 18/01/2026.
//

#ifndef PKMNRPG_DISPLAY_MAP_HPP
#define PKMNRPG_DISPLAY_MAP_HPP

#include <SFML/Graphics.hpp>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <vector>
#include <memory>

#include "tile.hpp"

#define SCALE_TILE  	(2.0f)
#define TILE_SIZE   	(16.0f)
#define DISPLAY_MARGIN 	(5)

typedef enum {
    UP, DOWN, LEFT, RIGHT
} orientation_t;

typedef struct {
    int x, y;
    orientation_t facing;
} player_position_t;

typedef struct {
	sf::Sprite sprite;
    int x, y;
}trainer_sprite_t ;

class Display_Map
{
private:
    sf::RenderWindow* window;
    sf::Font* font;

    std::vector<std::unique_ptr<Tile>>* map;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Sprite> player_sprites;
    std::vector<trainer_sprite_t> trainers_sprites;
    int size[2]; // (Rows, Columns)
    int* view_size; // (ylim_low, ylim_high, xlim_low, xlim_high)

    player_position_t* player_pos;

    std::unordered_map<std::string, sf::Texture> loaded_textures; // string=filename
public:
    // Constructor
    Display_Map(sf::RenderWindow* window, sf::Font* font, player_position_t* player_pos, std::vector<std::unique_ptr<Tile>>* map, int* size, int* view_size);

    // Destructor
    virtual ~Display_Map() = default;

    // Getters
    player_position_t* getPlayerPos();
	std::unordered_map<std::string, sf::Texture>* getLoadedTextures();
	sf::Texture* getBaseTexture(std::string filename); // Find base texture into unordered map or add it if not into it yet
	sf::Texture* getObjectTexture(Object object); 	  // Find object texture into unordered map or add it if not into it yet

    // Setters
    void setSize(int nrows, int ncols);
    //void setViewSize(int ylim_low, int ylim_high, int xlim_low, int xlim_high);

    // Drawing methods
    void drawTile(int idx);
    void drawPlayer();
    void drawTrainers();
    void drawMap();
	void drawMenuBackground();
	void drawCursorAtPos(Point point); // update cursor pos and draw it

    // Display methods
    void displayMap();

    // Other methods
    void generateSpriteVector();
    void updateTileSprite(int idx);
    void updateSpritesPos();
	void openShop(Trainer* player);
	std::string objectName(Object object);
	int objectPrice(Object object);
};
#endif //PKMNRPG_DISPLAY_MAP_HPP
