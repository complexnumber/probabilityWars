#include "World.hpp"

World::World() {
	game_settings = NULL;
	countries = NULL;
	total_lands = 0;
	lands = NULL;
	selectable_land_ids = GeneralBuffer<size_t>();
	selected_land_ids = GeneralBuffer<size_t>();
}

void World::setup(GameSettings* set_game_settings, Country** set_countries) {
	game_settings = set_game_settings;
	countries = set_countries;
	total_lands = game_settings->getNumberColumn() * game_settings->getNumberRow();
	lands = new Land[total_lands];
	selectable_land_ids = GeneralBuffer<size_t>(total_lands);
	selected_land_ids = GeneralBuffer<size_t>(total_lands);
	setupLands();
	initializeSelectableLands(countries[0]);
}

void World::update() {

}

void World::draw() {
	if (lands != NULL) {
		for (size_t id = 0; id < total_lands; id++)
		{
			bool selectable = false;
			for (size_t i = 0; i < selectable_land_ids.length(); i++)
			{
				if (selectable_land_ids.getItem(i) == id) {
					selectable = true;
					break;
				}
			}
			lands[id].draw(game_settings, selectable);
		}
		string text = "Selected lands:" + to_string(selected_land_ids.length());
		ofSetColor(0);
		game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 3);
		text = "Selectable lands:" + to_string(selectable_land_ids.length());
		ofSetColor(0);
		game_settings->getFont().drawString(text, game_settings->getSquareLength() * game_settings->getNumberColumn(), game_settings->getFont().stringHeight(text) * 5);
	}
}

void World::setupLands() {
	size_t num_row = game_settings->getNumberRow();
	size_t num_col = game_settings->getNumberColumn();

	GeneralBuffer<size_t> rand_center_ids = GeneralBuffer<size_t>(game_settings->getNumberCountries());
	GeneralBuffer<size_t> possible_centers = GeneralBuffer<size_t>((num_col - 2) * (num_row - 2));
	// Eliminates border lands to establish a country
	for (size_t i = 0; i < possible_centers.memory_length(); i++)
	{
		possible_centers.setItem(i, (num_col + 1 + i) + (i / (num_col - 2)) * 2);
	}

	// Randomly find a center to establish a country
	unsigned int rand_index = 0;
	for (size_t i = 0; i < rand_center_ids.memory_length(); i++)
	{
		rand_index = unsigned int(ofRandom(possible_centers.length()));
		rand_center_ids.setItem(i, possible_centers.getItem(rand_index));
		possible_centers.reduceShiftList(rand_index);
		size_t rand_center_id = rand_center_ids.getItem(i);
		size_t k = 0;
		while(k < possible_centers.length())
		{
			size_t possible_center = possible_centers.getItem(k);
			if (possible_center == rand_center_id + 2
				|| possible_center == rand_center_id + 1
				|| possible_center == rand_center_id - 1
				|| possible_center == rand_center_id - 2
				|| possible_center == rand_center_id + 2 * num_col
				|| possible_center == rand_center_id + num_col
				|| possible_center == rand_center_id - num_col
				|| possible_center == rand_center_id - 2 * num_col
				|| possible_center == rand_center_id + num_col + 1
				|| possible_center == rand_center_id + num_col - 1
				|| possible_center == rand_center_id - num_col + 1
				|| possible_center == rand_center_id - num_col - 1) {
				possible_centers.reduceShiftList(k);
			}
			else {
				k++;
			}
		}
	}
	
	// Establish countries on lands
	for (size_t id = 0; id < total_lands; id++)
	{
		for (size_t i = 0; i < rand_center_ids.length(); i++)
		{
			if (id == rand_center_ids.getItem(i)) {
				size_t down_neighbour_id = id - num_col;
				size_t up_neighbour_id = id + num_col;
				size_t right_neighbour_id = id + 1;
				size_t left_neighbour_id = id - 1;
				lands[down_neighbour_id].setup(countries[i], down_neighbour_id, game_settings);
				lands[left_neighbour_id].setup(countries[i], left_neighbour_id, game_settings);
				lands[id].setup(countries[i], id, game_settings);
				lands[right_neighbour_id].setup(countries[i], right_neighbour_id, game_settings);
				lands[up_neighbour_id].setup(countries[i], up_neighbour_id, game_settings);
			}
		}

		if (!lands[id].is_initialized()) {
			lands[id].setup(countries[rand_center_ids.length()], id, game_settings);
		}
	}
}

void World::resetWorld() {
	countries = NULL;
	for (size_t id = 0; id < total_lands; id++)
	{
		lands[id].reset();
	}
	delete[] lands;
	lands = NULL;
	selected_land_ids.reset();
	selectable_land_ids.reset();
}

