#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "LevelTwo.h"
#include "block.h"

using namespace std;

//LevelTwo constructor
LevelTwo::LevelTwo(bool random, string source) : myLevel{2}, random{random}, source{source} {}

//left empty as it is not used
void LevelTwo::retrieveBlocks() {
	if (random) return;
        char piece;
        in.open(source);
        while (in >> piece) {
                theBlocks.emplace_back(piece);
        }
}

//this method will retrieve the next block from the file
Block* LevelTwo::getNextBlock(size_t pos) {
	size_t i;
        if (random) {
		theBlocks.clear();
                theBlocks = {'S','Z','I','J','L','O','T'};
		i = rand() % (theBlocks.size());
        } else {
                this->retrieveBlocks();
                i = pos % theBlocks.size();
        }
	if (theBlocks[i] == 'I') return new Iblock{false};
        else if (theBlocks[i] == 'J') return new Jblock{false};
        else if (theBlocks[i] == 'L') return new Lblock{false};
        else if (theBlocks[i] == 'O') return new Oblock{false};
        else if (theBlocks[i] == 'S') return new Sblock{false};
        else if (theBlocks[i] == 'Z') return new Zblock{false};
        else  return new Tblock{false};
}

size_t LevelTwo::getLevel() { return myLevel; }
bool LevelTwo::isRandom() { return false; }
string LevelTwo::getFileName() { return source; }

LevelTwo::~LevelTwo() {}
