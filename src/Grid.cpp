#include "Grid.hpp"

Grid::Grid() {
	game_settings = NULL;

	units = NULL;

	border_units = GeneralBuffer<Unit*>();
	possible_country_center_units = GeneralBuffer<Unit*>();
	initial_country_center_units = GeneralBuffer<Unit*>();

	selectable_units = GeneralBuffer<Unit*>();
	selected_units = GeneralBuffer<Unit*>();
	selectable_country_units = GeneralBuffer<Unit*>();
	selected_country_units = GeneralBuffer<Unit*>();

	player_country = NULL;
}

void Grid::reducePossibleCountryCenterUnits(Unit* unit) {
	size_t num_col = game_settings->getNumberColumn();
	
	possible_country_center_units.reduceUniquely(units[unit->getID()]);

	possible_country_center_units.reduceUniquely(units[unit->up()]);
	possible_country_center_units.reduceUniquely(units[unit->down()]);
	possible_country_center_units.reduceUniquely(units[unit->right()]);
	possible_country_center_units.reduceUniquely(units[unit->left()]);

	possible_country_center_units.reduceUniquely(units[unit->up() - num_col]);
	possible_country_center_units.reduceUniquely(units[unit->down() + num_col]);
	possible_country_center_units.reduceUniquely(units[unit->right() + 1]);
	possible_country_center_units.reduceUniquely(units[unit->left() - 1]);

	possible_country_center_units.reduceUniquely(units[unit->up() - 1]);
	possible_country_center_units.reduceUniquely(units[unit->down() + 1]);
	possible_country_center_units.reduceUniquely(units[unit->right() - num_col]);
	possible_country_center_units.reduceUniquely(units[unit->left() + num_col]);
}

GeneralBuffer<Unit*> Grid::selectableButNotSelectedUnits() {
	if (selectable_units.length() - selected_units.length() != 0) {
		GeneralBuffer<Unit*> selectable_but_not_selected_units = GeneralBuffer<Unit*>(selectable_units.length() - selected_units.length());
		for (size_t i = 0; i < selectable_units.length(); i++)
		{
			if (!selected_units.checkItem(selectable_units[i])) {
				selectable_but_not_selected_units.insertItem(selectable_units[i]);
			}
		}
		return selectable_but_not_selected_units;
	}
	return GeneralBuffer<Unit*>();
}

GeneralBuffer<Unit*> Grid::selectableButNotSelectedCountryUnits() {
	if (selectable_country_units.length() - selected_country_units.length() != 0) {
		GeneralBuffer<Unit*> selectable_but_not_selected_country_units = GeneralBuffer<Unit*>(selectable_country_units.length() - selected_country_units.length());
		for (size_t i = 0; i < selectable_country_units.length(); i++)
		{
			if (!selected_country_units.checkItem(selectable_country_units[i])) {
				selectable_but_not_selected_country_units.insertItem(selectable_country_units[i]);
			}
		}
		return selectable_but_not_selected_country_units;
	}
	return GeneralBuffer<Unit*>();
}

void Grid::setup(GameSettings* set_game_settings) {
	game_settings = set_game_settings;
	size_t num_row = game_settings->getNumberRow();
	size_t num_col = game_settings->getNumberColumn();

	units = new Unit * [game_settings->num_units]();

	border_units = GeneralBuffer<Unit*>(2 * (num_col + num_row - 2));
	possible_country_center_units = GeneralBuffer<Unit*>((num_col - 2) * (num_row - 2));
	initial_country_center_units = GeneralBuffer<Unit*>(game_settings->getNumberCountries());

	selectable_units = GeneralBuffer<Unit*>(game_settings->num_units);
	selected_units = GeneralBuffer<Unit*>(game_settings->num_units);
	selectable_country_units = GeneralBuffer<Unit*>(game_settings->num_units);
	selected_country_units = GeneralBuffer<Unit*>(game_settings->num_units);

	for (size_t id = 0; id < game_settings->num_units; id++)
	{
		units[id] = new Unit();
		units[id]->setup(id, game_settings);
		if (units[id]->isBorder()) {
			border_units.insertItem(units[id]);
		}
		else {
			possible_country_center_units.insertItem(units[id]);
		}
	}

	for (size_t i = 0; i < game_settings->getNumberCountries(); i++)
	{
		Unit* initial_country_center_unit = possible_country_center_units[unsigned int(ofRandom(possible_country_center_units.length()))];
		initial_country_center_units.insertItem(initial_country_center_unit);
		reducePossibleCountryCenterUnits(initial_country_center_unit);
	}

	player_country = NULL;
}

