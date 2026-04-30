/*
 * main.cpp
 *
 *  Created on: 12 Dec 2025
 *      Author: lucas
 */


#include "main.hpp"

extern std::unordered_map<int, Move*> existing_moves;

int main()
{

	existing_moves.emplace(0, new Move());

    sqlite3* db;
    int rc;

    rc = sqlite3_open("./data/PkmnRPG.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
    }

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/PokemonGb-RAeo.ttf")) {
        std::cerr << "Failed to load font!\n";
        return 1;
    }

    // Create a window 800x600
    sf::RenderWindow window(sf::VideoMode(800, 800), "Display");
    window.setFramerateLimit(30);

    Trainer player = Trainer(db, "Lucas");

    player.addObject(POTION, 5);
    player.addObject(RAPPEL, 3);
    player.addObject(RAPPEL_MAX, 1);
    player.addObject(SP_ATTACK_PLUS, 1);
    player.addObject(SP_DEFENSE_PLUS, 1);
    player.addObject(SPEED_PLUS, 1);
    player.addMoney(-5300);

    Map map = Map(&window, &font, &player, db);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
	            window.close();
            }
            map.handleEvent(event);
        }

        map.getDisplay()->displayMap();
    }

    window.close();
    sqlite3_close(db);

    // --- Delete all dynamically created objects ---
    // Delete all Moves
    for (const auto& [id, move] : existing_moves)
    {
    	delete move;
    }

    cout << "YOUPI (it didn't crash)" << endl;
	return 0;
}
