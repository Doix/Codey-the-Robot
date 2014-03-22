#include "Codey.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "MapCodey.h"



MapCodey::MapCodey(Graphics& graphics, int x, int y) : Codey(graphics, x, y)
{

}

MapCodey::~MapCodey()
{
}


void MapCodey::update(int elapsedTimeMs){
	sprites[getSpriteState()]->update(elapsedTimeMs);
}