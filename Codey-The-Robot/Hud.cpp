#include "Hud.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include <iostream>
#include "Rectangle.h"

namespace{
	const int BUTTON_SIZE = 32;
	const std::string HUD_FILE_PATH = "content/hud.bmp";
	const std::string BUTTON_FILE_PATH = "content/buttons.bmp";
	const int HUD_WIDTH = Game::TILE_SIZE * 4;
	const int HUD_HEIGHT = Game::TILE_SIZE * 6;
}


Hud::Hud(Graphics& graphics, int x, int y, std::shared_ptr<ControlledSprite> player)
{
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//initialise the AnimatedSprite for the player
	sprite.reset(new Sprite(graphics, HUD_FILE_PATH, 0, 0, HUD_WIDTH, HUD_HEIGHT));
	initializeSprites(graphics);

	// lets just hardcode this for now
	availableCommands = std::vector<CommandAction>{CommandAction::MOVE_FORWARD, CommandAction::TURN_LEFT, CommandAction::TURN_RIGHT};
	setPlayer(player);
}

//Destructor - release the sprite
Hud::~Hud()
{
	sprite.release();
}
void Hud::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY, HUD_WIDTH, HUD_HEIGHT);

	
	SDL_Rect rect = player->clickRectangle();
	graphics.drawRectanlge(&rect);


	int x = 666;
	int y = 374;
	int count = 0;

	for (const auto& command : availableCommands) {
		buttons[command]->draw(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE);
		x += BUTTON_SIZE + 10;
		count++;
		if (count % 6 == 0){
			x = 666;
			y += BUTTON_SIZE + 10;
		}
	}

	x = 666;
	y = 20;
	count = 0;

	std::list < std::shared_ptr<Command>>* commands = player->getCommands();

	for (std::shared_ptr<Command> command : *commands){
		buttons[command->getCommand()]->draw(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE);
		x += BUTTON_SIZE + 10;
		count++;
		if (count % 6 == 0){
			x = 666;
			y += BUTTON_SIZE + 10;
		}
	}

}

bool Hud::click(std::tuple<int, int> clicked) {
	int x, y;
	bool ret = false;
	std::tie(x, y) = clicked;
	if (!player->isBusy()) {
		if (x > 666 && x < 926 && y >375 && y < 470) {
			ret = true;
			x -= 655;
			y -= 375;
			unsigned int col = x / (BUTTON_SIZE + 10);
			unsigned int row = y / BUTTON_SIZE;
			//TODO:: will need to be updated to handle multiple rows
			//when we have enough commands
			if (col < availableCommands.size()) {
				CommandAction command = availableCommands.at(col);
				player->sendCommand(std::shared_ptr<Command>(new Command(command)));
			}
		}

		if (x > 666 && x < 926 && y > 10 && y < 360) {
			ret = true;
			x -= 655;
			y -= 21;
			int col = x / (BUTTON_SIZE + 10);
			int row = y / BUTTON_SIZE;

			unsigned int index = col + row * 6;
			if (index < player->getCommands()->size()) {
				player->removeCommand(index);
			}
		}
	}
	return ret;
}

void Hud::initializeSprites(Graphics& graphics) {
	// very very very ugly
	// need a better solution for this
	buttons[CommandAction::TURN_RIGHT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 0, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[CommandAction::LOOP] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 1, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[CommandAction::MOVE_FORWARD] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 2, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[CommandAction::TURN_LEFT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 3, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[CommandAction::NONE] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 4, 0, BUTTON_SIZE, BUTTON_SIZE));

}

void Hud::setPlayer(std::shared_ptr<ControlledSprite> player) {
	this->player = player;
}