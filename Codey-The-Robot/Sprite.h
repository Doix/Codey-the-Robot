#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include "SDL.h"


class Graphics;

class Sprite
{
public:
	Sprite(Graphics& graphics, const std::string& file_path, 
		int xLocation, int yLocation, 
		int width, int height);

	~Sprite();

	void draw(Graphics& graphics, int x, int y) const;
private:
	SDL_Texture* texture;
	SDL_Rect sourceRect;

};


#endif //SPRITE_H_