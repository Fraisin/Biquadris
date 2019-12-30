#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "LevelThree.h"
#include "block.h"

using namespace std;

//LevelThree constructor
LevelThree::LevelThree(bool random, string source) : myLevel{3}, random{random}, source{source} {}

//if the Level is not random, retrieve the blocks from the specified file
void LevelThree::retrieveBlocks() {
	if (random) return;
	char piece;
	in.open(source);
        while (in >> piece) {
                theBlocks.emplace_back(piece);
        }
}

//this method will retrieve the next block from the file
Block* LevelThree::getNextBlock(size_t pos) {
	size_t i;
	if (random) {
		theBlocks.clear();
        	theBlocks = {'S','S','Z','Z','I','J','L','O','T'};
        	i = rand() % (theBlocks.size());
	} else {
		this->retrieveBlocks();
		i = pos % theBlocks.size();
	}
        if (theBlocks[i] == 'I') return new Iblock{true};
        else if (theBlocks[i] == 'J') return new Jblock{true};
        else if (theBlocks[i] == 'L') return new Lblock{true};
        else if (theBlocks[i] == 'O') return new Oblock{true};
        else if (theBlocks[i] == 'S') return new Sblock{true};
        else if (theBlocks[i] == 'Z') return new Zblock{true};
        else  return new Tblock{true};
}

size_t LevelThree::getLevel() { return myLevel; }
bool LevelThree::isRandom() { return random; }
string LevelThree::getFileName() { return source; }

LevelThree::~LevelThree() {}
