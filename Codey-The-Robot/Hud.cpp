#include "Hud.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include <iostream>

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
	availableCommands = std::vector<Command>{Command::LEFT, Command::DOWN, Command::UP, Command::RIGHT};
	setPlayer(player);
}

//Destructor - release the sprite
Hud::~Hud()
{
	sprite.release();
}
void Hud::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY, HUD_WIDTH, HUD_HEIGHT);

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
	std::deque<Command> commands = player->getCommands();

	x = 666;
	y = 20;
	count = 0;
	for (Command command : commands){ 
		buttons[command]->draw(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE);
		x += BUTTON_SIZE + 10;
		count++;
		if (count % 6 == 0){
			x = 666;
			y += BUTTON_SIZE + 10;
		}
	}

}

void Hud::click(std::tuple<int, int> clicked) {
	int x, y;
	std::tie(x, y) = clicked;
	if (x > 655 && x < 926 && y >375 && y < 470) {
		x -= 655;
		y -= 375;
		int col = x / (BUTTON_SIZE+10);
		int row = y / BUTTON_SIZE;
		//TODO:: will need to be updated to handle multiple rows
		//when we have enough commands
		Command command = availableCommands.at(col);
		player->sendCommand(command);
	}
}

void Hud::initializeSprites(Graphics& graphics) {
	// very very very ugly
	// need a better solution for this
	buttons[Command::RIGHT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE*0, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::DOWN] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 1, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::UP] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 2, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::LEFT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 3, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::NONE] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_SIZE * 4, 0, BUTTON_SIZE, BUTTON_SIZE));

}

void Hud::setPlayer(std::shared_ptr<ControlledSprite> player) {
	this->player = player;
}