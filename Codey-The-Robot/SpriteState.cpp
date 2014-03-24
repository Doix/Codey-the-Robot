#include "SpriteState.h"
#include <tuple>

SpriteState::SpriteState(MotionType motionType, DirectionFacing currentDirection) : 
motionType(motionType), 
currentDirection(currentDirection)
{}

bool operator<(const SpriteState& a, const SpriteState& b){	
	auto atie = std::tie(
		a.motionType,
		a.currentDirection
		);
	auto btie = std::tie(
		b.motionType,
		b.currentDirection
		);
	return atie < btie;
}
