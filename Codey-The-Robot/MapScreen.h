#ifndef MAP_SCREEN_H_
#define MAP_SCREEN_H_

#include "Screen.h"
#include "Sprite.h"
#include "Button.h"
#include "MapCodey.h"
#include "Rectangle.h"
#include <string>

class MapScreen : public Screen
{
public:
	MapScreen(Game* game);
	~MapScreen();
	virtual void draw();
	virtual void update(int elapsedTimeInMs);
	std::string level;

private:
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	int xoffset;
	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> menuButton;
	std::shared_ptr<MapCodey> codey;

	std::map< Rectangle, std::tuple<int, int, std::string>> circles;

};

#endif //MAP_SCREEN_H_

