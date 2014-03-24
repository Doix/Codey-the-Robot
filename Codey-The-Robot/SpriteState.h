#ifndef SPRITE_STATE_H_
#define SPRITE_STATE_H_

enum class MotionType {
	STANDING,
	WALKING,
	DEAD,
	DYING
};

enum class DirectionFacing{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class SpriteState 
{
public:
	MotionType motionType;
	DirectionFacing currentDirection;

	SpriteState(MotionType motionType = MotionType::STANDING, DirectionFacing currentDirection = DirectionFacing::RIGHT);

	friend bool operator<(const SpriteState& a, const SpriteState& b);
};

#endif //SPRITE_STATE_H_