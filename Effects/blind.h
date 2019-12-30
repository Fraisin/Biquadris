#ifndef _BLIND_H_
#define _BLIND_H_
#include "AbsBoard.h"
#include "decorator.h"
#include <memory>

using namespace std;

class Blind: public Decorator {
	public:
		Blind(shared_ptr<AbsBoard> absboard);
		void apply(Board &b) override;
		~Blind();
};

#endif
