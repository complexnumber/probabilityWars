#pragma once

#ifndef Country_hpp
#define Country_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "GeneralBuffer.hpp"
#include "Grid.hpp"
#include "Unit.hpp"

class Grid;

class Country {
private:
	char* name;
	ofColor color;

	GeneralBuffer<Unit*> units;
public:
	Country();
	void setup(GameSettings* game_settings, size_t country_id);
	void update();
	void draw();

	void establish(Grid* world_grid, size_t center_id);
	void destroy();

	char* getName();
	ofColor getColor();

	void addUnit(Unit* unit);
	void deleteUnit(Unit* unit);
	GeneralBuffer<Unit*> getUnits();
};

#endif /* Country.hpp */
