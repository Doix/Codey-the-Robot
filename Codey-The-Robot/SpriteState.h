#ifndef SPRITE_STATE_H_
#define SPRITE_STATE_H_

enum class MotionType { STANDING, WALKING_LEFT, WALKING_RIGHT, WALKING_UP, WALKING_DOWN, DEAD, DYING };

class SpriteState
{
public:
	MotionType motionType;

	SpriteState(MotionType motionType = MotionType::STANDING);

	friend bool operator<(const SpriteState& a, const SpriteState& b);

};

#endif //SPRITE_STATE_H_