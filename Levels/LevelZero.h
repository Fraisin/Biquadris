#ifndef _LEVEL0_H_
#define _LEVEL0_H_
#include <iostream>
#include <fstream>
#include <string>
#include "AbsLevel.h"
#include "block.h"

using namespace std;

//Derived class from the Abstract Level class for Level 0
class LevelZero : public AbsLevel {
	size_t myLevel;
	ifstream in; //the file the level uses to find the next block
	string source;
	bool random = false;
	public:
		//source represents the name of the file used
		LevelZero(string source);
		void retrieveBlocks() override;
		Block* getNextBlock(size_t pos) override;
		size_t getLevel() override;
		bool isRandom() override;
		string getFileName() override;
		~LevelZero() override;
};
#endif
