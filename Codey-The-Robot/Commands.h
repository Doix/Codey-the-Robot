#ifndef COMMAND_H_
#define COMMAND_H_
enum class CommandAction {
		LEFT = 1, 
		RIGHT = 2, 
		UP = 3, 
		DOWN = 4,
		NONE
};



class Command
{
public:
	Command(CommandAction command);
	~Command();
	CommandAction getCommand();
	bool isFinished();
protected:
	CommandAction command;
};


#endif