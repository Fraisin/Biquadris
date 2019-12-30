#include "heavy.h"
#include "board.h"
#include <memory>

using namespace std;


Heavy::Heavy(shared_ptr<AbsBoard> absboard) : Decorator{absboard} {}

void Heavy::apply(Board &b) {
	//Apply the effect to the board
	absboard->apply(b);
	
	if (b.isHeavy()) {
		//Set the current block to be effect heavy
		b.getCurBlock()->setEffectHeavy(true);
	}
}

Heavy::~Heavy() {}
