#include "CommandList.h"


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
		restart();
	}
}

bool CommandList::isFinished() {
	return (iterator != commands.end());
}

void CommandList::restart() {
	iterator = commands.begin();
}

std::list < std::shared_ptr<Command>>* CommandList::getList() {
	return &commands;
}