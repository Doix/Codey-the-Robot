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
	void LoopCommand::addCommand(std::shared_ptr<Command> c);
protected:
	CommandAction command;
	int repeatAmount;
	int amountLeft;
	CommandList commands;
};

#endif //LOOP_COMMAND_H_
