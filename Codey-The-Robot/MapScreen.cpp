#include "MapScreen.h"
#include "Sprite.h"
#include "Button.h"
#include "Rectangle.h"
#include <algorithm>    // std::max
#include "IntroScreen.h"
#include "GameScreen.h"


namespace {
	const std::string MAP_FILE_PATH = "content/map.png";
	const std::string BUTTON_FILE_PATH = "content/map_buttons.png";
}

MapScreen::MapScreen(Game* game) : Screen(game)
{

	codey.reset(new MapCodey(*game->getGraphics(), 1 * Game::TILE_SIZE, 1 * Game::TILE_SIZE));

	texture = game->getGraphics()->loadTexture(MAP_FILE_PATH);
	xoffset = 0;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 940;
	sourceRect.h = 480;

	playButton.reset(new Button(*game->getGraphics(), BUTTON_FILE_PATH, 
		0, 0, 260, 52, Rectangle(175, 426, 260, 52))); //numberwang
	menuButton.reset(new Button(*game->getGraphics(), BUTTON_FILE_PATH, 
		261, 0, 260, 52, Rectangle(475, 426, 260, 52)));

}

MapScreen::~MapScreen()
{
}

void MapScreen::draw() {
	SDL_Rect destinationRect;
	destinationRect.x = 0;
	destinationRect.y = 0;
	destinationRect.w = 940;
	destinationRect.h = 480;

	game->getGraphics()->renderTexture(texture, &sourceRect, &destinationRect);
	playButton->draw(*game->getGraphics(), 175, 426, 260, 52);
	menuButton->draw(*game->getGraphics(), 475, 426, 260, 52);
	codey->draw(*game->getGraphics());
	
}

void MapScreen::update(int time) {

	codey->update(time);

	if (game->getInput()->isMouseHeld()) {
		int xrel, yrel;
		std::tie(xrel, yrel) = game->getInput()->getMouseMotion();
		xoffset = std::max(0, std::min(xoffset - xrel, 940));;
		sourceRect.x = xoffset;
	}

	if (game->getInput()->wasMouseClicked()) {
		int x, y;
		std::tie(x, y) = game->getInput()->getMouseClick();
		if (y > 420) { // possible button press
			if (playButton->isClicked(x,y)) {
				game->setScreen(new GameScreen(game));
				return;
			}
			else if (menuButton->isClicked(x,y)){
				game->setScreen(new IntroScreen(game));
				return;
			}
		}
		else { // possible circle press

		}
		printf("%d %d\n", x, y);
	}
	//Check if Escape key pressed - back to menu
	if (game->getInput()->wasKeyPressed(SDLK_ESCAPE)){
		game->setScreen(new IntroScreen(game));
		return;
	}
}
