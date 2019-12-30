#ifndef TILE_H
#define TILE_H
#include "subject.h"
#include "observer.h"
#include "tileinfo.h"
class Board; //forward declaration of Board

class Tile : public Subject {
	size_t x, y;
	char myPiece;
	bool occupied;
	Board *myBoard; //pointer to which Board this tile is on
	public:
		Tile(size_t x, size_t y, Board *myBoard);
		//places a tile of a certain block
		void setPiece(char piece);
		void unsetPiece();
		void notifyObservers() override;
		void setX(size_t x);
		void setY(size_t y);
		size_t getX();
		size_t getY();
		//allows the caller to get all the tile's information
		TileInfo getInfo() const;
};
#endif
