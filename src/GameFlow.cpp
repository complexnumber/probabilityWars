#include "GameFlow.hpp"

GameFlow::GameFlow() {
	world = NULL;
	coin = NULL;

	tour_number = 0;
	turn_counter = 0;
	end_tour = false;

	active_country = NULL;
	attacked_country = NULL;

	attack = false;
	attack_button_color = ofColor(0, 0, 255);
	attack_button_position = ofPoint(0);
	attack_button_size = ofPoint(100, 50);

	tour_start_time = 0;
	tour_time_limit = 20;

	guess = coinState::IDLE;
	guess_button_color = ofColor(255, 255, 255);
}

void GameFlow::setup(GameSettings* game_settings, World* set_world, Coin* set_coin) {
	world = set_world;
	coin = set_coin;

	tour_number = 1;
	turn_counter = 0;
	end_tour = false;

	active_country = (*world)[turn_counter];
	attacked_country = NULL; // not implemented

	attack = false;
	attack_button_color = ofColor(0, 0, 255);
	attack_button_position = ofPoint(game_settings->getSquareLength() * game_settings->getNumberColumn(), ofGetWindowHeight() * 0.65);
	attack_button_size = ofPoint(100, 50);

	tour_start_time = 0;
	tour_time_limit = game_settings->getTourTimeLimit();

	guess = coinState::IDLE;
	guess_button_color = ofColor(255, 255, 255);

	world->grid()->setPlayer(active_country);
	world->updateUnits();
}

void GameFlow::update() {
	coin->update();
	if (attack && !end_tour && coin->getCoinState() != coinState::ROTATING) {
		coin->tossCoin();
		end_tour = true;
		tour_start_time = tour_start_time + world->settings()->getCoinRotationTime() + 1;
	}
	if (ofGetElapsedTimef() - tour_start_time > tour_time_limit) {
		nextTour();
		end_tour = false;
	}
	if (end_tour && coin->getCoinState() != coinState::ROTATING) {
		conquerLands();
		nextTour();
		end_tour = false;
	}
}

void GameFlow::draw(GameSettings* game_settings) {
	coin->draw();
	world->draw();

	ofSetColor(0);
	string text = "Remaining time: " + to_string(int(tour_time_limit - ofGetElapsedTimef() + tour_start_time));
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text)*5.5);

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

	ofSetColor(255, 255, 0);
	ofDrawRectRounded(attack_button_position.x, attack_button_position.y + 3 * attack_button_size.y, attack_button_size.x, attack_button_size.y, 10);
}

void GameFlow::setAttackedCountry(Country* set_attacked_country) {
	attacked_country = set_attacked_country;
} // not implemented

void GameFlow::conquerLands() {

	if (guess != coinState::IDLE && guess == coin->getCoinState()) {
		GeneralBuffer<Unit*>* selected_units = world->grid()->getSelectedUnits();
		for (size_t i = 0; i < selected_units->length(); i++)
		{
			for (size_t j = 0; j < world->numberOfCountries(); j++)
			{
				if ((*world)[j] != active_country) {
					(*world)[j]->deleteUnit((*selected_units)[i]);
				}
			}
			active_country->addUnit((*selected_units)[i]);
		}
	}
	else if (guess != coinState::IDLE && guess != coin->getCoinState()) {
		GeneralBuffer<Unit*>* selected_country_units = world->grid()->getSelectedCountryUnits();
		for (size_t i = 0; i < selected_country_units->length(); i++)
		{
			active_country->deleteUnit((*selected_country_units)[i]);
		}
	}
}

void GameFlow::setGuess(coinState set_guess) {
	guess = set_guess;
}

bool GameFlow::mousePressed(int x, int y, int mouse_button) {
	if (!coin->mousePressed(x, y, mouse_button) && !world->mousePressed(x, y, mouse_button)) {
		switch (mouse_button)
		{
		case 0:
			if (!attack) {
				Grid* world_grid = world->grid();
				size_t a = world_grid->getSelectedUnits()->length();
				size_t b = world_grid->getSelectedCountryUnits()->length();
				if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
					&& y > attack_button_position.y && y < attack_button_position.y + attack_button_size.y) {
					if (a && (b == a / 2 + a % 2 || (active_country->getUnits().length() == 1 && a == 1 && b == 1)) && guess != coinState::IDLE) {
						attack = true;
					}
					return true;
				}
				else if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
					&& y > attack_button_position.y + attack_button_size.y && y < attack_button_position.y + 2 * attack_button_size.y) {
					if (guess == coinState::HEAD || guess == coinState::IDLE) {
						guess = coinState::TAILS;
					}
					else if (guess == coinState::TAILS || guess == coinState::IDLE) {
						guess = coinState::HEAD;
					}
					return true;
				}
				else if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
					&& y > attack_button_position.y + 2 * attack_button_size.y && y < attack_button_position.y + 3 * attack_button_size.y) {
					world_grid->clearSelectedLands();
					world_grid->clearSelectedCountryLands();
					return true;
				}
				else if (x > attack_button_position.x && x < attack_button_position.x + attack_button_size.x
					&& y > attack_button_position.y + 3 * attack_button_size.y && y < attack_button_position.y + 4 * attack_button_size.y) {
					world_grid->clearSelectedLands();
					world_grid->clearSelectedCountryLands();
					world_grid->randomlySelectUnits();
					world_grid->randomlySelectCountryUnits();
					return true;
				}
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	return true;
}

void GameFlow::nextTour() {
	attack = false;
	guess = coinState::IDLE;
	tour_number++;
	world->grid()->clearSelectedLands();
	world->grid()->clearSelectedCountryLands();
	if (world->numberOfCountries()) {
		if (!world->checkCountryDestruction()) {
			turn_counter++;
			turn_counter = turn_counter % world->numberOfCountries();
		}
		else if (turn_counter == world->numberOfCountries()) {
			turn_counter = 0;
		}
	}
	if (world->numberOfCountries()) active_country = (*world)[turn_counter]; else active_country = NULL;
	world->grid()->setPlayer(active_country);
	world->updateUnits();
	resetTourTimer();
}

void GameFlow::resetTourTimer() {
	tour_start_time = ofGetElapsedTimef();
}