#include "blind.h"
#include "board.h"
#include <memory>

using namespace std;


Blind::Blind(shared_ptr<AbsBoard> absboard) : Decorator{absboard} {}

void Blind::apply(Board &b) {
	absboard->apply(b);
}

Blind::~Blind() {}
