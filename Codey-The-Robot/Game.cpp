#include "Game.h"
#include "Graphics.h"
#include "SDL.h"
#include <stdio.h>

#include "AnimatedSprite.h"

//Constants
namespace{
	const int FPS = 60;
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

	sprite.reset(new AnimatedSprite(graphics, "content/codey.png", 0, 0, TILE_SIZE, TILE_SIZE, 15, 9));
	//set time for animation sprite update
	int lastUpdateTimeMs = SDL_GetTicks();

	bool running = true;
	while (running){

		//start time for the current frame
		const int startTimeMs = SDL_GetTicks();

		//handle events
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE){
					running = false;
					break;
				}

				default:
					break;
			}
		}

		//check time elapsed since last update method called 
		const int currentTimeMs = SDL_GetTicks();

		//update the screen
		update(currentTimeMs - lastUpdateTimeMs);
		lastUpdateTimeMs = currentTimeMs;

		//draw all items on the screen
		draw(graphics);

		//time frame has taken to run
		const int elapsedTimeMs = SDL_GetTicks() - startTimeMs;

		//delay next frame till 1000/60th of a second has elapsed (less time taken to draw frame)
		SDL_Delay(1000 /*ms*/ / FPS - elapsedTimeMs /*ms*/);
	} 

}

void Game::update(int elapsedTimeInMs)
{
	sprite->update(elapsedTimeInMs);
}

void Game::draw(Graphics& graphics)
{
	graphics.clear();
	sprite->draw(graphics, 200, 200);
	graphics.flip();
}

