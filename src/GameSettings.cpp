#include "GameSettings.hpp"

GameSettings::GameSettings() {
	num_row = 13;
	num_col = 13;
	num_units = 13 * 13;

	country_names = NULL;
	country_colors = NULL;

	max_num_countries = unsigned int((num_row + 2) / 5) * unsigned int((num_col + 2) / 5);
	num_countries = max_num_countries;

	border_scaling = 0.9;
	square_length = (ofGetWindowHeight() / num_row) * 0.7;

	coin_radius = 20;
	coin_rotation_time = 2;
	coin_num_turns = 6;

	tour_time = 20;

	font_size = 16;
	font.load("arial.ttf", font_size);
}

void GameSettings::setup(size_t set_num_row, size_t set_num_col) {
	num_row = set_num_row;
	num_col = set_num_col;
	num_units = set_num_row * set_num_col;

	max_num_countries = unsigned int((num_row + 2) / 5) * unsigned int((num_col + 2) / 5);
	square_length = (ofGetWindowHeight() / num_row) * 0.7;
}

bool GameSettings::setup(size_t set_num_row, size_t set_num_col, size_t set_num_countries) {
	num_row = set_num_row;
	num_col = set_num_col;
	num_units = set_num_row * set_num_col;

	num_countries = set_num_countries;
	max_num_countries = unsigned int((num_row + 2) / 5) * unsigned int((num_col + 2) / 5);
	if (num_countries > max_num_countries) {
		return false;
		ofResetElapsedTimeCounter();
	}
	else {
		square_length = (ofGetWindowHeight() / num_row) * 0.7;
		return true;
	}
}

void GameSettings::update() {

}

void GameSettings::draw() {

}

void GameSettings::setCountryNames(char** set_country_names) {
	country_names = set_country_names;
}

void GameSettings::setCountryNamesRandom() {
	string random_names[10] = { "Cakil", "Turkey", "Germany", "Josh", "Paul", "Italy", "USA", "Russia", "England", "France" };
	country_names = new char*[num_countries];
	for (size_t i = 0; i < num_countries; i++)
	{
		string random_name = random_names[unsigned int(ofRandom(num_countries))];
		country_names[i] = new char[random_name.length() + 1];
		random_name.copy(country_names[i], random_name.length());
		country_names[i][random_name.length()] = '\0';
	}
}

void GameSettings::setCountryColors(ofColor* set_country_colors) {
	country_colors = set_country_colors;
}

void GameSettings::setCountryColorsRandom() {
	country_colors = new ofColor[num_countries];
	ofColor color = ofColor();
	for (size_t i = 0; i < num_countries; i++)
	{
		color.setHsb(ofRandom(255), 200, 200);
		country_colors[i] = color;
	}
}

void GameSettings::setCountries(char** set_country_names, ofColor* set_country_colors) {
	setCountryNames(set_country_names);
	setCountryColors(set_country_colors);
}

void GameSettings::setCountriesRandom() {
	setCountryNamesRandom();
	setCountryColorsRandom();
}

void GameSettings::setCountryName(char* set_country_name, size_t country_id) {
	country_names[country_id] = set_country_name;
}

void GameSettings::setCountryColor(ofColor set_country_color, size_t country_id) {
	country_colors[country_id] = set_country_color;
}

void GameSettings::setCountry(char* set_country_name, ofColor set_country_color, size_t country_id) {
	setCountryName(set_country_name, country_id);
	setCountryColor(set_country_color, country_id);
}

char** GameSettings::getCountryNames() {
	return country_names;
}

ofColor* GameSettings::getCountryColors() {
	return country_colors;
}

size_t GameSettings::getNumberColumn() {
	return num_col;
}

size_t GameSettings::getNumberRow() {
	return num_row;
}

size_t GameSettings::getNumberCountries() {
	return num_countries;
}

float GameSettings::getBorderScaling() {
	return border_scaling;
}

void GameSettings::setWorldGraphics(float set_border_scaling) {
	border_scaling = set_border_scaling;
}

void GameSettings::setWorldGraphics(float set_border_scaling, float set_square_length) {
	border_scaling = set_border_scaling;
	square_length = set_square_length;
}

float GameSettings::getSquareLength() {
	return square_length;
}

void GameSettings::setCoin(float set_coin_radius, float set_coin_rotation_time, uint8_t set_coin_num_turns) {
	coin_radius = set_coin_radius;
	coin_rotation_time = set_coin_rotation_time;
	coin_num_turns = set_coin_num_turns;
}

float GameSettings::getCoinRadius() {
	return coin_radius;
}

float GameSettings::getCoinRotationTime() {
	return coin_rotation_time;
}

uint8_t GameSettings::getCoinNumberTurns() {
	return coin_num_turns;
}

void GameSettings::setTourTime(float set_tour_time) {
	tour_time = set_tour_time;
}

float GameSettings::getTourTime() {
	return tour_time;
}

ofTrueTypeFont GameSettings::getFont() {
	return font;
}

void GameSettings::setFont(string font_name, size_t set_font_size) {
	font.load(font_name, set_font_size);
}

GameSettings::~GameSettings() {
	;
}