#ifndef HUD_H_
#define HUD_H_

#include "Sprite.h"
#include "Graphics.h"
#include <memory>
#include <queue>
#include "Commands.h"

class Hud
{
public:
	Hud(Graphics& graphics, int x, int y);
	~Hud();

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics);
	void click(std::tuple<int, int> clicked);

private:
	int PosX;
	int PosY;

	std::unique_ptr<Sprite> sprite;
	std::queue< Command > commands;
	Command curCommand;
};


#endif