#include "World.hpp"

World::World() {
	game_settings = NULL;
	world_grid = NULL;
	countries = GeneralBuffer<Country*>();
}

void World::setup(GameSettings* set_game_settings) {
	game_settings = set_game_settings;
	world_grid = new Grid();
	world_grid->setup(game_settings);
	game_settings->setCountriesRandom();
	setupCountries();
}

void World::update() {
}

void World::updateUnits() {
	world_grid->updateBaseSelectableUnits();
	world_grid->updateBaseCountrySelectableUnits();
}

void World::draw() {
	world_grid->draw();
}

void World::setupCountries() {
	// Establish countries on lands
	size_t num_countries = game_settings->getNumberCountries();
	countries = GeneralBuffer<Country*>(num_countries);
	for (size_t id = 0; id < num_countries; id++)
	{
		countries.insertItem(new Country());
		countries[id]->setup(game_settings, id);
		countries[id]->establish(world_grid, (*(world_grid->getInitialCountryCenterUnits()))[id]->getID());
	}
}

bool World::checkCountryDestruction() {
	for (size_t id = 0; id < countries.length(); id++)
	{
		if (!countries[id]->getUnits().length()) {
			countries[id]->destroy();
			delete countries[id];
			countries.reduceShiftList(id);
			return true;
		}
	}
	return false;
}

void World::resetWorld() {
	world_grid->reset();
	while (countries.length()) {
		countries[countries.length() - 1]->destroy();
		delete countries[countries.length() - 1];
		countries.reduceShiftList(countries.length() - 1);
	}
}

GameSettings* World::settings() {
	return game_settings;
}

Grid* World::grid() {
	return world_grid;
}

size_t World::numberOfCountries() {
	return countries.length();
}

Country*& World::operator[](unsigned int index) {
	return countries[index];
}

bool World::mousePressed(int x, int y, int mouse_button) {
	switch (mouse_button)
	{
	case 0:
		if (world_grid->updateSelectedUnits(x, y)) return true;
		return false;
		break;
	default:
		return false;
		break;
	}
}