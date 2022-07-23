#pragma once

#ifndef Unit_hpp
#define Unit_hpp

#include "ofMain.h"
#include "GameSettings.hpp"

class Country;

class Unit {
private:
	Country* owner;

	size_t id;
	size_t x;
	size_t y;

	size_t up_id;
	size_t down_id;
	size_t right_id;
	size_t left_id;

	ofPoint square_pos;
public:
	Unit();

	void setup(size_t set_id, GameSettings* game_settings);
	void draw(GameSettings* game_settings, ofColor border_color);
	void reset();

	void setOwner(Country* set_owner);
	Country* getOwner();

	size_t getID();
	size_t getX();
	size_t getY();

	size_t up();
	size_t down();
	size_t right();
	size_t left();

	bool isBorder();

	ofPoint getPosition();
};

#endif /* Unit.hpp */
