#include "Graphics.h"
#include "SDL.h"
#include "SDL_image.h"

#include <stdio.h>
#include <string>

//Constants
namespace{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
}

Graphics::Graphics()
{
	//create window
	window = SDL_CreateWindow(
		"Codey the Robot Saves the World!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0
		);

	if (window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	if (renderer == nullptr) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	//Look at  "http://wiki.libsdl.org/MigrationGuide" for new SDL2.0 features - SDL_Surface now deprecated for the main window	

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	for (auto& entry : spriteCache) {
		SDL_DestroyTexture(entry.second);
	}

	IMG_Quit();
}

/**
* Create an SDL_texture from an image file
*
Adapted from: http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php

*/

SDL_Texture* Graphics::loadTexture(std::string path)
{
	if (spriteCache.count(path.c_str()) == 0){
		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
			spriteCache[path.c_str()] = newTexture;
		}
	}

	return spriteCache[path.c_str()];
}


//Draw a texture at a destination rectangle

void Graphics::renderTexture(
	TextureId texture,
	const SDL_Rect* sourceRect,
	const SDL_Rect* destinationRect) const
{
	SDL_RenderCopy(renderer, texture, sourceRect, destinationRect);
}

void Graphics::flip() const
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear() const
{
	SDL_RenderClear(renderer);
}
