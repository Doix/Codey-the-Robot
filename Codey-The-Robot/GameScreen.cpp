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
	if (!(level->tutorialComplete)){
		level->drawTutorial();
	}
	if (level->levelBeaten){
		level->drawWinScreen();
	}
	
}

void GameScreen::update(int elapsedTimeInMs) {

	if (level->tutorialComplete){
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


		if (level->tutorialComplete){
			if (game->getInput()->wasKeyReleased(SDLK_r)) {
				level->restart();
			}
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
	}
	if (game->getInput()->wasKeyPressed(SDLK_RETURN)){
		if (level->levelBeaten){
			game->setScreen(new MapScreen(game));
		}
		else if (!(level->tutorialComplete)){
			level->nextTutorialText();
		}
		return;
	}
	
	if (game->getInput()->wasKeyPressed(SDLK_ESCAPE)){
		game->setScreen(new MapScreen(game));
		return;
	}
	
	level->update(elapsedTimeInMs);
}