#ifndef GRAPHICS_H_
#define GRAPHICS_H_



#include <string>
#include "SDL.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Texture* loadTexture(std::string path);

	void renderTexture(SDL_Texture *texture,
		const SDL_Rect *sourceRect,
		const SDL_Rect* destinationRect) const;

	void flip() const;
	void clear() const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // GRAPHICS_H_

