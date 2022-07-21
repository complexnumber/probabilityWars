#include "Land.hpp"

Land::Land() {
	owner = NULL;
	id = 0;
	square_pos = ofPoint(0, 0);
	selection_status = false;
}

void Land::setup(Country* set_owner, size_t set_id, GameSettings* game_settings) {
	owner = set_owner;
	id = set_id;
	square_pos = ofPoint((id % game_settings->getNumberColumn()) * game_settings->getSquareLength(), (id / game_settings->getNumberColumn()) * game_settings->getSquareLength());
	selection_status = false;
}

bool Land::is_initialized() {
	if (owner == NULL) return false; else return true;
}

void Land::update() {

}

void Land::draw(GameSettings* game_settings, bool selectable) {
	if (ofGetMouseX() > square_pos.x && ofGetMouseX() < square_pos.x + game_settings->getSquareLength()
		&& ofGetMouseY() > square_pos.y && ofGetMouseY() < square_pos.y + game_settings->getSquareLength()) {
		ofSetColor(0);
		string text = "Owner: " + owner->getName();
		game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text));
		if (selection_status) {
			ofSetColor(0, 0, 255);
		}
		else {
			ofSetColor(255, 0, 0);
		}
	}
	else if (selection_status) {
		ofSetColor(255);
	}
	else if (selectable) {
		ofSetColor(255, 0, 255);
	}
	else if (!selection_status) {
		ofSetColor(0);
	}
	ofDrawRectangle(square_pos, game_settings->getSquareLength(), game_settings->getSquareLength());
	ofPushMatrix();
	ofSetColor(owner->getColor());
	ofScale(game_settings->getBorderScaling());
	float square_x_scaled = (id % game_settings->getNumberColumn() + (1 - game_settings->getBorderScaling()) / 2) * game_settings->getSquareLength() * (1 / game_settings->getBorderScaling());
	float square_y_scaled = (id / game_settings->getNumberColumn() + (1 - game_settings->getBorderScaling()) / 2) * game_settings->getSquareLength() * (1 / game_settings->getBorderScaling());
	ofDrawRectangle(square_x_scaled, square_y_scaled, game_settings->getSquareLength(), game_settings->getSquareLength());
	ofPopMatrix();
}

void Land::reset() {
	owner = NULL;
	id = 0;
	square_pos = ofPoint(0, 0);
	selection_status = false;
}

void Land::setOwner(Country* set_owner) {
	owner = set_owner;
}

Country* Land::getOwner() {
	return owner;
}

ofPoint Land::getPosition() {
	return square_pos;
}

void Land::toggleSelectionStatus() {
	selection_status = !selection_status;
}

bool Land::getSelectionStatus() {
	return selection_status;
}