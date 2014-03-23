#include "SDL.h"
#include <stdio.h>
#include <algorithm>

#include "Codey.h"
#include "Input.h"
#include "Map.h"
#include "Game.h"
#include "Graphics.h"
#include <algorithm>
#include "Hud.h"
#include "Enemy.h"
#include "Rectangle.h"
#include "IntroScreen.h"


#include <angelscript.h>
#include "add_on/scriptstdstring/scriptstdstring.h"
#include "add_on/scriptbuilder/scriptbuilder.h"

//Constants
namespace{
	const int FPS = 60;
	const int FRAME_TIME = 1000 / FPS;
	const int MAX_FRAME_TIME = 4 * FRAME_TIME;
}

//static - accessible by all classes
int Game::TILE_SIZE = 80; //pixels

//constructor - initialise all SDL tools
Game::Game()
{	
	SDL_Init(SDL_INIT_EVERYTHING);
	running = false;
	eventLoop();
}

//close all SDL tools
Game::~Game()
{
	SDL_Quit();
}

void MessageCallback(const asSMessageInfo *msg, void *){
	if (msg->section[0] == '\0'){
		printf("%s: %s\n", msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
	else if (msg->row == 0 && msg->col == 0){
		printf("%s: %s : %s\n", msg->section, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
	else{
		printf("%s(%d, %d): %s : %s\n", msg->section, msg->row, msg->col, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
}

//Main Event loop
void Game::eventLoop(){

	//what even is going on here
	// trying to move graphics or input anywhere seems to break things
	// so just dereferencing them here, works fine for now i guess
	Graphics graphics;
	_graphics = &graphics;
	SDL_Event event;
	Input input;
	_input = &input;


	asIScriptEngine *engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	// Set the message callback to receive information on errors in human readable form.
	int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
	// AngelScript doesn't have a built-in string type, as there is no definite standard 
	// string type for C++ applications. Every developer is free to register it's own string type.
	// The SDK do however provide a standard add-on for registering a string type, so it's not
	// necessary to implement the registration yourself if you don't want to.
	RegisterStdString(engine);


	setScreen(new IntroScreen(this));

	//set initial time for animation sprite update
	int lastUpdateTimeMs = SDL_GetTicks();

	//Loop for each frame
	running = true;
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
			case SDL_MOUSEBUTTONUP:
				input.MouseReleasedEvent(event);
				break;
			case SDL_MOUSEMOTION:
				input.MouseMotionEvent(event);
				break;
			default:
				break;
			}
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
			SDL_Delay(FRAME_TIME - elapsedTimeMs /*ms*/);
		}
		
	} 

}

//update the screen
void Game::update(int elapsedTimeInMs)
{
	_screen->update(elapsedTimeInMs);
}

void Game::setScreen(Screen* scr){
	_screen.reset(scr);
}

//clear and then redraw the screen
void Game::draw(Graphics& graphics)
{
	graphics.clear();

	_screen->draw();
	graphics.flip();
}

Graphics* Game::getGraphics() {
	return _graphics;
}

Input* Game::getInput() {
	return _input;
}

void Game::quit() {
	running = false;
}