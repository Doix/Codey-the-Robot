#include "Codey.h"
#include "Game.h"
#include "AnimatedSprite.h"

namespace{
	const int CODEY_TILE_SIZE = 80;
	const std::string CODEY_FILE_PATH = "content/codey.png";
	const std::string CODEY_REVERSE_FILE_PATH = "content/codeyReverse.png";
	const int FPS = 15;
	const int DEATH_SEQ_TIME = 1500;
}

Codey::Codey(Graphics& graphics, int x, int y) : ControlledSprite(graphics, x, y)
{
	//initialise the AnimatedSprite for the player
	initialiseSpriteSheets(graphics);
}

Codey *Codey_Factory(Graphics& graphics, int x, int y) {
	return new Codey(graphics, x, y);
}

Codey::~Codey()
{
}

void Codey::initialiseSpriteSheets(Graphics& graphics){
	sprites[SpriteState(MotionType::STANDING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 2));

	sprites[SpriteState(MotionType::WALKING_LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_REVERSE_FILE_PATH,
		2 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 6));

	sprites[SpriteState(MotionType::WALKING_RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		2 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 6));

	sprites[SpriteState(MotionType::WALKING_UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0 * CODEY_TILE_SIZE, 5 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 6));

	sprites[SpriteState(MotionType::WALKING_DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		6 * CODEY_TILE_SIZE, 5 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 2));

	sprites[SpriteState(MotionType::DEAD)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		9 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 1));

	sprites[SpriteState(MotionType::DYING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0 * CODEY_TILE_SIZE, 2 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, FPS, 2));
}

void Codey::resetSprite(){
	ControlledSprite::resetSprite();
	startedDeathSequence = false;
	finishedDying = false;
	deathSeqTimer = 0;
}

void Codey::update(int elapsedTimeMs, const Map& map){
	if (startedDeathSequence && !finishedDying){
		deathSeqTimer += elapsedTimeMs;
		if (deathSeqTimer > DEATH_SEQ_TIME){
			finishedDying = true;
			currentMotion = MotionType::DEAD;
			busy = false;
		}
	}
	ControlledSprite::update(elapsedTimeMs, map);
}

void Codey::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX, PosY, CODEY_TILE_SIZE, CODEY_TILE_SIZE);
}

void Codey::deathSequence(){
	if (!startedDeathSequence){
		startedDeathSequence = true;	
		deathSeqTimer = 0;
		started = false;//stop current commands
		currentMotion = MotionType::DYING;		
		printf("Codey is going to die now! :'( \n");
	}
	
}