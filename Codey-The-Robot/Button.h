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

	Button(Sprite& sprite, Rectangle rect);

	~Button();
	bool isClicked(int px, int py);

protected:
	const Rectangle rect;

};

#endif // BUTTON_H_