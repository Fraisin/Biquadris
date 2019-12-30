#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "textdisplay.h"
#include "observer.h"
#include "subject.h"
#include "tileinfo.h"
#include "tile.h"
#include "board.h"

using namespace std;

//TextDisplay Constructor
TextDisplay::TextDisplay(size_t width, size_t height, Board *b1, Board *b2) :
       	width{width}, height{height}, b1{b1}, b2{b2} {
	       //initialize the board displays
	       for (size_t i = 0; i < height; i++) {
		       vector<char> row;
		       p1Display.emplace_back(row);
		       p2Display.emplace_back(row);
		       for (size_t j = 0; j < width; j++) {
			       p1Display[i].emplace_back(' ');
			       p2Display[i].emplace_back(' ');
		       }
	       }
	       //initialize the previews for nextblock
	       for (size_t i = 0; i < 8; i++) {
		       p1Preview.emplace_back(' ');
		       p2Preview.emplace_back(' ');
	       }
}

//notify the TextDisplay if a tile has changed
void TextDisplay::notify(Tile &whoNotified) {
	size_t r = whoNotified.getInfo().x;
	size_t c = whoNotified.getInfo().y;
	char piece = whoNotified.getInfo().myPiece;
	Board *b = whoNotified.getInfo().myBoard;
	if (b == b1) p1Display[r][c] = piece;
	else if (b == b2) p2Display[r][c] = piece;
}

//if a player is blind, this method blinds the player that is currently blind
void TextDisplay::blind(size_t player, ostream &out) const {
	string spaceBetweenBoards;
	size_t spacebetween = 8;
	for (size_t i = 0; i < spacebetween; i++) spaceBetweenBoards += " ";
	vector<vector<char>> displayCopy;
	if (player == 1) displayCopy = p1Display;
	else if (player == 2) displayCopy = p2Display;
	for (size_t x = 0; x < height; x++) {
		for (size_t y = 0; y < width; y++) {
			if ((x >= 5 && x <= 14) && (y >= 2 && y <= 8)) {
				displayCopy[x][y] = '?';
			}
		}
	}
	//now that the display copy has been created, print it out
	for (size_t x = 0; x < height; x++) {
		for (size_t y = 0; y < width; y++) {
			if (player == 1) out << displayCopy[x][y];
			else out << p1Display[x][y];
		}
		out << spaceBetweenBoards;
                for (size_t y = 0; y < width; y++) {
			if (player == 2) out << displayCopy[x][y];
			else out << p2Display[x][y];
		}
                out << endl;
	}
}
				
//notify the TextDisplay if a nextBlock has been set
void TextDisplay::notify(Board &whoNotified) {
	if (whoNotified.getNotifType().nextBlockSet) {
		size_t player = whoNotified.getPlayer();
		changePreviews(whoNotified.getNextBlock(), player);
	}
}

//takes in two block pointers and prints them in the preview section
void TextDisplay::changePreviews(Block* nextBlock, size_t player) {
	//if the block is a * block, ignore it
	if (nextBlock->getType() == '*') return;
	//clear the preview before we do anything
	for (int i = 0; i < 8; i++) {
		if (player == 1) p1Preview[i] = ' ';
		else p2Preview[i] = ' ';
	}
	for (int i = 0; i < 4; i++) {
		size_t indexToReplace = nextBlock->getPreview()[i];
		if (player == 1) p1Preview[indexToReplace] = nextBlock->getType();
		else p2Preview[indexToReplace] = nextBlock->getType();
	}
}

//prints the two previews for the nextblock
void TextDisplay::printPreviews(ostream &out) const {
	size_t spacebetween = 8;
        size_t previewSpace = width - 4 + spacebetween;
        size_t nextSpace = width - 5 + spacebetween;
	string spaceAfterPrev, spaceAfterNext;
	for (size_t i = 0; i < previewSpace; i++) spaceAfterPrev += " ";
        for (size_t i = 0; i < nextSpace; i++) spaceAfterNext += " ";
	out << "Next:" << spaceAfterNext << "Next:" << endl;
        for (int i = 0; i < 4; i++) { out << p1Preview[i]; }
        out << spaceAfterPrev;
        for (int i = 0; i < 4; i++) { out << p2Preview[i]; }
        out << endl;
        for (int i = 4; i < 8; i++) { out << p1Preview[i]; }
        out << spaceAfterPrev;
        for (int i = 4; i < 8; i++) { out << p2Preview[i]; }
	out << endl;
}

//overloaded ostream operator for TextDisplay
ostream &operator<<(ostream &out, const TextDisplay &td) {
	size_t spacebetween = 8;
	size_t displayWidth = (td.width * 2) + spacebetween;
	size_t spaceForHigh = (displayWidth - (spacebetween * 2)) / 2;
	string divider = "";
	string spaceBetweenBoards = ""; 
	string hiscorespace = "";
	//initialization of the divider and the space between the two boards
	for (size_t i = 0; i < td.width; i++) divider += "-";
	for (size_t i = 0; i < spacebetween; i++) spaceBetweenBoards.append(" ");
	for (size_t i = 0; i < spaceForHigh; i++) hiscorespace.append(" ");
	//Print out the High Score at the top
	out << endl;
	out << hiscorespace << "High Score:" << setw(5) << td.b1->getHiScore() << hiscorespace << endl;
	//Printing the header information
	out << "Level:" << setw(5) << td.b1->getLevel() << spaceBetweenBoards;
        out << "Level:" << setw(5) << td.b2->getLevel() << endl;
	out << "Score:" << setw(5) << td.b1->getScore() << spaceBetweenBoards;
	out << "Score:" << setw(5) << td.b2->getScore() << endl;
	out << divider << spaceBetweenBoards << divider << endl;
	//Printing the two boards and their contents
	if (td.b1->isBlind()) td.blind(1, out);
	else if (td.b2->isBlind()) td.blind(2, out);
	else {
		for (size_t x = 0; x < td.height; x++) {
			for (size_t y = 0; y < td.width; y++) out << td.p1Display[x][y];
			out << spaceBetweenBoards;
			for (size_t y = 0; y < td.width; y++) out << td.p2Display[x][y];
			out << endl;
		}
	}
	out << divider << spaceBetweenBoards << divider << endl;
	//Printing the preview section
	td.printPreviews(out);
	out << endl;
	return out;
}

TextDisplay::~TextDisplay() {}
