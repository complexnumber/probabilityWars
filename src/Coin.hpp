#pragma once

#ifndef Coin_hpp
#define Coin_hpp

#include "ofMain.h"
#include "GameSettings.hpp"

constexpr auto COIN_SATURATION = 200;
constexpr auto COIN_BRIGHTNESS = 200;

constexpr auto COIN_HEAD_HUE = 255;
constexpr auto COIN_TAILS_HUE = 127;

enum class coinState { HEAD, TAILS, PERP, ROTATING, IDLE };

class Coin {
private:
	ofPoint coin_position;
	float coin_radius;
	ofColor coin_color;

	coinState coin_state;

	float toss_time;
	float rotation_time;
	uint8_t num_turns;
public:
	Coin();
	void setup(GameSettings* game_settings);
	void update();
	void draw();

	bool mousePressed(int x, int y, int mouse_button);

	coinState getCoinState();

	void tossCoin();
};

#endif /* Coin.hpp */