Country* World::getCountry(size_t order) {
	return countries[order];
}

size_t World::getNumberCountry() {
	return game_settings->getNumberCountries();
}

Land* World::getLand(size_t id) {
	return &lands[id];
}

size_t* World::getSelectedLandIDs() {
	return selected_land_ids.getArray();
}

size_t World::getNumberSelectedLand() {
	return selected_land_ids.length();
}

void World::updateLandsState(size_t id) {
	lands[id].toggleSelectionStatus();
	if (lands[id].getSelectionStatus()) {
		selected_land_ids.insertItem(id);
		increaseSelectableLands(id);
	}
	else {
		for (size_t i = 0; i < selected_land_ids.length(); i++)
		{
			if (selected_land_ids.getItem(i) == id) {
				selected_land_ids.reduceShiftList(i);
				decreaseSelectableLands(id);
				break;
			}
		}
	}
}

template <typename T>
void insertArrayUniquely(T* arr, T item, size_t& array_length) {
	bool existence = false;
	for (size_t i = 0; i < array_length; i++)
	{
		if (arr[i] == item) {
			existence = true;
			break;
		}
	}
	if (!existence) {
		arr[array_length] = item;
		array_length++;
	}
}

void World::initializeSelectableLands(Country* active_country) {
	for (size_t id = 0; id < total_lands; id++) {
		if (lands[id].getOwner() == active_country) {
			selectable_land_ids.insertItemUniquely(id);
			increaseSelectableLands(id);
		}
	}
}

void World::increaseSelectableLands(size_t selected_id) {
	size_t num_row = game_settings->getNumberRow();
	size_t num_col = game_settings->getNumberColumn();

	if (selected_id % num_col < num_col - 1) {
		selectable_land_ids.insertItemUniquely(selected_id + 1);
	}
	if (selected_id % num_col > 0) {
		selectable_land_ids.insertItemUniquely(selected_id - 1);
	}
	if ((selected_id + num_col) / num_col < num_row) {
		selectable_land_ids.insertItemUniquely(selected_id + num_col);
	}
	if ((selected_id - num_col) >= 0) {
		selectable_land_ids.insertItemUniquely(selected_id - num_col);
	}
}

void World::decreaseSelectableLands(size_t unselected_id) {
	size_t num_col = game_settings->getNumberColumn();
	bool still_selectable = false;
	size_t i = 0;
	while(i < selectable_land_ids.length()) {
		size_t selectable_land_id = selectable_land_ids.getItem(i);
		if (selectable_land_id == unselected_id + 1
			|| selectable_land_id == unselected_id - 1
			|| selectable_land_id == unselected_id + num_col
			|| selectable_land_id == unselected_id - num_col) {
			for (size_t k = 0; k < selected_land_ids.length(); k++)
			{
				size_t selected_land_id = selected_land_ids.getItem(k);
				if (selected_land_id == selectable_land_id + 1
					|| selected_land_id == selectable_land_id - 1
					|| selected_land_id == selectable_land_id + num_col
					|| selected_land_id == selectable_land_id - num_col) {
					still_selectable = true;
					break;
				}
			}
			if (lands[selectable_land_id].getOwner() == countries[0]
				|| lands[selectable_land_id + 1].getOwner() == countries[0]
				|| lands[selectable_land_id - 1].getOwner() == countries[0]
				|| lands[selectable_land_id + num_col].getOwner() == countries[0]
				|| lands[selectable_land_id - num_col].getOwner() == countries[0]) {
				still_selectable = true;
			}
			if (!still_selectable) {
				selectable_land_ids.reduceShiftList(i);
			}
			else {
				i++;
			}
			still_selectable = false;
		}
		else {
			i++;
		}
	}
}

void World::deselectLands() {
	for (size_t i = 0; i < selected_land_ids.length(); i++)
	{
		lands[selected_land_ids.getItem(i)].toggleSelectionStatus();
	}
	selected_land_ids.reset(total_lands);
	selectable_land_ids.reset(total_lands);
	initializeSelectableLands(countries[0]);
}

void World::checkPress(int x, int y) {
	for (size_t id = 0; id < total_lands; id++)
	{
		if (x > lands[id].getPosition().x && x < lands[id].getPosition().x + game_settings->getSquareLength()
			&& y > lands[id].getPosition().y && y < lands[id].getPosition().y + game_settings->getSquareLength()) {
			for (size_t i = 0; i < total_lands; i++)
			{
				if (selectable_land_ids.getItem(i) == id) {
					updateLandsState(id);
					break;
				}
			}
			break;
		}
	}
}

World::~World() {

}