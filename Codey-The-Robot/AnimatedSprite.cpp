#include "AnimatedSprite.h"
#include "Game.h"


AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& file_path,
	int xLocation, int yLocation,
	int width, int height,
	int fps, int numFrames) :
	Sprite(graphics, file_path,
	xLocation, yLocation,
	width, height),
	frameTime(1000 / fps),
	numFrames(numFrames),
	currentFrame(0),
	elapsedTime(0)
{
}


AnimatedSprite::~AnimatedSprite()
{
}


void AnimatedSprite::update(int elapsedTimeInMs){
	elapsedTime += elapsedTimeInMs;

	if (elapsedTime > frameTime){
		++currentFrame;
		elapsedTime = 0;
		if (currentFrame < numFrames){
			sourceRect.x += Game::TILE_SIZE;
		}
		else{
			sourceRect.x -= Game::TILE_SIZE * (numFrames - 1);
			currentFrame = 0;
		}
	}
}
