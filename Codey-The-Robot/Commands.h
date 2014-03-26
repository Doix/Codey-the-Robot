#ifndef COMMAND_H_
#define COMMAND_H_
enum class CommandAction {
		TURN_LEFT, 
		TURN_RIGHT, 
		MOVE_FORWARD , 
		LOOP,
		NONE_SELECTED,
		LOOP_UP,
		LOOP_DOWN,
		NONE
};



class Command
{
public:
	Command(CommandAction command);
	~Command();
	virtual CommandAction getCommand();
	virtual bool isFinished();
	virtual void restart() {};
protected:
	CommandAction command;
};


#endif