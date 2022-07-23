#pragma once

#ifndef Grid_hpp
#define Grid_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "GeneralBuffer.hpp"
#include "GeneralBuffer.cpp"
#include "Country.hpp"
#include "Unit.hpp"

class Unit;

class Country;

class Grid {
private:
	GameSettings* game_settings;

	Unit** units;

	GeneralBuffer<Unit*> border_units;
	GeneralBuffer<Unit*> possible_country_center_units;
	GeneralBuffer<Unit*> initial_country_center_units;

	GeneralBuffer<Unit*> selectable_units;
	GeneralBuffer<Unit*> selected_units;

	void reducePossibleCountryCenterUnits(Unit* unit);
public:
	Grid();

	void setup(GameSettings* set_game_settings);
	void draw();
	void reset();

	Unit** getUnits();

	GeneralBuffer<Unit*>* getInitialCountryCenterUnits();

	GeneralBuffer<Unit*>* getSelectedUnits();

	void updateSelectedUnits(int x, int y);
	void updateSelectableUnits(Country* player_country);
	void clearSelectedLands();
};

#endif /* Grid.hpp */
