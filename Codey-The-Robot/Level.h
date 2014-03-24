#ifndef LEVLE_H_
#define LEVLE_H_

#include <string>
#include "Graphics.h"
#include <memory>
#include "Map.h"
#include "Enemy.h"
#include "Codey.h"

class Level
{
public:
	Level(std::string name, Graphics* graphics);
	~Level();
	void update(int elapsedTimeInMs);
	void draw();
	std::vector < std::shared_ptr<Codey>> getPlayers();
	void start();

private:
	Graphics* graphics;
	std::unique_ptr<Map> map;
	std::string name;
	std::vector < std::shared_ptr<Codey>> players;;
	std::vector<std::shared_ptr<Enemy>> enemies;
	void LoadEntities();

};

#endif // LEVLE_H_

