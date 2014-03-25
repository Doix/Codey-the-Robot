#ifndef CODEY_SPRITE_H_
#define CODEY_SPRITE_H_

#include "ControlledSprite.h"

class Codey : public ControlledSprite
{
public:
	Codey(Graphics& graphics, int x, int y);
	~Codey();
	void update(int elapsedTimeMs, const Map& map);
	void draw(Graphics& graphics);
	void deathSequence();
	
protected:
	void resetSprite();
	virtual void initialiseSpriteSheets(Graphics& graphics);
	bool startedDeathSequence;
	bool finishedDying;
	int deathSeqTimer;
};
Codey *Codey_Factory(Graphics& graphics, int x, int y);
#endif //CODEY_SPRITE_H_

