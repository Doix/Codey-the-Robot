#ifndef COMMAND_H_
#define COMMAND_H_
enum class CommandAction {
		TURN_LEFT, 
		TURN_RIGHT, 
		MOVE_FORWARD , 
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