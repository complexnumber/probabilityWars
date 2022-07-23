#pragma once

#ifndef World_hpp
#define World_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "Country.hpp"
#include "Grid.hpp"

class World {
private:
	GameSettings* game_settings;
	Grid* world_grid;
	Country** countries;
public:
	World();
	void setup(GameSettings* set_game_settings);
	void update(Country* country);
	void draw();

	void setupCountries();
	void resetWorld();

	GameSettings* settings();
	Grid* grid();
	Country*& operator[](unsigned int index);

	void mousePressed(int x, int y, int mouse_button);
};

#endif /* World.hpp */
