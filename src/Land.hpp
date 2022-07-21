#pragma once

#ifndef Land_hpp
#define Land_hpp

#include "ofMain.h"
#include "Country.hpp"
#include "GameSettings.hpp"

class Land {
private:
	Country* owner;
	size_t id;
	ofPoint square_pos;
	bool selection_status;
public:
	Land();
	void setup(Country* set_owner, size_t set_id, GameSettings* game_settings);
	bool is_initialized();
	void update();
	void draw(GameSettings* game_settings, bool selectable);
	void reset();

	void setOwner(Country* set_owner);
	Country* getOwner();

	ofPoint getPosition();

	void toggleSelectionStatus();
	bool getSelectionStatus();
};

#endif /* Land.hpp */
