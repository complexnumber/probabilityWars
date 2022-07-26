#pragma once

#ifndef World_hpp
#define World_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "GeneralBuffer.hpp"
#include "Country.hpp"
#include "Grid.hpp"

class World {
private:
	GameSettings* game_settings;
	Grid* world_grid;
	GeneralBuffer<Country*> countries;
public:
	World();
	void setup(GameSettings* set_game_settings);
	void update();
	void updateUnits();
	void draw();
	void resetWorld();

	void setupCountries();
	bool checkCountryDestruction();

	GameSettings* settings();
	Grid* grid();
	size_t numberOfCountries();
	Country*& operator[](unsigned int index);

	bool mousePressed(int x, int y, int mouse_button);
};

#endif /* World.hpp */
