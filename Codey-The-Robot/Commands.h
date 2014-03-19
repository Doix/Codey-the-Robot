#ifndef COMMAND_H_
#define COMMAND_H_
enum class CommandAction {
		LEFT, 
		RIGHT, 
		UP , 
		DOWN,
		LOOP,
		NONE
};



class Command
{
public:
	Command(CommandAction command);
	~Command();
	virtual CommandAction getCommand();
	virtual bool isFinished();
protected:
	CommandAction command;
};


#endif