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
	if (amountLeft == 0 && commands.isFinished())
		return true;
	return false;
}

void LoopCommand::addCommand(std::shared_ptr<Command> c) {
	commands.addCommand(c);
}

CommandAction LoopCommand::getCommand(){
	if (commands.isFinished()) {
		amountLeft--;
		commands.restart();
	}

	return commands.getCommand();
}
