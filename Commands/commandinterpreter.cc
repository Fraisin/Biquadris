#include "commandinterpreter.h"

using namespace std;


//case sensitive checker to see if main starts with match. works if match == main and does not work if 
//whitespace does not match but since the way we read the strings in, there will never be trailing whitespace 
//or whitespace preceding any string
bool startswith(string main, string match) {
	if (main.find(match) != 0) {
		return false;
	} 
	return true;
}


//if input command is ambiguous or wrong, will return ERROR
//otherwise will return the appropriate command e.g. "left", "right" ......
string CommandInterpreter::readinput(string input) {
	int matches = 0;
	int multi;
	stringstream ss;
	ss << input;
	string givencommand;
	string toreturn;
	if (ss >> multi) {
		if (!(ss >> givencommand)) {
			toreturn = "ERROR";
		} 
		if (multi < 0) {
			toreturn = "ERROR";
		} 
	
	} else {
		givencommand = input;
		if (givencommand.find("rename") != std::string::npos){
			return givencommand;
		}
	}
	

	int length = this->commands.size();
	for (int i = 0; i < length; ++i) {
		string validcommand = this->renamedcommands[i];
		bool found = startswith(validcommand, givencommand);
		if (found) {
			matches += 1;
			toreturn = this->commands[i];
		}
	}
	if (matches == 1) {
		return toreturn;
	}
	return "ERROR";	
}


int CommandInterpreter::getmult(string input) {
	stringstream ss;
	ss << input;
	int toreturn;
	if (!(ss >> toreturn)) {
		return 1;
	} 
	return toreturn;
}

void CommandInterpreter::renamecommand(string oldcommand, string newcommand) {
	int length = this->renamedcommands.size();
	//first check if newcommand already exists or is too vague
	int matches = 0;
	for (int i = 0; i < length; ++i) {
		string currentrenamedcommand = renamedcommands[i];
		bool found = startswith(currentrenamedcommand, newcommand);
		if (found) {
			matches += 1;
		}
	}
	if (matches != 0) {
		cout << "ERROR! Cannot rename command to existing or vague command" << endl;
		return;
	}
	//modify the command in the vecotr renamedcommands to be the newcommand
	for (int i = 0; i < length; ++i) {
		if (this->renamedcommands[i] == oldcommand) {
			this->renamedcommands[i] = newcommand;
		}
	}
	
}
