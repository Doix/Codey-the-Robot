#include "Hud.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include <iostream>
#include "Rectangle.h"
#include "LoopCommand.h"

namespace{
	const int BUTTON_SIZE = 32;
	const std::string HUD_FILE_PATH = "content/hud.bmp";
	const std::string BUTTON_FILE_PATH = "content/hudButtons.png";
	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 95;
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
	availableCommands = std::vector<CommandAction>{CommandAction::MOVE_FORWARD, CommandAction::TURN_LEFT, CommandAction::TURN_RIGHT,
		CommandAction::LOOP};
	setPlayer(player);

	insertMode = InsertMode::MAIN;
	loopLocation = 0;

}

//Destructor - release the sprite
Hud::~Hud()
{
	sprite.release();
}
void Hud::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY, HUD_WIDTH, HUD_HEIGHT);
	clickableCommands.clear();

	SDL_Rect rect = player->clickRectangle();
	graphics.drawRectangle(&rect);


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
	int commandLocation = 0;
	std::list < std::shared_ptr<Command>>* commands = player->getCommands();

	for (std::shared_ptr<Command> command : *commands){

		if (std::dynamic_pointer_cast<LoopCommand>(command)) {
			count = 0;
			std::shared_ptr<LoopCommand>loopCommand = std::dynamic_pointer_cast<LoopCommand>(command);
			if (x != 666) {
				x = 666;
				y += BUTTON_SIZE + 10;
			}
			makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::LOOP], loopCommand);
			graphics.renderText("start:", x + BUTTON_SIZE + BUTTON_SIZE / 4, y - 5, BUTTON_SIZE);


			graphics.renderText(std::to_string(loopCommand->getLoops() + 1), x + BUTTON_SIZE * 5, y - 5, BUTTON_SIZE);

			makeAndDrawButton(graphics, x + BUTTON_SIZE * 4, y, BUTTON_SIZE / 1.5, BUTTON_SIZE, *buttons[CommandAction::LOOP_UP],
				std::shared_ptr<Command>(new Command(CommandAction::LOOP_UP)));
			makeAndDrawButton(graphics, x + BUTTON_SIZE * 6, y, BUTTON_SIZE / 1.5, BUTTON_SIZE, *buttons[CommandAction::LOOP_DOWN],
				std::shared_ptr<Command>(new Command(CommandAction::LOOP_DOWN)));


			y += BUTTON_SIZE + 10;

			for (std::shared_ptr<Command> command2 : *loopCommand->getCommands()) {
				makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[command2->getCommand()], command2);
				count++;
				x += BUTTON_SIZE + 10;
				if (count % 6 == 0){
					x = 666;
					y += BUTTON_SIZE + 10;
				}
			}

			if (insertMode == InsertMode::LOOP && loopLocation == commandLocation) {
				makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::NONE_SELECTED], nullptr);
			}
			else {
				makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::NONE], nullptr);
			}

			y += BUTTON_SIZE + 10;
			x = 666;
			makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::LOOP], loopCommand);
			count = 0;
			y += BUTTON_SIZE + 10;
		}
		else {
			makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[command->getCommand()], command);

			x += BUTTON_SIZE + 10;
			count++;
			if (count % 6 == 0){
				x = 666;
				y += BUTTON_SIZE + 10;
			}
		}
		commandLocation++;
	}
	if (insertMode == InsertMode::MAIN){
		makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::NONE_SELECTED], nullptr);
	}
	else {
		makeAndDrawButton(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE, *buttons[CommandAction::NONE], nullptr);
	}
}


void Hud::makeAndDrawButton(Graphics& graphics, int x, int y, int w, int h, Sprite& sprite, std::shared_ptr<Command> command) {
	HudButton temp = HudButton(sprite, Rectangle(x, y, w, h), command);
	clickableCommands.push_back(temp);
	sprite.draw(graphics, x, y, w, h);
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

			if (col < availableCommands.size()) {
				CommandAction command = availableCommands.at(col);
				if (command == CommandAction::LOOP) {
					player->sendCommand(std::shared_ptr<LoopCommand>(new LoopCommand(command, 1)));
					insertMode = InsertMode::LOOP;
					std::list < std::shared_ptr<Command>>* commands = player->getCommands();
					loopLocation = commands->size() - 1;
				}
				else {
					if (insertMode == InsertMode::MAIN)
						player->sendCommand(std::shared_ptr<Command>(new Command(command)));
					else {
						std::list < std::shared_ptr<Command>>* commands = player->getCommands();
						std::list<std::shared_ptr<Command>>::iterator it = commands->begin();
						std::advance(it, loopLocation);
						std::shared_ptr<LoopCommand> loopCommand = std::dynamic_pointer_cast<LoopCommand>(*it);
						loopCommand->addCommand(std::shared_ptr<Command>(new Command(command)));
					}
				}
			}
		}

		if (x > 666 && x < 926 && y > 10 && y < 360) {

			unsigned int index = 0;
			bool inLoop = false;
			unsigned int loopIndex = 0;
			unsigned int commandIndex = 0;

			std::shared_ptr<LoopCommand> loopCommand = nullptr;

			for (auto thingy : clickableCommands) {
				if (thingy.command != nullptr) {
					if (std::dynamic_pointer_cast<LoopCommand>(thingy.command)) {
						loopCommand = std::dynamic_pointer_cast<LoopCommand>(thingy.command);
						inLoop = !inLoop;
						loopIndex = -1;
					}
				}
				if (thingy.isClicked(x, y)){
					printf("%d\n", commandIndex);
					if (index == clickableCommands.size() - 1) {
						insertMode = InsertMode::MAIN;
					}
					else if (inLoop) {
						if (thingy.command != nullptr) {
							if (thingy.command->getCommand() == CommandAction::LOOP_DOWN) {
								loopCommand->decreaseLoops();
							}
							else if (thingy.command->getCommand() == CommandAction::LOOP_UP) {
								loopCommand->increaseLoops();
							}
							else {
								player->removeCommand(commandIndex);
								insertMode = InsertMode::MAIN;
							}
						}
						else if (loopIndex == loopCommand->size() + 2){
							insertMode = InsertMode::LOOP;
							loopLocation = commandIndex;
						}
						else if (loopIndex != -1) {
							loopCommand->removeCommand(loopIndex);
						}

						else {
							player->removeCommand(commandIndex);
							insertMode = InsertMode::MAIN;
						}
					}
					else {
						player->removeCommand(commandIndex);
						insertMode = InsertMode::MAIN;
					}
				}
				if (inLoop) {
					loopIndex++;
					commandIndex--;
				}
				index++;
				commandIndex++;

			}
		}
	}
	return ret;
}

void Hud::initializeSprites(Graphics& graphics) {
	// very very very ugly
	// need a better solution for this
	buttons[CommandAction::TURN_RIGHT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 3, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::LOOP] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 1, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::MOVE_FORWARD] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::TURN_LEFT] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::NONE] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 4, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::NONE_SELECTED] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 5, 0, BUTTON_WIDTH, BUTTON_HEIGHT));

	buttons[CommandAction::LOOP_UP] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT));
	buttons[CommandAction::LOOP_DOWN] = std::unique_ptr<Sprite>(new Sprite(graphics, BUTTON_FILE_PATH, BUTTON_WIDTH * 6, 0, BUTTON_WIDTH, BUTTON_HEIGHT));

}

void Hud::setPlayer(std::shared_ptr<ControlledSprite> player) {
	this->player = player;
}