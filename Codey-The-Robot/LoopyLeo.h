#ifndef LOOPY_LEO_H_
#define LOOPY_LEO_H_

#include "Codey.h"

class LoopyLeo : public Codey
{
public:
	LoopyLeo(Graphics& graphics, int x, int y);
	~LoopyLeo();

	void draw(Graphics& graphics);
protected:
	void initialiseSpriteSheets(Graphics& graphics);
};


#endif // LOOPY_LEO_H_