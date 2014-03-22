#include "IntroScreen.h"
#include "Sprite.h"
#include "GameScreen.h"

namespace {
	const std::string MENU_FILE_PATH = "content/menu.png";
}

IntroScreen::IntroScreen(Game* game) : Screen(game)
{
	initializeSprites(*game->getGraphics());
}

IntroScreen::~IntroScreen()
{
}

void IntroScreen::draw() {
	background->draw(*game->getGraphics(), 0, 0, 940, 480);
}

void IntroScreen::update(int time) {
	if (game->getInput()->wasMouseClicked()) {
		int x, y;
		std::tie(x, y) = game->getInput()->getMouseClick();
		if (x > 380 && x < 560 && y > 282 && y < 408 ) {
			if (y < 328)
				start();
			else
				quit();
		}
		printf("%d %d\n", x, y ); 
	}
}

void IntroScreen::quit(){
	game->quit(); 
}

void IntroScreen::start() {
	game->setScreen(new GameScreen(game));
}

void IntroScreen::initializeSprites(Graphics& graphics) {

	background.reset(new Sprite(graphics, MENU_FILE_PATH, 0, 0, 940, 480));
}
