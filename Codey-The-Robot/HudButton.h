#ifndef HUD_BUTTON_H_
#define HUD_BUTTON_H_

#include "Sprite.h"
#include "Rectangle.h"
#include "Button.h"
#include <memory>
#include "Commands.h"

class HudButton : public Button
{
public:

	HudButton(Sprite& sprite, Rectangle rect, std::shared_ptr<Command>);

	~HudButton();
	std::shared_ptr<Command> command;
private:

};

#endif // HUD_BUTTON_H_