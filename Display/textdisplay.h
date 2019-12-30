#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "tileinfo.h"
using namespace std;
class Tile; //forward declaration of Tile
class Block;

class TextDisplay: public Observer {
	size_t width, height;	
	vector<vector<char>> p1Display;
	vector<vector<char>> p2Display;
	//these two vectors represent the preview display at the bottom
	vector<char> p1Preview;
	vector<char> p2Preview;
	Board *b1; //pointer to Player One's board
	Board *b2; //pointer to Player Two's board
	public:
		TextDisplay(size_t width, size_t height, Board *b1, Board *b2);
		void notify(Tile &whoNotified) override;
		void notify(Board &whoNotified) override;
		void blind(size_t player, ostream &out) const;
		void changePreviews(Block* nextBlock, size_t player);
		void printPreviews(ostream &out) const;
		friend ostream &operator<<(ostream &out, const TextDisplay &td);
		~TextDisplay();
};
#endif
