#include "Game.h"
#include "Graphics.h"
#include "SDL.h"
#include <stdio.h>

#include "Player.h"
#include "Input.h"
#include <algorithm>

//Constants
namespace{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 4 * 1000 / 60;
}

//static
int Game::TILE_SIZE = 80;

Game::Game()
{	
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
}


Game::~Game()
{
	SDL_Quit();
}


void Game::eventLoop(){
	//call graphics constructor
	Graphics graphics;
	SDL_Event event;
	Input input;

	player.reset(new Player(graphics, 320, 240));
	//set time for animation sprite update
	int lastUpdateTimeMs = SDL_GetTicks();

	bool running = true;
	while (running){

		//start time for the current frame
		const int startTimeMs = SDL_GetTicks();

		//start new frame for keyboard inputs
		input.beginNewFrame();

		//handle events
		while (SDL_PollEvent(&event)){
			switch (event.type){

			case SDL_KEYDOWN:
				input.KeyDownEvent(event);
				break;

			case SDL_KEYUP:
				input.KeyUpEvent(event);
				break;

			default:
				break;
			}
		}

		if (input.wasKeyPressed(SDLK_ESCAPE)){
			running = false;
		}

		//Check direction arrows being pushed - THIS WILL NEED TO BE UPDATED TO RESPOND TO COMMANDS ORDERED BY PLAYER
		if (input.isKeyHeld(SDLK_RIGHT)){
			player->startMovingRight();
		}
		else if (input.isKeyHeld(SDLK_LEFT)){
			player->startMovingLeft();
		}
		else if (input.isKeyHeld(SDLK_UP)){
			player->startMovingUp();
		}
		else if (input.isKeyHeld(SDLK_DOWN)){
			player->startMovingDown();
		}
		else{
			player->stopMoving();
		}



		//check time elapsed since last update method called 
		const int currentTimeMs = SDL_GetTicks();

		const int frameElapsedTime = currentTimeMs - lastUpdateTimeMs;

		//update the screen
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

void Game::update(int elapsedTimeInMs)
{
	player->update(elapsedTimeInMs);
}

void Game::draw(Graphics& graphics)
{
	graphics.clear();
	player->draw(graphics);
	graphics.flip();
}

