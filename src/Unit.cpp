#include "Unit.hpp"

Unit::Unit() {
	owner = NULL;

	id = 0;
	x = 0;
	y = 0;

	up_id = 0;
	down_id = 0;
	right_id = 0;
	left_id = 0;

	square_pos = ofPoint(0, 0);
}

void Unit::setup(size_t set_id, GameSettings* game_settings) {
	owner = NULL;

	size_t num_col = game_settings->getNumberColumn();
	size_t num_row = game_settings->getNumberRow();
	id = set_id;
	x = id % num_col;
	y = id / num_col;

	if (y > 0) {
		up_id = id - num_col;
	}
	else {
		up_id = id;
	}

	if (y < num_row - 1) {
		down_id = id + num_col;
	}
	else {
		down_id = id;
	}

	if (x < num_col - 1) {
		right_id = id + 1;
	}
	else {
		right_id = id;
	}

	if (x > 0) {
		left_id = id - 1;
	}
	else {
		left_id = id;
	}

	square_pos = ofPoint(x * game_settings->getSquareLength(), y * game_settings->getSquareLength());
}

void Unit::draw(GameSettings* game_settings, ofColor border_color) {
	if (ofGetMouseX() > square_pos.x && ofGetMouseX() < square_pos.x + game_settings->getSquareLength()
		&& ofGetMouseY() > square_pos.y && ofGetMouseY() < square_pos.y + game_settings->getSquareLength()) {
		ofSetColor(0);
		string text = "Owner: ";
		if (owner != NULL) {
			text.append(owner->getName());
		}
		else {
			text = "Unoccupied Land";
		}
		game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text));
		ofSetColor(255, 0, 0);
		if (border_color.r == 255 && border_color.g == 255 && border_color.b == 255) {
			ofSetColor(0, 0, 255);
		}
	}
	else {
		ofSetColor(border_color);
	}
	// Draw border
	ofDrawRectangle(square_pos, game_settings->getSquareLength(), game_settings->getSquareLength());
	// Draw inside
	ofPushMatrix();
	if (owner != NULL) {
		ofSetColor(owner->getColor());
	}
	else {
		ofSetColor(200, 200, 0);
	}
	ofScale(game_settings->getBorderScaling());
	float square_x_scaled = (id % game_settings->getNumberColumn() + (1 - game_settings->getBorderScaling()) / 2) * game_settings->getSquareLength() * (1 / game_settings->getBorderScaling());
	float square_y_scaled = (id / game_settings->getNumberColumn() + (1 - game_settings->getBorderScaling()) / 2) * game_settings->getSquareLength() * (1 / game_settings->getBorderScaling());
	ofDrawRectangle(square_x_scaled, square_y_scaled, game_settings->getSquareLength(), game_settings->getSquareLength());
	ofPopMatrix();
}

void Unit::reset() {
	owner = NULL;

	id = 0;
	x = 0;
	y = 0;

	up_id = 0;
	down_id = 0;
	right_id = 0;
	left_id = 0;

	square_pos = ofPoint(0, 0);
}

void Unit::setOwner(Country* set_owner) {
	owner = set_owner;
}

Country* Unit::getOwner() {
	return owner;
}

size_t Unit::getID() {
	return id;
}

size_t Unit::getX() {
	return x;
}

size_t Unit::getY() {
	return y;
}

size_t Unit::up() {
	return up_id;
}

size_t Unit::down() {
	return down_id;
}

size_t Unit::right() {
	return right_id;
}

size_t Unit::left() {
	return left_id;
}

bool Unit::isBorder() {
	if (up() == id || down() == id || right() == id || left() == id) {
		return true;
	}
	else {
		return false;
	}
}

ofPoint Unit::getPosition() {
	return square_pos;
}