#include "HudButton.h"
#include "Game.h"


HudButton::HudButton(Sprite& sprite, Rectangle rect,std::shared_ptr<Command> command) : 
Button(sprite, rect), command(command){
}

//empty destructor
HudButton::~HudButton()
{
}