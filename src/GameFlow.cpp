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

	active_country = (*world)[0];
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
	coin->update();
	world->update(active_country);
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
	coin->draw();
	world->draw();
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

void GameFlow::conquerLands() {

	if (guess != coinState::IDLE && guess == coin->getCoinState()) {
		GeneralBuffer<Unit*>* selected_units = world->grid()->getSelectedUnits();
		for (size_t i = 0; i < selected_units->length(); i++)
		{
			for (size_t j = 0; j < world->settings()->getNumberCountries(); j++)
			{
				if ((*world)[j] != active_country) {
					(*world)[j]->deleteUnit((*selected_units)[i]);
				}
			}
			active_country->addUnit((*selected_units)[i]);
		}
	}
	else if (guess != coinState::IDLE && guess != coin->getCoinState()) {
		;
	}
}

void GameFlow::setGuess(coinState set_guess) {
	guess = set_guess;
}

void GameFlow::mousePressed(int x, int y, int mouse_button) {
	coin->mousePressed(x, y, mouse_button);
	world->mousePressed(x, y, mouse_button);
	switch (mouse_button)
	{
	case 0:
		if (!attack) {
			if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
				&& y > attack_button_position.y && y < attack_button_position.y + attack_button_size.y
				&& world->grid()->getSelectedUnits()->length() && guess != coinState::IDLE) {
				attack = true;
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
				world->grid()->clearSelectedLands();
			}
		}
		break;
	default:
		break;
	}
}

void GameFlow::nextTour() {
	attack = false;
	end_tour = false;
	guess = coinState::IDLE;
	tour_number++;
	world->grid()->clearSelectedLands();
	active_country = (*world)[tour_number % world->settings()->getNumberCountries()];
}

GameFlow::~GameFlow() {

}