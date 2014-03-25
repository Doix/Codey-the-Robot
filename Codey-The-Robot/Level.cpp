#include "Level.h"
#include "Map.h"
#include "Codey.h"
#include "Game.h"
#include "Enemy.h"
#include "ChopperEnemy.h"
#include "DogEnemy.h"
#include "LoopyLeo.h"
#include "Rectangle.h"
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <angelscript.h>
#include "add_on/scriptstdstring/scriptstdstring.h"
#include "add_on/scriptbuilder/scriptbuilder.h"
#include <sstream>
#include <vector>

using std::regex;
using std::string;
using std::sregex_token_iterator;

void MessageCallback(const asSMessageInfo *msg, void *){
	if (msg->section[0] == '\0'){
		printf("%s: %s\n", msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
	else if (msg->row == 0 && msg->col == 0){
		printf("%s: %s : %s\n", msg->section, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
	else{
		printf("%s(%d, %d): %s : %s\n", msg->section, msg->row, msg->col, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	}
}



Level::Level(std::string name, Graphics* graphics) : name(name), graphics(graphics), tutorialComplete(true) {
	map.reset(Map::createMapFromFile(*graphics, "content/levels/" + name + "/map"));
	LoadEntities();

	setupAngelscript();

	tutorialText.reset(new TutorialText(*graphics));

	//setTutorialText("Well, HOWDY there pard'ner, my name\'s Loopy Leo!", "Loopy");
	//setTutorialText("Hi, I\'m Codey and I'm here to save the World", "Codey");
	//setTutorialText("Well I\'ll be dar-niddly-arned. That\'s something I can help you with/nLet me teach you how to Loop!", "Loopy");


	asIScriptModule *mod = engine->GetModule("MyModule");
	asIScriptFunction *func = mod->GetFunctionByDecl("void init()");
	asIScriptContext *ctx = engine->CreateContext();
	ctx->Prepare(func);
	ctx->Execute();
	ctx->Release();

}
Level::~Level() {
	engine->Release();
}



void Level::start() {
	for (auto player : players)
		player->startCommands();
}

void Level::restart() {
	for (auto player : players) {
		player->restart();
	}
}

void Level::LoadEntities() {
	std::ifstream fs("content/levels/" + name + "/entities");
	string line;
	regex re("[\\s,]+");

	int col = 0;
	int row = 0;


	while (std::getline(fs, line)) {
		sregex_token_iterator it(line.begin(), line.end(), re, -1);
		sregex_token_iterator reg_end;
		string object = it->str();

		if (object == "Codey") {
			it++;
			players.push_back(std::shared_ptr<Codey>(new Codey(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}
		else if (object == "EnemyDog") {
			it++;
			enemies.push_back(std::shared_ptr<Enemy>(new DogEnemy(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}
		else if (object == "EnemyChopper") {
			it++;
			enemies.push_back(std::shared_ptr<Enemy>(new ChopperEnemy(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}
		else if (object == "Loopy") {
			it++;
			players.push_back(std::shared_ptr<LoopyLeo>(new LoopyLeo(*graphics,
				std::stoi(it++->str()) * Game::TILE_SIZE,
				std::stoi(it++->str()) * Game::TILE_SIZE)));
		}

	}
}

void Level::update(int elapsedTimeInMs) {
	
	asIScriptModule *mod = engine->GetModule("MyModule");
	asIScriptFunction *func = mod->GetFunctionByDecl("void update()");
	asIScriptContext *ctx = engine->CreateContext();
	ctx->Prepare(func);
	ctx->Execute();
	ctx->Release();
	
	map->update(elapsedTimeInMs);
	for (auto player : players)
		player->update(elapsedTimeInMs, *map);
	for (auto enemy: enemies)
		enemy->update(elapsedTimeInMs, *map);

	for (auto player : players){
		for (auto enemy : enemies) {
			if (enemy->damageRectangle().collidesWith(player->damageRectangle())){
				player->deathSequence();
			}
		}
	}
}

void Level::draw() {
	map->draw(*graphics);
	for (auto player : players)
		player->draw(*graphics);

	for (auto enemy : enemies) 
		enemy->draw(*graphics);

	if (!tutorialComplete){
		tutorialText->draw(*graphics);
	}
	
}


std::vector<std::shared_ptr<Codey>> Level::getPlayers() {
	return players;
}

void print(int i)
{
	printf("%d\n",i);
}

void Level::levelWon() {
	//TODO: SHOW WINSCREEN AND STUFF!
	printf("won!\n");
}

void Level::setTutorialText(string &msg, int speakerId)
{			
	tutorialText->setTutorialText(msg, speakerId);
	tutorialComplete = false;
}

void Level::nextTutorialText(){
	tutorialText->nextTutorialText();
	if (tutorialText->tutorialComplete){
		tutorialComplete = true;
	}
}

void Level::setupAngelscript() {
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
	RegisterStdString(engine);

	engine->RegisterObjectType("Map", 0, asOBJ_REF); // asOBJ_REF because you wanted a reference call
	engine->RegisterObjectBehaviour("Map", asBEHAVE_ADDREF, "void f()", asMETHOD(Map, AddRef), asCALL_THISCALL);
	engine->RegisterObjectBehaviour("Map", asBEHAVE_RELEASE, "void f()", asMETHOD(Map, ReleaseRef), asCALL_THISCALL);
	engine->RegisterObjectMethod("Map", "void setTile(int,int ,int)", asMETHOD(Map, setTile), asCALL_THISCALL);


	engine->RegisterObjectType("Codey", 0, asOBJ_REF); // asOBJ_REF because you wanted a reference call
	engine->RegisterObjectBehaviour("Codey", asBEHAVE_ADDREF, "void f()", asMETHOD(Codey, AddRef), asCALL_THISCALL);
	engine->RegisterObjectBehaviour("Codey", asBEHAVE_RELEASE, "void f()", asMETHOD(Codey, ReleaseRef), asCALL_THISCALL);

	engine->RegisterObjectMethod("Codey", "int getRow()", asMETHOD(Codey, getRow), asCALL_THISCALL);
	engine->RegisterObjectMethod("Codey", "int getCol()", asMETHOD(Codey, getCol), asCALL_THISCALL);

	engine->RegisterObjectType("Enemy", 0, asOBJ_REF); // asOBJ_REF because you wanted a reference call
	engine->RegisterObjectBehaviour("Enemy", asBEHAVE_ADDREF, "void f()", asMETHOD(Enemy, AddRef), asCALL_THISCALL);
	engine->RegisterObjectBehaviour("Enemy", asBEHAVE_RELEASE, "void f()", asMETHOD(Enemy, ReleaseRef), asCALL_THISCALL);

	engine->RegisterObjectMethod("Enemy", "int getRow()", asMETHOD(Enemy, getRow), asCALL_THISCALL);
	engine->RegisterObjectMethod("Enemy", "int getCol()", asMETHOD(Enemy, getCol), asCALL_THISCALL);

	engine->RegisterGlobalProperty("Map map", map.get());
	engine->RegisterGlobalFunction("void print(int)", asFUNCTION(print), asCALL_CDECL);

	engine->RegisterObjectType("Level", 0, asOBJ_REF); // asOBJ_REF because you wanted a reference call
	engine->RegisterObjectBehaviour("Level", asBEHAVE_ADDREF, "void f()", asMETHOD(Enemy, AddRef), asCALL_THISCALL);
	engine->RegisterObjectBehaviour("Level", asBEHAVE_RELEASE, "void f()", asMETHOD(Enemy, ReleaseRef), asCALL_THISCALL);

	engine->RegisterGlobalProperty("Level level", this);
	engine->RegisterObjectMethod("Level", "void win()", asMETHOD(Level, levelWon), asCALL_THISCALL);
	engine->RegisterObjectMethod("Level", "void setTutorialText(const string &in, int speakerId)", asMETHOD(Level, setTutorialText), asCALL_THISCALL);

	int i = 0;
	for (auto player : players) {
		engine->RegisterGlobalProperty(("Codey codey" +
			std::to_string(i)).c_str(), player.get());
		i++;
	}

	i = 0;

	for (auto enemy : enemies) {
		engine->RegisterGlobalProperty(("Enemy enemy" +
			std::to_string(i)).c_str(), enemy.get());
		i++;
	}

	CScriptBuilder builder;
	builder.StartNewModule(engine, "MyModule");
	builder.AddSectionFromFile((string("content/levels/") + name + "/as").c_str());
	builder.BuildModule();
}

