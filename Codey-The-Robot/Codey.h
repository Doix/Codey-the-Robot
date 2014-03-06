#ifndef CODEY_SPRITE_H_
#define CODEY_SPRITE_H_

#include "ControlledSprite.h"

class Codey : public ControlledSprite
{
public:
	Codey(Graphics& graphics, int x, int y);
	~Codey();
	
	void Codey::draw(Graphics& graphics);
	
protected:
	void initialiseSpriteSheets(Graphics& graphics);
};

#endif //CODEY_SPRITE_H_

