#include "MapScreen.h"
#include "Sprite.h"
#include <algorithm>    // std::max


namespace {
	const std::string MAP_FILE_PATH = "content/map.png";
}

MapScreen::MapScreen(Game* game) : Screen(game)
{
	texture = game->getGraphics()->loadTexture(MAP_FILE_PATH);

	xoffset = 0;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 940;
	sourceRect.h = 480;

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
}

void MapScreen::update(int time) {
	if (game->getInput()->isMouseHeld()) {
		int xrel, yrel;
		std::tie(xrel, yrel) = game->getInput()->getMouseMotion();
		xoffset = std::max(0, std::min(xoffset - xrel, 940));;
		sourceRect.x = xoffset;
	}
}
