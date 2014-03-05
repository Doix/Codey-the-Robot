#include "Game.h"
#include "Graphics.h"
#include "SDL.h"
#include <stdio.h>

#include "Codey.h"
#include "Input.h"
#include <algorithm>
#include "Hud.h"

//Constants
namespace{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 4 * 1000 / 60;
}

//static - accessible by all classes
int Game::TILE_SIZE = 80;

//constructor - initialise all SDL tools
Game::Game()
{	
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
}

//close all SDL tools
Game::~Game()
{
	SDL_Quit();
}

//Main Event loop
void Game::eventLoop(){
	//call graphics constructor
	Graphics graphics;
	SDL_Event event;
	Input input;

	player.reset(new Codey(graphics, 320, 240));

	hud.reset(new Hud(graphics, 640, 0));
	//set initial time for animation sprite update
	int lastUpdateTimeMs = SDL_GetTicks();

	//Loop for each frame
	bool running = true;
	while (running){
		//start time for the current frame
		const int startTimeMs = SDL_GetTicks();

		//start new frame for keyboard inputs
		input.beginNewFrame();

		//handle events - pass them to relevant functions to use
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_KEYDOWN:
				input.KeyDownEvent(event);
				break;
			case SDL_KEYUP:
				input.KeyUpEvent(event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				input.MouseClickEvent(event);
				break;
			default:
				break;
			}
		}

		//Check if Escape key pressed - quits game
		if (input.wasKeyPressed(SDLK_ESCAPE)){
			running = false;
		}

		//Check direction arrows being pushed - 
		//THIS WILL NEED TO BE UPDATED TO RESPOND TO COMMANDS ORDERED BY PLAYER
		if (input.wasKeyReleased(SDLK_RIGHT)){
			player->startMovingRight();
		}
		else if (input.wasKeyReleased(SDLK_LEFT)){
			player->startMovingLeft();
		}
		else if (input.wasKeyReleased(SDLK_UP)){
			player->startMovingUp();
		}
		else if (input.wasKeyReleased(SDLK_DOWN)){
			player->startMovingDown();
		}
		else if (input.wasKeyReleased(SDLK_SPACE)) {
			player->startCommands();
		}

		if (input.wasMouseClicked()) {
			hud->click(input.getMouseClick());
		}
		//check time elapsed since last update method called 
		const int currentTimeMs = SDL_GetTicks();

		//time elapsed since the screen was last updated
		const int frameElapsedTime = currentTimeMs - lastUpdateTimeMs;

		//update the screen - 
		//time elapsed smaller of time elapsed since last update or max update time (see constant)
		update(std::min(frameElapsedTime, MAX_FRAME_TIME));
		lastUpdateTimeMs = currentTimeMs;

		//draw all items on the screen
		draw(graphics);

		//time frame has taken to run
		const int elapsedTimeMs = SDL_GetTicks() - startTimeMs;

		//delay next frame till 1000/60th of a second has elapsed (less time taken to draw frame)
		//If statement to ensure that the elapsed time !> the 100 / FPS otherwise freezes
		if (elapsedTimeMs < 1000 /*ms*/ / FPS){
			SDL_Delay(1000 /*ms*/ / FPS - elapsedTimeMs /*ms*/);
		}
		
	} 

}

//update the screen
void Game::update(int elapsedTimeInMs)
{
	player->update(elapsedTimeInMs);
}

//clear and then redraw the screen
void Game::draw(Graphics& graphics)
{
	graphics.clear();
	player->draw(graphics);
	hud->draw(graphics);
	graphics.flip();
}

