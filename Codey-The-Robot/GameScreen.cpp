#include "GameScreen.h"
#include "MapScreen.h"
#include "Rectangle.h"

GameScreen::GameScreen(Game* game) : Screen(game)
{
	//Initialise Map & Player
	player.reset(new Codey(*game->getGraphics(), 1 * Game::TILE_SIZE, 1 * Game::TILE_SIZE));
	firstEnemy.reset(new Enemy(*game->getGraphics(), 4 * Game::TILE_SIZE, 4 * Game::TILE_SIZE));
	map.reset(Map::createTestMap(*game->getGraphics()));
	hud.reset(new Hud(*game->getGraphics(), 640, 0, player));
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw() {
	map->draw(*game->getGraphics());
	player->draw(*game->getGraphics());
	firstEnemy->draw(*game->getGraphics());
	hud->draw(*game->getGraphics());
}

void GameScreen::update(int elapsedTimeInMs) {

	if (game->getInput()->wasKeyReleased(SDLK_SPACE)) {
		player->startCommands();
	}

	if (game->getInput()->wasMouseClicked()){
		hud->click(game->getInput()->getMouseClick());
	}

	map->update(elapsedTimeInMs);
	player->update(elapsedTimeInMs, *map);
	firstEnemy->update(elapsedTimeInMs, *map);
	if (firstEnemy->damageRectangle().collidesWith(player->damageRectangle())){
		player->deathSequence();		
	}
	//Check if Escape key pressed - back to menu
	if (game->getInput()->wasKeyPressed(SDLK_ESCAPE)){
		game->setScreen(new MapScreen(game));
		return;
	}

}