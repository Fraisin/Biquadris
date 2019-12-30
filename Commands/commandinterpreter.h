#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>


class CommandInterpreter {
	private:
		std::vector<std::string> commands =
	       		{"quit", "left", "right", "down", "clockwise", "counterclockwise", 
			"drop", "levelup", "leveldown", "norandom", "random",
			"sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", 
			"blind", "force", "heavy", "rename", "keystrokeson"};
		std::vector<std::string> renamedcommands =
		 	{"quit", "left", "right", "down", "clockwise", "counterclockwise",
	                 "drop", "levelup", "leveldown", "norandom", "random",
	                 "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart",
			 "blind", "force", "heavy", "rename", "keystrokeson"};
		
	
	
	public:	
		std::string readinput(std::string input);
		int getmult(std::string input);
		void renamecommand(std::string oldcommand, std::string newcommand);

};



#endif
