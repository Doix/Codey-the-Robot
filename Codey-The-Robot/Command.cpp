#include "Commands.h"


Command::Command(CommandAction command) : command(command)  {

}

//Destructor - release the sprite not necessary, scoped pointers!
Command::~Command() {
}

bool Command::isFinished(){
	return true;
}

CommandAction Command::getCommand(){
	return command;
}
