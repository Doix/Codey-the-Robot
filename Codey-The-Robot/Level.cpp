#include "Level.h"
#include "Map.h"
#include "Codey.h"
#include "Game.h"
#include "Enemy.h"
#include "Rectangle.h"


Level::Level(std::string name, Graphics* graphics) : name(name), graphics(graphics) {
	map.reset(Map::createMapFromFile(*graphics, "content/levels/" + name + ".map"));

	player.reset(new Codey(*graphics, 1 * Game::TILE_SIZE, 1 * Game::TILE_SIZE));
	firstEnemy.reset(new Enemy(*graphics, 4 * Game::TILE_SIZE, 4 * Game::TILE_SIZE));

}
Level::~Level() {
}

void Level::start() {
	player->startCommands();
}

void Level::update(int elapsedTimeInMs) {
	map->update(elapsedTimeInMs);
	player->update(elapsedTimeInMs, *map);
	firstEnemy->update(elapsedTimeInMs, *map);
	if (firstEnemy->damageRectangle().collidesWith(player->damageRectangle())){
		player->deathSequence();		
	}
}

void Level::draw() {
	map->draw(*graphics);
	player->draw(*graphics);
	firstEnemy->draw(*graphics);
}


std::shared_ptr<Codey> Level::getPlayer() {
	return player;
}