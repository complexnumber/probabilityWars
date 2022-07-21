#pragma once

#ifndef GameSettings_hpp
#define GameSettings_hpp

#include "ofMain.h"

class GameSettings {
private:
	size_t num_row;
	size_t num_col;
	size_t num_countries;

	float border_scaling;
	float square_length;

	float coin_radius;
	float coin_rotation_time;
	uint8_t coin_num_turns;

	float tour_time;

	size_t font_size;
	ofTrueTypeFont font;
public:
	size_t max_num_countries;
	GameSettings();

	void setup(size_t set_num_row, size_t set_num_col);
	bool setup(size_t set_num_row, size_t set_num_col, size_t set_num_countries);
	void update();
	void draw();

	size_t getNumberColumn();
	size_t getNumberRow();
	size_t getNumberCountries();

	void setWorldGraphics(float set_border_scaling);
	void setWorldGraphics(float set_border_scaling, float set_square_length);
	float getBorderScaling();
	float getSquareLength();

	void setCoin(float set_coin_radius, float set_coin_rotation_time, uint8_t set_coin_num_turns);
	float getCoinRadius();
	float getCoinRotationTime();
	uint8_t getCoinNumberTurns();

	void setTourTime(float set_tour_time);
	float getTourTime();

	ofTrueTypeFont getFont();
	void setFont(string font_name, size_t set_font_size);

	~GameSettings();
};

#endif /* GameSettings.hpp */