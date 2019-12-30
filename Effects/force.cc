#include "force.h"
#include "board.h"
#include <memory>

using namespace std;


Force::Force(shared_ptr<AbsBoard> absboard, char block) : Decorator{absboard}, block{block} {}

void Force::apply(Board &b) {
	//Apply the effect to the board
	absboard->apply(b);
	
	if(b.isForce()) {
		//Match heavy to level
        	bool heavy = false;
        	if (b.getLevel() == 3 || b.getLevel() == 4) {
			heavy = true;
		}

		//Find which block they want
        	Block * oldBlock = b.getCurBlock();
        	Block * newBlock = nullptr;
        	if (block == 'I') {
			newBlock = new Iblock{heavy};
		}
        	else if (block == 'J') {
                	newBlock = new Jblock{heavy};
        	}
        	else if (block == 'L') {
                	newBlock = new Lblock{heavy};
        	}
        	else if (block == 'O') {
                	newBlock = new Oblock{heavy};
        	}
        	else if (block == 'S') {
                	newBlock = new Sblock{heavy};
        	}
        	else if (block == 'Z') {
                	newBlock = new Zblock{heavy};
        	}
        	else if (block == 'T') {
                	newBlock = new Tblock{heavy};
        	}
        	else {
                	return;
        	}

        	//Set if valid and otherwise don't move and set board to dead
        	newBlock->setX(oldBlock->getX());
        	newBlock->setY(oldBlock->getY());
        	b.unsetBlock();
        	b.setCurBlock(newBlock);

        	if (b.validMove(0, 0, 0)) {
			b.moveBlock(0, 0, 0);
                	delete oldBlock;
		} else {
                	b.setCurBlock(oldBlock);
                	b.moveBlock(0, 0, 0);
                	delete newBlock;
			b.setDead(true);
        	}
	}
}
Force::~Force() {}
