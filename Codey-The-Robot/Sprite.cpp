#include "Sprite.h"
#include "Graphics.h"
#include "SDL.h"


Sprite::Sprite(Graphics& graphics,
	const std::string& filePath, 
	int xLocation, int yLocation, 
	int width, int height)
{
	texture = graphics.loadTexture(filePath.c_str());

	sourceRect.x = xLocation;
	sourceRect.y = yLocation;
	sourceRect.w = width;
	sourceRect.h = height;
}


Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, int x, int y) const
{
	SDL_Rect destinationRect;
	destinationRect.x = x;
	destinationRect.y = y;
	destinationRect.w = sourceRect.w;
	destinationRect.h = sourceRect.h;

	graphics.renderTexture(texture, &sourceRect, &destinationRect);
}
