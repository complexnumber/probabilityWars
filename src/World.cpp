#include "World.hpp"

World::World() {
	game_settings = NULL;
	world_grid = NULL;
	countries = NULL;
}

void World::setup(GameSettings* set_game_settings) {
	game_settings = set_game_settings;
	world_grid = new Grid();
	world_grid->setup(game_settings);
	game_settings->setCountriesRandom();
	setupCountries();
}

void World::update(Country* country) {
	world_grid->updateSelectableUnits(country);
}

void World::draw() {
	world_grid->draw();
}

void World::setupCountries() {
	// Establish countries on lands
	size_t num_countries = game_settings->getNumberCountries();
	countries = new Country * [num_countries]();
	for (size_t id = 0; id < num_countries; id++)
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

GameSettings* World::settings() {
	return game_settings;
}

Grid* World::grid() {
	return world_grid;
}

Country*& World::operator[](unsigned int index) {
	return countries[index];
}

void World::mousePressed(int x, int y, int mouse_button) {
	switch (mouse_button)
	{
	case 0:
		world_grid->updateSelectedUnits(x, y);
		break;
	default:
		break;
	}
}