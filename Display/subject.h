#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
#include "tileinfo.h"

using namespace std;

class Subject {
	protected:
		vector<Observer*> observers;
	public:
		void attach(Observer *o);
		void virtual notifyObservers() = 0;
};

#endif
