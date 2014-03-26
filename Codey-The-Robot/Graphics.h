#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include "SDL.h"
#include <map>
#include "SDL_ttf.h"
#include <memory>

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
	void drawRectangle(const SDL_Rect* rect);

	//Creates image from font string
	bool renderText(std::string textureText, const int x, const int y, const int width);

private:
	std::map<std::string, SDL_Texture*> spriteCache;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font *gFont = nullptr;
	SDL_Color textColor;
	SDL_Texture* textTexture;
	SDL_Rect textRectClip;
	SDL_Rect textDestinationRect;
	std::string previousText;
	
};

#endif // GRAPHICS_H_

