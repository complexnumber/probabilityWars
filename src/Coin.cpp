#include "Coin.hpp"

Coin::Coin() {
	coin_position = ofPoint(0);
	coin_radius = 20;
	coin_color = ofColor(255);
	coin_state = coinState::IDLE;
	rotation_time = 2;
	toss_time = 0;
	num_turns = 4;
}

void Coin::setup(GameSettings* game_settings) {
	coin_radius = game_settings->getCoinRadius();
	coin_position = ofPoint(game_settings->getSquareLength() * game_settings->getNumberColumn() + coin_radius, ofGetWindowHeight() / 2);
	coin_color = ofColor(255);
	coin_state = coinState::IDLE;
	rotation_time = game_settings->getCoinRotationTime();
	toss_time = 0;
	num_turns = game_settings->getCoinNumberTurns();
}

void Coin::update() {
	switch (coin_state)
	{
		case coinState::HEAD: {
			coin_color.setHsb(COIN_HEAD_HUE, COIN_SATURATION, COIN_BRIGHTNESS);
			break;
		}
		case coinState::TAILS: {
			coin_color.setHsb(COIN_TAILS_HUE, COIN_SATURATION, COIN_BRIGHTNESS);
			break;
		}
		case coinState::PERP: {
			coin_color.setHsb(0, 0, 0);
			break;
		}
		case coinState::ROTATING: {
			coin_color.setHsb(ofRandom(256), COIN_SATURATION, COIN_BRIGHTNESS);
			if (ofGetElapsedTimef() - toss_time > rotation_time) {
				float toss = ofRandom(1);
				if (toss < 0.5) {
					coin_state = coinState::HEAD;
				}
				else if (toss > 0.5) {
					coin_state = coinState::TAILS;
				}
				else {
					coin_state = coinState::PERP;
				}
			}
			break;
		}
		case coinState::IDLE: {
			coin_color.setHsb(0, 0, 255);
			break;
		}
			break;
		default:
			break;
	}
}

void Coin::draw() {
	ofPushMatrix();
	ofSetColor(coin_color);
	ofTranslate(coin_position);
	switch (coin_state)
	{
		case coinState::HEAD:
			break;
		case coinState::TAILS:
			break;
		case coinState::PERP:
			ofRotateYDeg(90);
			break;
		case coinState::ROTATING:
			ofRotateYDeg((num_turns / rotation_time) * 360 *(ofGetElapsedTimef() - toss_time));
			break;
		case coinState::IDLE:
			break;
		default:
			break;
	}
	ofDrawCircle(0, 0, coin_radius);
	ofPopMatrix();
}

bool Coin::mousePressed(int x, int y, int mouse_button) {
	switch (mouse_button)
	{
	case 0:
		if (x > coin_position.x - coin_radius && x < coin_position.x + coin_radius
			&& y > coin_position.y - coin_radius && y < coin_position.y + coin_radius) {
			if (coin_state != coinState::ROTATING) tossCoin();
			return true;
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}

void Coin::tossCoin() {
	coin_state = coinState::ROTATING;
	toss_time = ofGetElapsedTimef();
}

coinState Coin::getCoinState() {
	return coin_state;
}