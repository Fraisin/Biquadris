#include <fstream>
#include <iostream>
#include <string>
#include "LevelZero.h"
#include "block.h"

using namespace std;

LevelZero::LevelZero(string source): myLevel{0}, source{source} {}

//this method will convert the given filename into a vector of chars
void LevelZero::retrieveBlocks() {
	char piece;
	in.open(source);
	while (in >> piece) {
		theBlocks.emplace_back(piece);
	}
}

//this method will retrieve the next block from the file
Block* LevelZero::getNextBlock(size_t pos) {
	this->retrieveBlocks();
	size_t i = pos % theBlocks.size();
	if (theBlocks[i] == 'I') return new Iblock{false};	
	else if (theBlocks[i] == 'J') return new Jblock{false};
	else if (theBlocks[i] == 'L') return new Lblock{false};
	else if (theBlocks[i] == 'O') return new Oblock{false};
	else if (theBlocks[i] == 'S') return new Sblock{false};
	else if (theBlocks[i] == 'Z') return new Zblock{false};
	else  return new Tblock{false};
}

size_t LevelZero::getLevel() { return myLevel; }
bool LevelZero::isRandom() { return false; }
string LevelZero::getFileName() { return source; }

LevelZero::~LevelZero() {}
