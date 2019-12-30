#include <iostream>
#include "subject.h"
#include "observer.h"
#include "tile.h"
#include "tileinfo.h"

using namespace std;

//Tile Constructor
Tile::Tile(size_t x, size_t y, Board *myBoard) : x{x}, y{y}, occupied{false},  myBoard{myBoard} {}

//places piece of given block on this tile
void Tile::setPiece(char piece) {
	myPiece = piece;
	occupied = true;
	//notify the Displays that we've just been placed
	notifyObservers();
}

void Tile::unsetPiece() {
	myPiece = ' ';
	occupied = false;
	notifyObservers();
}

size_t Tile::getX() { return x; }
size_t Tile::getY() { return y; }
void Tile::setX(size_t x) { this->x = x; }
void Tile::setY(size_t y) { this->y = y; }

//override Subject's notifyObservers() method
void Tile::notifyObservers() {
	for (auto &ob : observers) ob->notify(*this);
}

TileInfo Tile::getInfo() const {
	return TileInfo{x, y, myPiece, occupied, myBoard};
}
