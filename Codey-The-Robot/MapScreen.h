#ifndef MAP_SCREEN_H_
#define MAP_SCREEN_H_

#include "Screen.h"
#include "Sprite.h"

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
};

#endif //MAP_SCREEN_H_

