#ifndef INTRO_SCREEN_H_
#define INTRO_SCREEN_H_

#include "Screen.h"
#include "Sprite.h"

class IntroScreen : public Screen
{
public:
	IntroScreen(Game* game);
	~IntroScreen();
	virtual void draw();
	virtual void update(int elapsedTimeInMs);

private:
	void initializeSprites(Graphics& graphics);
	std::unique_ptr<Sprite> background;

	void start();
	void quit();
};

#endif //INTRO_SCREEN_H_

