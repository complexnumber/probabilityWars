#pragma once

#ifndef Country_hpp
#define Country_hpp

#include "ofMain.h"

class Country {
private:
	string name;
	ofColor color;
public:
	Country();
	void setup(string set_name, ofColor set_color);
	void update();
	void draw();

	string getName();
	ofColor getColor();
};

#endif /* Country.hpp */