void Grid::draw() {
	ofColor border_color;
	for (size_t id = 0; id < game_settings->num_units; id++)
	{
		if (selected_units.checkItem(units[id])) {
			border_color = ofColor(255);
		}
		else if (selectable_units.checkItem(units[id])) {
			border_color = ofColor(200, 0, 200);
		}
		else if (selected_country_units.checkItem(units[id])) {
			border_color = ofColor(0, 200, 200);
		}
		else if (selectable_country_units.checkItem(units[id])) {
			border_color = ofColor(0, 255, 255);
		}
		else {
			border_color = ofColor(0);
		}
		units[id]->draw(game_settings, border_color);
	}
	string text = "Selectable lands: " + to_string(selectable_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 3);
	text = "Selected lands: " + to_string(selected_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 5);
	text = "Selectable country lands: " + to_string(selectable_country_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 7);
	text = "Selected country lands: " + to_string(selected_country_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 9);
}

void Grid::reset() {
	possible_country_center_units.clear();
	initial_country_center_units.clear();

	clearSelectedLands();
	clearSelectedCountryLands();
	for (size_t id = 0; id < game_settings->num_units; id++)
	{
		delete units[id];
	}
	delete[]units;
}

Unit** Grid::getUnits() {
	return units;
}

GeneralBuffer<Unit*>* Grid::getInitialCountryCenterUnits() {
	return &initial_country_center_units;
}

GeneralBuffer<Unit*>* Grid::getSelectedUnits() {
	return &selected_units;
}

GeneralBuffer<Unit*>* Grid::getSelectedCountryUnits() {
	return &selected_country_units;
}

bool Grid::updateSelectedUnits(int x, int y) {
	for (size_t id = 0; id < game_settings->num_units; id++)
	{
		if (x > units[id]->getPosition().x && x < units[id]->getPosition().x + game_settings->getSquareLength()
			&& y > units[id]->getPosition().y && y < units[id]->getPosition().y + game_settings->getSquareLength()) {

			if (units[id]->getOwner() == player_country && selectable_country_units.checkItem(units[id])) {
				if (selected_country_units.checkItem(units[id])) {
					// Unselection
					selected_country_units.reduceUniquely(units[id]);
					selectable_country_units.clear();
					updateBaseCountrySelectableUnits();
					updateCountrySelectableUnits();
				}
				else if (selected_country_units.length() < selected_units.length() / 2 + selected_units.length() % 2) {
					// Selection
					selected_country_units.insertItem(units[id]);
					updateCountrySelectableUnits();
				}
			}
			else if (selectable_units.checkItem(units[id])) {
				if (selected_units.checkItem(units[id])) {
					// Unselection
					selected_units.reduceUniquely(units[id]);
					updateBaseSelectableUnits();
					updateSelectableUnits();
					clearSelectedCountryLands();
				}
				else if (selected_units.length() < player_country->getUnits().length() / 2 || (player_country->getUnits().length() == 1 && selected_units.length() == 0)) {
					// Selection
					selected_units.insertItem(units[id]);
					updateSelectableUnits();
					updateBaseCountrySelectableUnits();
				}
			}
			return true;
		}
	}
	return false;
}

void Grid::updateBaseSelectableUnits() {
	if (player_country != NULL) {
		selectable_units.clear();
		for (size_t i = 0; i < player_country->getUnits().length(); i++)
		{
			if (!player_country->getUnits().checkItem(units[player_country->getUnits()[i]->up()])) {
				selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->up()]);
			}
			if (!player_country->getUnits().checkItem(units[player_country->getUnits()[i]->down()])) {
				selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->down()]);
			}
			if (!player_country->getUnits().checkItem(units[player_country->getUnits()[i]->right()])) {
				selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->right()]);
			}
			if (!player_country->getUnits().checkItem(units[player_country->getUnits()[i]->left()])) {
				selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->left()]);
			}
		}
	}
}

