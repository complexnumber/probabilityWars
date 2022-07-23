#include "World.hpp"

World::World() {
	game_settings = NULL;
	world_grid = NULL;
	countries = NULL;
}

void World::setup(GameSettings* set_game_settings) {
	game_settings = set_game_settings;
	world_grid = new Grid();
	setupCountries();
}

void World::update() {
	world_grid->updateSelectableUnits(countries[0]);
}

void World::draw() {
	world_grid->draw();
}

void World::setupCountries() {
	world_grid->setup(game_settings);
	game_settings->setCountriesRandom();
	// Establish countries on lands
	countries = new Country * [game_settings->getNumberCountries()]();
	for (size_t id = 0; id < game_settings->getNumberCountries(); id++)
	{
		countries[id] = new Country();
		countries[id]->setup(game_settings, id);
		countries[id]->establish(world_grid, (*(world_grid->getInitialCountryCenterUnits()))[id]->getID());
	}
}

void World::resetWorld() {
	for (size_t i = 0; i < game_settings->getNumberCountries(); i++)
	{
		countries[i]->destroy();
		delete countries[i];
	}
	delete[]countries;
	world_grid->reset();
}

Country* World::getCountry(size_t order) {
	return countries[order];
}

size_t World::getNumberCountry() {
	return game_settings->getNumberCountries();
}

Grid* World::getGrid() {
	return world_grid;
}