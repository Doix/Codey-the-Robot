#include "Codey.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "MapCodey.h"
#include "Rectangle.h"



MapCodey::MapCodey(Graphics& graphics, int x, int y) : Codey(graphics, x, y)
{

}

MapCodey::~MapCodey()
{
}

void MapCodey::moveTo(int x, int y) {
	originX = x;
	originY = y;
}

void MapCodey::update(int elapsedTimeMs,int xoffset){
	sprites[getSpriteState()]->update(elapsedTimeMs);
	PosX = originX - xoffset;
	PosY = originY;
}