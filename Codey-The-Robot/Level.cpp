#include "Level.h"
#include "Map.h"
#include "Codey.h"
#include "Game.h"
#include "Enemy.h"
#include "Rectangle.h"
#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using std::regex;
using std::string;
using std::sregex_token_iterator;

Level::Level(std::string name, Graphics* graphics) : name(name), graphics(graphics) {
	map.reset(Map::createMapFromFile(*graphics, "content/levels/" + name + ".map"));

	LoadEntities();
}
Level::~Level() {
}

void Level::start() {
	for (auto player : players)
		player->startCommands();
}

void Level::LoadEntities() {
	std::ifstream fs("content/levels/" + name + ".entities");
	string line;
	regex re("[\\s,]+");

	int col = 0;
	int row = 0;


	while (std::getline(fs, line)) {
		sregex_token_iterator it(line.begin(), line.end(), re, -1);
		sregex_token_iterator reg_end;
		string object = it->str();

		if (object == "Codey") {
			it++;
			players.push_back(std::shared_ptr<Codey>(new Codey(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}
		else if (object == "Enemy") {
			it++;
			enemies.push_back(std::shared_ptr<Enemy>(new Enemy(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}

	}
}

void Level::update(int elapsedTimeInMs) {
	map->update(elapsedTimeInMs);
	for (auto player : players)
		player->update(elapsedTimeInMs, *map);
	for (auto enemy: enemies)
		enemy->update(elapsedTimeInMs, *map);

	for (auto player : players){
		for (auto enemy : enemies) {
			if (enemy->damageRectangle().collidesWith(player->damageRectangle())){
				player->deathSequence();
			}
		}
	}

}

void Level::draw() {
	map->draw(*graphics);
	for (auto player : players)
		player->draw(*graphics);

	for (auto enemy : enemies) 
		enemy->draw(*graphics);
}


std::vector<std::shared_ptr<Codey>> Level::getPlayers() {
	return players;
}