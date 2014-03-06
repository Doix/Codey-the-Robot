#ifndef HUD_H_
#define HUD_H_

#include "Sprite.h"
#include "Graphics.h"
#include <memory>
#include <queue>
#include <set>
#include "Commands.h"
#include "ControlledSprite.h"

class Hud
{
public:
	Hud(Graphics& graphics, int x, int y, std::shared_ptr<ControlledSprite> player);
	~Hud();

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics);
	void click(std::tuple<int, int> clicked);

private:
	int PosX;
	int PosY;

	std::shared_ptr<ControlledSprite> player;

	std::unique_ptr<Sprite> sprite;
	Command curCommand;
	void Hud::initializeSprites(Graphics& graphics);
	std::map<Command, std::unique_ptr<Sprite>> buttons;
	std::vector<Command> availableCommands;

	void Hud::setPlayer(std::shared_ptr<ControlledSprite> player);

};


#endif