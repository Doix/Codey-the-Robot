#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(Graphics& graphics, const std::string& file_path,
		int xLocation, int yLocation,
		int width, int height, 
		int fps , int numFrames);

	~AnimatedSprite();

	void update(int elapsedTimeInMs);
private:
	
	const int frameTime;
	const int numFrames;
	int currentFrame;
	int elapsedTime; //Elapsed time since the last frame change

};

#endif // ANIMATED_SPRITE_H_