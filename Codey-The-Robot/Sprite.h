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

	virtual ~Sprite();

	virtual void update(int /*elapsed time in ms*/){}

	void draw(Graphics& graphics, int x, int y) const;

protected:
	SDL_Rect sourceRect;

private:
	SDL_Texture* texture;

};


#endif //SPRITE_H_