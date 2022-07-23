#pragma once

#ifndef GameFlow_hpp
#define GameFlow_hpp

#include "ofMain.h"
#include "World.hpp"
#include "Coin.hpp"
#include "Country.hpp"

class GameFlow {
private:
	World* world;
	Coin* coin;

	size_t tour_number;
	bool end_tour;

	Country* active_country;
	Country* attacked_country; // not implemented // Ülkeler elenmeli

	bool attack;
	ofColor attack_button_color;
	ofPoint attack_button_position;
	ofPoint attack_button_size;

	float current_tour_time; // not implemented
	float tour_time; // not implemented

	coinState guess;
	ofColor guess_button_color;
public:
	GameFlow();
	void setup(GameSettings* game_settings, World* set_world, Coin* set_coin);
	void update();
	void draw();

	void setAttackedCountry(Country* set_attacked_country);

	void conquerLands();

	void setGuess(coinState set_guess);

	void mousePressed(int x, int y, int mouse_button);
	void nextTour();
	~GameFlow();
};

#endif /* GameFlow.hpp */
