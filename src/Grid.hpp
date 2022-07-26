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
	GeneralBuffer<Unit*> selectable_country_units;
	GeneralBuffer<Unit*> selected_country_units;

	Country* player_country;

	void reducePossibleCountryCenterUnits(Unit* unit);
	GeneralBuffer<Unit*> selectableButNotSelectedUnits();
	GeneralBuffer<Unit*> selectableButNotSelectedCountryUnits();
public:
	Grid();

	void setup(GameSettings* set_game_settings);
	void draw();
	void reset();

	Unit** getUnits();

	GeneralBuffer<Unit*>* getInitialCountryCenterUnits();

	GeneralBuffer<Unit*>* getSelectedUnits();
	GeneralBuffer<Unit*>* getSelectedCountryUnits();

	bool updateSelectedUnits(int x, int y);
	void updateBaseSelectableUnits();
	void updateSelectableUnits();
	void updateBaseCountrySelectableUnits();
	void updateCountrySelectableUnits();

	void randomlySelectUnits();
	void randomlySelectCountryUnits();

	void clearSelectedLands();
	void clearSelectedCountryLands();

	void setPlayer(Country* set_player_country);
};

#endif /* Grid.hpp */
