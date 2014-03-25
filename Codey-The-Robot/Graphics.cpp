#include "Graphics.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

#include <stdio.h> 
#include <string>

//Constants
namespace{
	const int SCREEN_WIDTH = 940;
	const int SCREEN_HEIGHT = 480;
}

//Graphics Constructor
//Initialises the window, renderer and starts up the SDL_IMG tool to allow for different PNG types
Graphics::Graphics()
{
	//create window
	window = SDL_CreateWindow(
		"Codey the Robot Saves the World!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0
		);
	
	//check for null window pointer, i.e. failed
	if (window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//check for null renderer pointer, i.e. failed
	if (renderer == nullptr) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize renderer color (default set to white)
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;

	//Check if false returned
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	textColor = { 0, 0, 0 };

	// Open the font
	gFont = TTF_OpenFont("content/Font/ITCKRIST.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

//destructor, ends SDL_IMG tool and destroys window, renderer and any spriteCaches
Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	for (auto& entry : spriteCache) {
		SDL_DestroyTexture(entry.second);
	}

	//Free global font
	TTF_CloseFont(gFont);
	gFont = nullptr;

	IMG_Quit();
	TTF_Quit();	
}

/**
* Create an SDL_texture from an image file
*
Adapted from: http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php

*/

//Reads in images and creates textures and add them to sprite cache 
//Does not read if image already read in (based on the path)
//returns texture
SDL_Texture* Graphics::loadTexture(std::string path)
{
	//check if image already read
	if (spriteCache.count(path.c_str()) == 0){
		//The final texture to be returned
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		//check if unable to load the picture (e.g. Path invalid)
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

			//Free old loaded surface and free the memory
			SDL_FreeSurface(loadedSurface);

			//add new texture to the spriteCache
			spriteCache[path.c_str()] = newTexture;
		}
	}
	//return texture based on file path
	return spriteCache[path.c_str()];
}



void Graphics::drawRectangle(const SDL_Rect* rect) {
	SDL_RenderDrawRect(renderer, rect);
}

bool Graphics::renderText(std::string textureText, const int x, const int y, const int width){
	
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor, width);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		//Create texture from surface pixels
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Get text dimensions
			SDL_Rect destinationRect;
			destinationRect.x = x;
			destinationRect.y = y;
			destinationRect.w = textSurface->w;
			destinationRect.h = textSurface->h;

			renderTexture(
				textTexture,
				&textSurface->clip_rect,
				&destinationRect);
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	return true;
	
}

//Draw a texture at a destination rectangle based on a source rectangle
//LoadTexture method must be used to get the texture input
void Graphics::renderTexture(
	TextureId texture,
	const SDL_Rect* sourceRect,
	const SDL_Rect* destinationRect) const
{
	//render image to render target at destination rectangle
	SDL_RenderCopy(renderer, texture, sourceRect, destinationRect);
}

//Present the (background) render to the window
void Graphics::flip() const
{
	SDL_RenderPresent(renderer);
}

//Clear the current (background) render
void Graphics::clear() const
{
	SDL_RenderClear(renderer);
}
