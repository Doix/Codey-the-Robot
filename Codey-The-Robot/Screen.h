#ifndef SCREEN_H_
#define SCREEN_H_

#include "Game.h"

class Screen
{
public:
	Screen(Game* game);
	~Screen();
	virtual void draw() = 0;
	virtual void update(int elapsedTimeInMs) =0 ;
protected:
	Game* game;
};

#endif   // SCREEN_H_