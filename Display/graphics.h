#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "subject.h"
#include "observer.h"
#include "window.h"
#include <string>

using namespace std;

class GraphicsDisplay : public Observer {
	size_t tw; //represents the width of a single tile
	size_t dw; //width of the entire window
	size_t dh; //height of the entire window
	size_t bw; //width of the board
        size_t bh; //height of the board
	Xwindow xw;
	Board *b1; //pointer to Player One's board
        Board *b2; //pointer to Player Two's board
	size_t p1borderL; //distance from left for p1's board
	size_t p2borderL; //distance from left for p2's board
	size_t borderT; 
	size_t space; //represents the space between the two boards
	public:
		GraphicsDisplay(size_t tw, size_t dw, size_t dh, size_t bw, size_t bh, Board *b1, Board *b2);
		~GraphicsDisplay();
		void init();
		void notify(Tile &whoNotified) override;
                void notify(Board &whoNotified) override;
		void applyBlind(size_t player);
		void removeBlind(Board *b);
		void displayWinner(size_t player);
};
#endif
