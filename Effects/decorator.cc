#include "AbsLevel.h"
#include "decorator.h"
#include <memory>

Decorator::Decorator(shared_ptr<AbsBoard> absboard) : absboard{absboard} {}

void Decorator::apply(Board &b) {
        absboard->apply(b);
}

Decorator::~Decorator() {}
