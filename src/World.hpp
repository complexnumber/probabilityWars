#pragma once

#ifndef World_hpp
#define World_hpp

#include "ofMain.h"
#include "GameSettings.hpp"
#include "Country.hpp"
#include "Land.hpp"
#include "GeneralBuffer.hpp"
#include "GeneralBuffer.cpp"

class World {
private:
	GameSettings* game_settings;
	Country** countries;

	size_t total_lands;
	Land* lands;

	GeneralBuffer<size_t> selectable_land_ids;

	GeneralBuffer<size_t> selected_land_ids;
public:
	World();
	void setup(GameSettings* set_game_settings, Country** set_countries);
	void update();
	void draw();
	void setupLands();
	void resetWorld();

	Country* getCountry(size_t order);
	size_t getNumberCountry();

	Land* getLand(size_t id);

	size_t* getSelectedLandIDs();
	size_t getNumberSelectedLand();
	void updateLandsState(size_t id);

	void initializeSelectableLands(Country* active_country);
	void increaseSelectableLands(size_t selected_id);
	void decreaseSelectableLands(size_t unselected_id);

	void deselectLands();

	void checkPress(int x, int y);
	~World();
};

#endif /* World.hpp */
