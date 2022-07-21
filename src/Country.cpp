#include "Country.hpp"

Country::Country() {
	name = "Empty";
	color = ofColor(255, 255, 0);
}

void Country::setup(string set_name, ofColor set_color) {
	name = set_name;
	color = set_color;
}

void Country::update() {

}

void Country::draw() {

}

string Country::getName() {
	return name;
}

ofColor Country::getColor() {
	return color;
}