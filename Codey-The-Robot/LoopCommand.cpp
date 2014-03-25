#include "LoopCommand.h"
#include "Commands.h"
#include <memory>

LoopCommand::LoopCommand(CommandAction action, int repeatAmount) :
	Command(action),
	repeatAmount(repeatAmount),
	amountLeft(repeatAmount)
{

}

LoopCommand::~LoopCommand() {
}

bool LoopCommand::isFinished(){
	if (amountLeft == 0 && commands.isFinished() || commands.size() == 0)
		return true;
	return false;
}

void LoopCommand::addCommand(std::shared_ptr<Command> c) {
	commands.addCommand(c);
}

void LoopCommand::restart() {
	amountLeft = repeatAmount;
}

CommandAction LoopCommand::getCommand(){
	if (commands.size() > 0) {
		if (commands.isFinished()) {
			amountLeft--;
			commands.restart();
		}
		CommandAction command = commands.getCommand();
		return command;
	}
	else
		return CommandAction::NONE; 
}

std::list < std::shared_ptr<Command>>* LoopCommand::getCommands() {
	return commands.getList();
}