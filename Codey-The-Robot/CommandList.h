#ifndef COMMANDLIST_H_
#define COMMANDLIST_H_

#include "Commands.h"
#include <list>
#include <memory>

class CommandList {
public:
	CommandList();
	~CommandList();

	CommandAction getCommand();
	bool isFinished();
	void addCommand(std::shared_ptr<Command> c);
	void addCommand(std::shared_ptr<Command> c, int pos);
	void restart();
	std::list < std::shared_ptr<Command>>* getList();

private:
	std::list < std::shared_ptr<Command>> commands;
	std::list<std::shared_ptr<Command>>::iterator iterator;
};



#endif