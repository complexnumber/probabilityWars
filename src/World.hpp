#pragma once

#ifndef World_hpp
#define World_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "Country.hpp"
#include "Grid.hpp"
#include "GeneralBuffer.hpp"
#include "GeneralBuffer.cpp"

class World {
private:
	GameSettings* game_settings;
	Grid* world_grid;
	Country** countries;
public:
	World();
	void setup(GameSettings* set_game_settings);
	void update();
	void draw();

	void setupCountries();
	void resetWorld();

	Country* getCountry(size_t order);
	size_t getNumberCountry();

	Grid* getGrid();
};

#endif /* World.hpp */
