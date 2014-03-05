#include "SpriteState.h"
#include <tuple>

SpriteState::SpriteState(MotionType motionType){
	this->motionType = motionType;
}

bool operator<(const SpriteState& a, const SpriteState& b){
	auto atie = std::tie(
		a.motionType
		);
	auto btie = std::tie(
		b.motionType
		);
	return atie < btie;
}