void Grid::updateSelectableUnits() {
	for (size_t i = 0; i < selected_units.length(); i++)
	{
		selectable_units.insertItemUniquely(selected_units[i]);
		if (!player_country->getUnits().checkItem(units[selected_units[i]->up()])) {
			selectable_units.insertItemUniquely(units[selected_units[i]->up()]);
		}
		if (!player_country->getUnits().checkItem(units[selected_units[i]->down()])) {
			selectable_units.insertItemUniquely(units[selected_units[i]->down()]);
		}
		if (!player_country->getUnits().checkItem(units[selected_units[i]->right()])) {
			selectable_units.insertItemUniquely(units[selected_units[i]->right()]);
		}
		if (!player_country->getUnits().checkItem(units[selected_units[i]->left()])) {
			selectable_units.insertItemUniquely(units[selected_units[i]->left()]);
		}
	}
}

void Grid::updateBaseCountrySelectableUnits() {
	if (player_country != NULL) {
		selectable_country_units.clear();
		for (size_t i = 0; i < selected_units.length(); i++)
		{
			if (units[selected_units[i]->up()]->getOwner() == player_country) {
				selectable_country_units.insertItemUniquely(units[selected_units[i]->up()]);
			}
			if (units[selected_units[i]->down()]->getOwner() == player_country) {
				selectable_country_units.insertItemUniquely(units[selected_units[i]->down()]);
			}
			if (units[selected_units[i]->right()]->getOwner() == player_country) {
				selectable_country_units.insertItemUniquely(units[selected_units[i]->right()]);
			}
			if (units[selected_units[i]->left()]->getOwner() == player_country) {
				selectable_country_units.insertItemUniquely(units[selected_units[i]->left()]);
			}
		}
	}
}

void Grid::updateCountrySelectableUnits() {
	for (size_t i = 0; i < selected_country_units.length(); i++)
	{
		selectable_country_units.insertItemUniquely(selected_country_units[i]);
		if (units[selected_country_units[i]->up()]->getOwner() == player_country) {
			selectable_country_units.insertItemUniquely(units[selected_country_units[i]->up()]);
		}
		if (units[selected_country_units[i]->down()]->getOwner() == player_country) {
			selectable_country_units.insertItemUniquely(units[selected_country_units[i]->down()]);
		}
		if (units[selected_country_units[i]->right()]->getOwner() == player_country) {
			selectable_country_units.insertItemUniquely(units[selected_country_units[i]->right()]);
		}
		if (units[selected_country_units[i]->left()]->getOwner() == player_country) {
			selectable_country_units.insertItemUniquely(units[selected_country_units[i]->left()]);
		}
	}
}

void Grid::randomlySelectUnits() {
	if (player_country != NULL) {
		size_t num_country_units = player_country->getUnits().length();
		while (!(selected_units.length() == num_country_units / 2)) {
			GeneralBuffer<Unit*> selectable_but_not_selected_units = selectableButNotSelectedUnits();
			if (selectable_but_not_selected_units.getBuffer() != NULL) {
				selected_units.insertItem(selectable_but_not_selected_units[ofRandom(selectable_but_not_selected_units.length())]);
				updateSelectableUnits();
			}
			else {
				break;
			}
		}
		if (num_country_units == 1 && selected_units.length() == 0) {
			selected_units.insertItem(selectable_units[ofRandom(selectable_units.length())]);
			updateSelectableUnits();
		}
		updateBaseCountrySelectableUnits();
		updateCountrySelectableUnits();
	}
}

void Grid::randomlySelectCountryUnits() {
	if (player_country != NULL) {
		size_t num_selected_units = selected_units.length();
		while (!(selected_country_units.length() == num_selected_units / 2 + num_selected_units % 2)) {
			GeneralBuffer<Unit*> selectable_but_not_selected_country_units = selectableButNotSelectedCountryUnits();
			if (selectable_but_not_selected_country_units.getBuffer() != NULL) {
				selected_country_units.insertItem(selectable_but_not_selected_country_units[ofRandom(selectable_but_not_selected_country_units.length())]);
				updateCountrySelectableUnits();
			}
			else {
				break;
			}
		}
	}
}

void Grid::clearSelectedLands() {
	selected_units.clear();
	updateBaseSelectableUnits();
}

void Grid::clearSelectedCountryLands() {
	selected_country_units.clear();
	updateBaseCountrySelectableUnits();
}

void Grid::setPlayer(Country* set_player_country) {
	player_country = set_player_country;
}