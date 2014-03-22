#ifndef MAP_CODEY_SPRITE_H_
#define MAP_CODEY_SPRITE_H_

#include "Codey.h"

class MapCodey : public Codey
{
public:
	MapCodey(Graphics& graphics, int x, int y);
	~MapCodey();
	void update(int elapsedTimeMs);
protected:

};

#endif //MAP_CODEY_SPRITE_H_

