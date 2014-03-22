#ifndef MAP_SCREEN_H_
#define MAP_SCREEN_H_

#include "Screen.h"
#include "Sprite.h"
#include "Button.h"

class MapScreen : public Screen
{
public:
	MapScreen(Game* game);
	~MapScreen();
	virtual void draw();
	virtual void update(int elapsedTimeInMs);

private:
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	int xoffset;
	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> menuButton;
};

#endif //MAP_SCREEN_H_

