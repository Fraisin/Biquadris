#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;
class Tile;
class Board;

class Observer {
	public:
		virtual void notify(Tile &whoFrom) = 0;
		virtual void notify(Board &whoFrom) = 0;
		virtual ~Observer();
};

#endif
