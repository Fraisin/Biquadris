#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include <iostream>
#include <fstream>
#include <string>
#include "AbsLevel.h"
#include "block.h"

using namespace std;

//Derived class from the Abstract Level class for Level 0
class LevelFour : public AbsLevel {
                size_t myLevel, streak;
                bool random = true; //indicates whether the level is random or not
                ifstream in; //file that this level could potentially use
                string source;
        public:
                LevelFour(bool random, string source = "");
		void retrieveBlocks() override;
                Block* getNextBlock(size_t pos) override;
                size_t getLevel() override;
		void increaseStreak();
		void setStreak(size_t streak);
		bool isRandom() override;
                string getFileName() override;
                ~LevelFour() override;
};
#endif
