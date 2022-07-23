#include "Country.hpp"
#include "Unit.hpp"
#include "Grid.hpp"

Country::Country() {
	name = new char[2];
	name[0] = ' '; name[1] = '\0';
	color = ofColor(255, 255, 0);

	units = GeneralBuffer<Unit*>();
}

void Country::setup(GameSettings* game_settings, size_t country_id) {
	char* set_name = game_settings->getCountryNames()[country_id];
	delete[]name;
	name = set_name;
	color = game_settings->getCountryColors()[country_id];

	units = GeneralBuffer<Unit*>(game_settings->num_units);
}

void Country::update() {

}

void Country::draw() {

}

void Country::establish(Grid* world_grid, size_t center_id) {
	Unit** all_units = world_grid->getUnits();
	all_units[center_id]->setOwner(this);
	units.insertItem(all_units[center_id]);
	all_units[all_units[center_id]->up()]->setOwner(this);
	units.insertItem(all_units[all_units[center_id]->up()]);
	all_units[all_units[center_id]->down()]->setOwner(this);
	units.insertItem(all_units[all_units[center_id]->down()]);
	all_units[all_units[center_id]->right()]->setOwner(this);
	units.insertItem(all_units[all_units[center_id]->right()]);
	all_units[all_units[center_id]->left()]->setOwner(this);
	units.insertItem(all_units[all_units[center_id]->left()]);
}

void Country::destroy() {
	size_t len = units.length();
	for (size_t i = 0; i < len; i++)
	{
		deleteUnit(units[i]);
	}
}

char* Country::getName() {
	return name;
}

ofColor Country::getColor() {
	return color;
}

void Country::addUnit(Unit* unit) {
	units.insertItemUniquely(unit);
	unit->setOwner(this);
}

void Country::deleteUnit(Unit* unit) {
	units.reduceUniquely(unit);
	unit->setOwner(NULL);
}

GeneralBuffer<Unit*> Country::getUnits() {
	return units;
}