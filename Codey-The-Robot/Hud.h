#ifndef HUD_H_
#define HUD_H_

#include "Sprite.h"
#include "Graphics.h"
#include <memory>
#include <queue>
#include <set>
#include "Commands.h"
#include "ControlledSprite.h"
#include "HudButton.h"

enum class InsertMode {
	MAIN,
	LOOP
};

using std::vector;
using std::map;
using std::shared_ptr;
using std::unique_ptr;

class Hud
{
public:
	Hud(Graphics& graphics, int x, int y, shared_ptr<ControlledSprite> player);
	~Hud();

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics);
	bool click(std::tuple<int, int> clicked);
	void setPlayer(shared_ptr<ControlledSprite> player);
private:
	int PosX;
	int PosY;
	unsigned int loopLocation;
	shared_ptr<ControlledSprite> player;
	void makeAndDrawButton(Graphics& graphics, int x, int y, int w, int h, Sprite& sprite, std::shared_ptr<Command> command);
	unique_ptr<Sprite> sprite;
	CommandAction curCommand;
	void initializeSprites(Graphics& graphics);
	map<CommandAction, std::unique_ptr<Sprite>> buttons;
	vector<CommandAction> availableCommands;
	InsertMode insertMode;
	vector<HudButton> clickableCommands;
};


#endif