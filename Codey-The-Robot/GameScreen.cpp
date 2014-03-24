#include "GameScreen.h"
#include "MapScreen.h"
#include "Rectangle.h"
#include "Level.h"

GameScreen::GameScreen(Game* game, std::shared_ptr<Level> level) : level(level), Screen(game)
{
	//Initialise Map & Player
	hud.reset(new Hud(*game->getGraphics(), 640, 0,
		level->getPlayers()[0]));
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw() {

	level->draw();
	hud->draw(*game->getGraphics());
}

void GameScreen::update(int elapsedTimeInMs) {

	if (game->getInput()->wasKeyReleased(SDLK_SPACE)) {
		bool busy = false;
		for (auto player : level->getPlayers()) {
			if (player->isBusy()) {
				busy = true;
			}
		}
		if (!busy)
			level->start();
	}

	if (game->getInput()->wasMouseClicked()){
		hud->click(game->getInput()->getMouseClick());
		for (auto player : level->getPlayers()) {
			int x, y;
			std::tie(x, y) = game->getInput()->getMouseClick();
			if (player->clickRectangle().contains(x, y))
				hud->setPlayer(player);
		}
	}

	level->update(elapsedTimeInMs);

	if (game->getInput()->wasKeyPressed(SDLK_ESCAPE)){
		game->setScreen(new MapScreen(game));
		return;
	}
}