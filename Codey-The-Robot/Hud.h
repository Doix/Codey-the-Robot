#ifndef HUD_H_
#define HUD_H_

#include "Sprite.h"
#include "Graphics.h"
#include <memory>
#include <queue>
#include <set>
#include "Commands.h"
#include "ControlledSprite.h"

enum class InsertMode {
	MAIN,
	LOOP
};


class Hud
{
public:
	Hud(Graphics& graphics, int x, int y, std::shared_ptr<ControlledSprite> player);
	~Hud();

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics);
	bool click(std::tuple<int, int> clicked);
	void setPlayer(std::shared_ptr<ControlledSprite> player);
private:
	int PosX;
	int PosY;
	int loopLocation;
	std::shared_ptr<ControlledSprite> player;

	std::unique_ptr<Sprite> sprite;
	CommandAction curCommand;
	void initializeSprites(Graphics& graphics);
	std::map<CommandAction, std::unique_ptr<Sprite>> buttons;
	std::vector<CommandAction> availableCommands;
	InsertMode insertMode;

};


#endif