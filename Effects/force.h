#ifndef _FORCE_H_
#define _FORCE_H_
#include "AbsBoard.h"
#include "decorator.h"
#include <memory>

using namespace std;

class Force: public Decorator {
	char block; //Char corresponding to the block that should be forced
	public:
		Force(shared_ptr<AbsBoard> absboard, char block);
		void apply(Board &b) override;
		~Force();
};

#endif
