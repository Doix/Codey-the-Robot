#ifndef BUTTON_H_
#define BUTTON_H_

#include "Sprite.h"
#include "Rectangle.h"

class Button : public Sprite
{
public:
	Button(Graphics& graphics, const std::string& file_path,
		int xLocation, int yLocation,
		int width, int height,
		Rectangle rect);

	~Button();
	bool isClicked(int px, int py);

private:
	const Rectangle rect;

};

#endif // ANIMATED_SPRITE_H_