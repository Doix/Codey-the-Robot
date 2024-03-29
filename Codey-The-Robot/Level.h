#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include "Graphics.h"
#include <memory>
#include "Map.h"
#include "Enemy.h"
#include "Codey.h"
#include "angelscript.h"
#include "TutorialText.h"
#include "MessageBox.h"

using std::string;

class Level
{
public:
	Level(std::string name, Graphics* graphics);
	~Level();
	void update(int elapsedTimeInMs);
	void draw();
	void drawTutorial();
	void drawWinScreen();
	std::vector < std::shared_ptr<Codey>> getPlayers();
	void start();
	void levelWon();
	void setTutorialText(string &msg, int speakerId);

	void nextTutorialText();
	bool tutorialComplete;
	void restart();

	bool levelBeaten;

private:
	Graphics* graphics;
	std::unique_ptr<Map> map;
	string name;
	std::vector <std::shared_ptr<Codey>> players;;
	std::vector<std::shared_ptr<ControlledSprite>> enemies;
	void LoadEntities();
	asIScriptEngine* engine;
	void setupAngelscript();

	std::unique_ptr<MessageBox> winMessage;
	
	std::unique_ptr<TutorialText> tutorialText;
};

#endif // LEVEL_H_

