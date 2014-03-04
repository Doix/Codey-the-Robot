#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include "SDL.h"
#include <map>;

class Graphics
{
public:
	typedef SDL_Texture* TextureId;
	Graphics();
	~Graphics();

	SDL_Texture* loadTexture(std::string path);

	void renderTexture(TextureId texture,
		const SDL_Rect *sourceRect,
		const SDL_Rect* destinationRect) const;

	void flip() const;
	void clear() const;

private:
	std::map<std::string, SDL_Texture*> spriteCache;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // GRAPHICS_H_

