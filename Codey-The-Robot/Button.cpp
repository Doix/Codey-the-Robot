#include "Button.h"
#include "Game.h"


Button::Button(Graphics& graphics, const std::string& file_path,
	int xLocation, int yLocation,
	int width, int height,
	Rectangle rect) :

	//Sprite constructor
	Sprite(graphics, file_path,
	xLocation, yLocation,
	width, height),
	rect(rect)
{
}

//empty destructor
Button::~Button()
{
}


bool Button::isClicked(int px, int py){
	return rect.contains(px, py);
}
