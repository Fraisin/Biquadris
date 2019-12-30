#ifndef __INFO_H__
#define __INFO_H__

class Board;

struct TileInfo {
	size_t x, y;
	char myPiece;
	bool occupied;
	Board *myBoard;	
};

#endif
