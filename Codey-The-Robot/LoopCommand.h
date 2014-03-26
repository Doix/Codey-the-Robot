#ifndef LOOP_COMMAND_H_
#define LOOP_COMMAND_H_

#include "CommandList.h"

class LoopCommand : public Command
{
public:
	LoopCommand(CommandAction command, int repeatAmount);
	~LoopCommand();
	virtual bool isFinished();
	virtual CommandAction getCommand();
	void addCommand(std::shared_ptr<Command> c);
	std::list < std::shared_ptr<Command>>* getCommands();
	virtual void restart();
	int size();
	int getLoops();

	void increaseLoops();
	void decreaseLoops();

	void removeCommand(int index);
protected:
	CommandAction command;
	int repeatAmount;
	int amountLeft;
	CommandList commands;
};

#endif //LOOP_COMMAND_H_
