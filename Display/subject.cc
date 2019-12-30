#include "subject.h"
#include <iostream>

void Subject::attach(Observer *o) {
	observers.emplace_back(o);
}

