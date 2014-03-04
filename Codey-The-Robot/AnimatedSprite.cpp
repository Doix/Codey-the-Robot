#include "AnimatedSprite.h"
#include "Game.h"


AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& file_path,
	int xLocation, int yLocation,
	int width, int height,
	int fps, int numFrames) :

	//Sprite constructor
	Sprite(graphics, file_path,
	xLocation, yLocation,
	width, height),

	//Initialise consts and variables
	frameTime(1000 / fps),
	numFrames(numFrames),
	currentFrame(0),
	elapsedTime(0)
{
}

//empty destructor
AnimatedSprite::~AnimatedSprite()
{
}

//update the frame for the current animation
//update the position of the sourceRect and position of spriteSheet that is being rendered
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
