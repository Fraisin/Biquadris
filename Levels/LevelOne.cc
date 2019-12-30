#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include "LevelOne.h"
#include "block.h"

using namespace std;

//LevelOne constructor
LevelOne::LevelOne(bool random, string source) : myLevel{1}, random{random}, source{source} {}       

//left empty as it is not used
void LevelOne::retrieveBlocks() {
	if (random) return;
        char piece;
        in.open(source);
        while (in >> piece) {
                theBlocks.emplace_back(piece);
        }
}

//this method will retrieve the next block from the file
Block* LevelOne::getNextBlock(size_t pos) {
	size_t i;
        if (random) {
		theBlocks.clear();
                theBlocks = {'S','Z','I','I','J','J','L','L','O','O','T','T'};
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

size_t LevelOne::getLevel() { return myLevel; }
bool LevelOne::isRandom() { return false; }
string LevelOne::getFileName() { return source; }

LevelOne::~LevelOne() {}
