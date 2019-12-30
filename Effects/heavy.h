#ifndef _HEAVY_H_
#define _HEAVY_H_
#include "AbsBoard.h"
#include "decorator.h"
#include <memory>

using namespace std;

class Heavy: public Decorator {
	public:
		Heavy(shared_ptr<AbsBoard> absboard);
		void apply(Board &b) override;
		~Heavy();
};

#endif
