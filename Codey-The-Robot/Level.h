#ifndef LEVLE_H_
#define LEVLE_H_

#include <string>
#include "Graphics.h"
#include <memory>
#include "Map.h"
#include "Enemy.h"
#include "Codey.h"
#include "angelscript.h"

using std::string;

class Level
{
public:
	Level(std::string name, Graphics* graphics);
	~Level();
	void update(int elapsedTimeInMs);
	void draw();
	std::vector < std::shared_ptr<Codey>> getPlayers();
	void start();
	void levelWon();
	void setTutorialText(string &msg);

	void nextTutorialText();

private:
	Graphics* graphics;
	std::unique_ptr<Map> map;
	string name;
	std::vector < std::shared_ptr<Codey>> players;;
	std::vector<std::shared_ptr<Enemy>> enemies;
	void LoadEntities();
	asIScriptEngine* engine;
	void setupAngelscript();

	std::vector<std::string> tutorialText;
	int tutorialLine;
};

#endif // LEVLE_H_

