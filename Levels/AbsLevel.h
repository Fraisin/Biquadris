#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "cblock.h"

using namespace std;

class AbsLevel {
	//a vector of characters that represents the sequence of blocks
	protected:
		vector<char> theBlocks;
	public:
		//pure virtual method that will be overriden by the concrete levels
		virtual void retrieveBlocks() = 0;
		virtual Block* getNextBlock(size_t pos) = 0;
		virtual size_t getLevel() = 0;
		virtual bool isRandom() = 0;
		virtual string getFileName() = 0;
		virtual ~AbsLevel();
};
#endif
