#ifndef GAME_H_
#define GAME_H_

#include "Graphics.h"
#include "Input.h"
#include "angelscript.h"

class Screen;

#include <memory>

class Game
{
public:
	Game();
	~Game();

	static int TILE_SIZE;
	void setScreen(Screen* screen);
	Graphics* getGraphics();
	Input* getInput();
	void quit();

	asIScriptEngine* getScriptEngine();

private:
	void eventLoop();
	void update(int elapsedTimeInMs);
	void draw(Graphics& graphics);
	bool running;
	Graphics* _graphics;
	std::shared_ptr<Screen> _screen;
	Input* _input;
	asIScriptEngine *engine;
};

#endif // GAME_H_

