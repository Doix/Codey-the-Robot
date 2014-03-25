#include "CommandList.h"
#include "LoopCommand.h"
#include <memory>

CommandList::CommandList() {
}

CommandList::~CommandList(){
}

CommandAction CommandList::getCommand() {
	std::shared_ptr<Command> c = *iterator;
	CommandAction ca = c->getCommand();

	if (c->isFinished()) {
		iterator++;
	}

	return ca;
	
}

void CommandList::addCommand(std::shared_ptr<Command> c) {
	commands.push_back(c);
	if (commands.size() == 1){
		iterator = commands.begin();
	}
}

int CommandList::size() {
	return commands.size();
}

bool CommandList::isFinished() {
	return (iterator == commands.end());
}

void CommandList::restart() {
	iterator = commands.begin();
	
	for (auto command : commands) {
		std::shared_ptr<LoopCommand>loopCommand = std::dynamic_pointer_cast<LoopCommand>(command);
		if (loopCommand) {
			loopCommand->restart();
		}
	}
}

void CommandList::deleteCommand(int index) {
	std::list<std::shared_ptr<Command>>::iterator it = commands.begin();
	std::advance(it, index);
	commands.erase(it);
}

std::list < std::shared_ptr<Command>>* CommandList::getList() {
	return &commands;
}