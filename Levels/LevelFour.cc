#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "LevelFour.h"
#include "block.h"

using namespace std;

//LevelFour constructor
LevelFour::LevelFour(bool random, string source) : myLevel{4}, streak{0}, random{random}, 
	source{source} {
	theBlocks.clear();
}

//left empty as it is not used
void LevelFour::retrieveBlocks() {
	if (random) return;
        char piece;
        in.open(source);
        while (in >> piece) {
                theBlocks.emplace_back(piece);
        }
}

//increase the streak by 1
void LevelFour::increaseStreak() { streak++; }

//this method will retrieve the next block from the file
Block* LevelFour::getNextBlock(size_t pos) {
	size_t i;
        if (random) {
                theBlocks.clear();
		theBlocks = {'S','S','Z','Z','I','J','L','O','T'};
                i = rand() % (theBlocks.size());
        } else {
                this->retrieveBlocks();
                i = pos % theBlocks.size();
        }
	//if # of blocks since last clear = 5, 10, 15, ... return the * block
	if ((streak > 0) && (streak % 5 == 0)) return new Cblock();
	else if (theBlocks[i] == 'I') return new Iblock{true};
        else if (theBlocks[i] == 'J') return new Jblock{true};
        else if (theBlocks[i] == 'L') return new Lblock{true};
        else if (theBlocks[i] == 'O') return new Oblock{true};
        else if (theBlocks[i] == 'S') return new Sblock{true};
        else if (theBlocks[i] == 'Z') return new Zblock{true};
        else return new Tblock{true};
}

size_t LevelFour::getLevel() { return myLevel; }
bool LevelFour::isRandom() { return random; }
string LevelFour::getFileName() { return source; }

void LevelFour::setStreak(size_t streak) { this->streak = streak; }

LevelFour::~LevelFour() {}
