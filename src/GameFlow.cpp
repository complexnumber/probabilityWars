#include "GameFlow.hpp"

GameFlow::GameFlow() {
	world = NULL;
	coin = NULL;

	tour_number = 0;
	end_tour = false;

	active_country = NULL;
	attacked_country = NULL;

	attack = false;
	attack_button_color = ofColor(0, 0, 255);
	attack_button_position = ofPoint(0);
	attack_button_size = ofPoint(100, 50);

	current_tour_time = 0;
	tour_time = 20;

	guess = coinState::IDLE;
	guess_button_color = ofColor(255, 255, 255);
}

void GameFlow::setup(GameSettings* game_settings, World* set_world, Coin* set_coin) {
	world = set_world;
	coin = set_coin;

	tour_number = 1;
	end_tour = false;

	active_country = world->getCountry(0);
	attacked_country = NULL;

	attack = false;
	attack_button_color = ofColor(0, 0, 255);
	attack_button_position = ofPoint(game_settings->getSquareLength() * game_settings->getNumberColumn(), ofGetWindowHeight() * 0.75);
	attack_button_size = ofPoint(100, 50);

	current_tour_time = 0;
	tour_time = game_settings->getTourTime();

	guess = coinState::IDLE;
	guess_button_color = ofColor(255, 255, 255);
}

void GameFlow::update() {
	if (attack && !end_tour && coin->getCoinState() != coinState::ROTATING) {
		coin->tossCoin();
		end_tour = true;
	}
	if (end_tour && coin->getCoinState() != coinState::ROTATING) {
		conquerLands();
		nextTour();
	}
}

void GameFlow::draw() {
	if (attack) {
		ofSetColor(attack_button_color);
	}
	else {
		ofSetColor(0);
	}
	ofDrawRectRounded(attack_button_position, attack_button_size.x, attack_button_size.y, 10);

	if (guess == coinState::HEAD) {
		guess_button_color.setHsb(COIN_HEAD_HUE, COIN_SATURATION, COIN_BRIGHTNESS);
	}
	else if (guess == coinState::TAILS) {
		guess_button_color.setHsb(COIN_TAILS_HUE, COIN_SATURATION, COIN_BRIGHTNESS);
	}
	else {
		guess_button_color.setHsb(0, 0, 255);
	}
	ofSetColor(guess_button_color);
	ofDrawRectRounded(attack_button_position.x, attack_button_position.y + attack_button_size.y, attack_button_size.x, attack_button_size.y, 10);

	ofSetColor(0, 127, 0);
	ofDrawRectRounded(attack_button_position.x, attack_button_position.y + 2 * attack_button_size.y, attack_button_size.x, attack_button_size.y, 10);
}

void GameFlow::setAttackedCountry(Country* set_attacked_country) {
	attacked_country = set_attacked_country;
}

void GameFlow::changeActiveCountry(Country* change_active_country) {
	active_country = change_active_country;
}

void GameFlow::conquerLands() {

	if (guess != coinState::IDLE && guess == coin->getCoinState()) {
		size_t* selected_land_ids = world->getSelectedLandIDs();
		for (size_t i = 0; i < world->getNumberSelectedLand(); i++)
		{
			world->getLand(selected_land_ids[i])->setOwner(active_country);
		}
	}
	else if (guess != coinState::IDLE && guess != coin->getCoinState()) {
		;
	}
}

void GameFlow::setGuess(coinState set_guess) {
	guess = set_guess;
}

void GameFlow::checkPress(int x, int y) {
	if (!attack) {
		if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
			&& y > attack_button_position.y && y < attack_button_position.y + attack_button_size.y
			&& world->getNumberSelectedLand() && guess != coinState::IDLE) {
			attack = true;
			setAttackedCountry(world->getLand(world->getSelectedLandIDs()[0])->getOwner());
		}
		if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
			&& y > attack_button_position.y + attack_button_size.y && y < attack_button_position.y + 2 * attack_button_size.y) {
			if (guess == coinState::HEAD || guess == coinState::IDLE) {
				guess = coinState::TAILS;
			}
			else if (guess == coinState::TAILS || guess == coinState::IDLE) {
				guess = coinState::HEAD;
			}
		}
		if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
			&& y > attack_button_position.y + 2 * attack_button_size.y && y < attack_button_position.y + 3 * attack_button_size.y) {
			world->deselectLands();
		}
	}
}

void GameFlow::nextTour() {
	attack = false;
	end_tour = false;
	guess = coinState::IDLE;
	tour_number++;
	world->deselectLands();
	changeActiveCountry(world->getCountry(tour_number % world->getNumberCountry()));
}

GameFlow::~GameFlow() {

}