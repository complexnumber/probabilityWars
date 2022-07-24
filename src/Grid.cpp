#include "Grid.hpp"

Grid::Grid() {
	game_settings = NULL;

	units = NULL;

	border_units = GeneralBuffer<Unit*>();
	possible_country_center_units = GeneralBuffer<Unit*>();
	initial_country_center_units = GeneralBuffer<Unit*>();

	selectable_units = GeneralBuffer<Unit*>();
	selected_units = GeneralBuffer<Unit*>();
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
		else {
			border_color = ofColor(0);
		}
		units[id]->draw(game_settings, border_color);
	}
	string text = "Selected lands:" + to_string(selected_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 3);
	text = "Selectable lands:" + to_string(selectable_units.length());
	ofSetColor(0);
	game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 5);
}

void Grid::reset() {
	possible_country_center_units.clear();
	initial_country_center_units.clear();

	selectable_units.clear();
	selected_units.clear();
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

void Grid::updateSelectedUnits(int x, int y, Country* player_country) {
	for (size_t id = 0; id < game_settings->num_units; id++)
	{
		if (x > units[id]->getPosition().x && x < units[id]->getPosition().x + game_settings->getSquareLength()
			&& y > units[id]->getPosition().y && y < units[id]->getPosition().y + game_settings->getSquareLength()
			&& selectable_units.checkItem(units[id])) {
			if (!selected_units.insertItemUniquely(units[id])) {
				selected_units.reduceUniquely(units[id]);
				selectable_units.clear();
				updateBaseSelectableUnits(player_country);
			}
			updateOutsideSelectableUnits();
			break;
		}
	}
}

void Grid::updateBaseSelectableUnits(Country* player_country) {
	selectable_units.clear();
	for (size_t i = 0; i < player_country->getUnits().length(); i++)
	{
		selectable_units.insertItemUniquely(player_country->getUnits()[i]);
		selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->up()]);
		selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->down()]);
		selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->right()]);
		selectable_units.insertItemUniquely(units[player_country->getUnits()[i]->left()]);
	}
}

void Grid::updateOutsideSelectableUnits() {
	for (size_t i = 0; i < selected_units.length(); i++)
	{
		selectable_units.insertItemUniquely(selected_units[i]);
		selectable_units.insertItemUniquely(units[selected_units[i]->up()]);
		selectable_units.insertItemUniquely(units[selected_units[i]->down()]);
		selectable_units.insertItemUniquely(units[selected_units[i]->right()]);
		selectable_units.insertItemUniquely(units[selected_units[i]->left()]);
	}
}

void Grid::clearSelectedLands() {
	selected_units.clear();
}