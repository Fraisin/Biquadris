#include <iostream>
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include "window.h"
#include "graphics.h"
#include "board.h"
#include <string>
#include <map>

using namespace std;

//constant map from a type of block to its corresponding index in xwindow's colour vector
map<char, int> m = {{'I', 0}, {'J', 1}, {'L', 2}, {'O', 3}, {'S', 4},
                {'Z', 5}, {'T', 6}, {'*', 7}};
//string and space initialization
string highscore, p1level, p2level, p1score, p2score;
string highscorespace(16, ' '), levelspace(33, ' ');

//GraphicsDisplay constructor
GraphicsDisplay::GraphicsDisplay(size_t tw, size_t dw, size_t dh, size_t bw, size_t bh, Board* b1, Board* b2) : 
	tw{tw}, dw{tw * dw}, dh{tw * dh}, bw{tw * bw}, bh{tw * bh},
       	xw{static_cast<int>(tw * dw), static_cast<int>(tw * dh)}, b1{b1}, b2{b2} {
		init();	
	}

//initializes the background of the board
void GraphicsDisplay::init() {
	p1borderL = tw * 5; //left border for P1
	borderT = tw * 7; //top border
	space = tw * 8; //space between the two boards
	p2borderL = p1borderL + bw + space; //left border for P2
	//print the high score, level and score of each player
	highscore = "High Score:" + highscorespace + to_string(b1->getHiScore());
	p1level = "Level:" + levelspace + to_string(b1->getLevel());
	p2level = "Level:" + levelspace + to_string(b2->getLevel());
	xw.drawString((dw - space) / 2, borderT - 80, highscore);
	xw.drawString(p1borderL, borderT - 40, p1level);
	xw.drawString(p1borderL, borderT - 20, "Score:" + levelspace + "0");
	xw.drawString(p2borderL, borderT - 40, p2level);
        xw.drawString(p2borderL, borderT - 20, "Score:" + levelspace + "0");
	//draw the background for Player One's board
	int black = 9;
	xw.fillRectangle(p1borderL, borderT, bw - 0.01, bh - 0.01, black);
	//draw the background for Player Two's board
	xw.fillRectangle(p2borderL, borderT, bw - 0.01, bh - 0.01, black);
	//draw the Next Block label for both players
	xw.drawString(p1borderL, dh - borderT + 10, "Next Block:");
	xw.drawString(p2borderL, dh - borderT + 10, "Next Block:");
}

//Notify method that will colour in the appropriate square 
void GraphicsDisplay::notify(Tile &whoNotified) {
	//get the information of the tile that notified the display
	bool tileOccupied = whoNotified.getInfo().occupied;
	size_t x = whoNotified.getInfo().x;
	size_t y = whoNotified.getInfo().y;
	char piece = whoNotified.getInfo().myPiece;
	size_t player = whoNotified.getInfo().myBoard->getPlayer();
	int colour = m[piece], black = 9;
	size_t blockSize = tw - 0.01;
	//if occupied, draw in the square at its location with the appropriate colour
	if (tileOccupied) {
		if (player == 1) xw.fillRectangle((y * tw) + p1borderL, 
				(x * tw) + borderT, blockSize, blockSize, colour);
		else xw.fillRectangle((y * tw) + p2borderL, 
				(x * tw) + borderT, blockSize, blockSize, colour);
	} else {
		if (player == 1) xw.fillRectangle((y * tw) + p1borderL, 
				(x * tw) + borderT, blockSize, blockSize, black);
                else xw.fillRectangle((y * tw) + p2borderL, 
				(x * tw) + borderT, blockSize, blockSize, black);
	}
	//if this tile's board is blind, redraw the blind rectangle
	if (whoNotified.getInfo().myBoard->isBlind()) applyBlind(player);
}

//Notifies the graphic display to change the preview, score, level, hiscore
void GraphicsDisplay::notify(Board &whoNotified) {
	//pb represents the preview's distance from the bottom
	size_t pb = dh - borderT + 30; 
	size_t player = whoNotified.getPlayer();
	//get the block's indices to help draw in the preview
	vector<size_t> preview = whoNotified.getNextBlock()->getPreview();
	int white = 8, black = 9;
	char piece = whoNotified.getNextBlock()->getType();
	int colour = m[piece];
	//these are used to give our blocks black lines
	size_t blockSize = tw - 0.01;
	size_t offset = 0.005;
	if (whoNotified.getNotifType().nextBlockSet) {
		//clear the correct player's preview first
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				if (player == 1) {
					xw.fillRectangle((i * tw) + p1borderL,
					(j * tw) + pb, tw + 1, tw + 1, white);
				} else {
					xw.fillRectangle((i * tw) + p2borderL,
					(j * tw) + pb, tw + 1, tw + 1, white);
				}
			}
		}
		//draw the preview depending on which block is next
		for (size_t i = 0; i < preview.size(); i++) {
			size_t cur = preview[i];
			if (cur > 3) {
				if (player == 1) {
					//draw the bigger black square first
					xw.fillRectangle((cur % 4) * tw + p1borderL,
                                	(1 * tw) + pb, tw + 1, tw + 1, black);
					//then draw the coloured square slightly smaller
					xw.fillRectangle((cur % 4) * tw + p1borderL + offset, 
					(1 * tw) + pb + offset, blockSize, blockSize, colour);
				} else {
					xw.fillRectangle((cur % 4) * tw + p2borderL,
                               	 	(1 * tw) + pb, tw + 1, tw + 1, black);
					xw.fillRectangle((cur % 4) * tw + p2borderL + offset,
                                	(1 * tw) + pb + offset, blockSize, blockSize, colour);
				}
			} else {
		       		if (player == 1) {
			       		xw.fillRectangle((cur * tw) + p1borderL,
                                	(0 * tw) + pb, tw + 1, tw + 1, black);
		       			xw.fillRectangle((cur * tw) + p1borderL + offset,
                               	 	(0 * tw) + pb + offset, blockSize, blockSize, colour);
		       		} else {
			        	xw.fillRectangle((cur * tw) + p2borderL,
                                	(0 * tw) + pb, tw + 1, tw + 1, black);
					xw.fillRectangle((cur * tw) + p2borderL + offset,
                                	(0 * tw) + pb + offset, blockSize, blockSize, colour);
		       		}
			}
		}
	}
	//if the high score has been changed, update it on the display
	if (whoNotified.getNotifType().hiScoreChanged) {
		string highscorespace, highscore;
		for (int i = 0; i < 16; i++) highscorespace += " ";
		highscore = "High Score:" + highscorespace + to_string(b1->getHiScore());
		//clear the current high score, then redraw the string
		xw.fillRectangle(p1borderL * 4.3, borderT - 90, 80, 15, white);
		xw.drawString((dw - space) / 2, borderT - 80, highscore);
	}
	//if the level has been changed, update it on the correct player's board
	if (whoNotified.getNotifType().levelChanged) {
		p1level = "Level:" + levelspace + to_string(b1->getLevel());
        	p2level = "Level:" + levelspace + to_string(b2->getLevel());
		if (player == 1) {
			//remove the old level and draw the new one
			xw.fillRectangle(p1borderL * 3, borderT - 50, 30, 15, white);
			xw.drawString(p1borderL, borderT - 40, p1level);
		}
		else { 
			//remove the old level and draw the new one
			xw.fillRectangle(p1borderL * 6.8, borderT - 50, 30, 15, white);
			xw.drawString(p2borderL, borderT - 40, p2level);
		}
	}
	//if the score has been changed, update it on the correct player's display
	if (whoNotified.getNotifType().scoreChanged) {
		p1score = "Score:" + levelspace + to_string(b1->getScore());
		p2score = "Score:" + levelspace + to_string(b2->getScore());
		if (player == 1) {
			//remove the old score and draw the new one
			xw.fillRectangle(p1borderL * 2.6, borderT - 30, 80, 15, white);
			xw.drawString(p1borderL, borderT - 20, p1score);
		}
		else {
			//remove the old score and draw the new one
			xw.fillRectangle(p1borderL * 6.4, borderT - 30, 80, 15, white);
			xw.drawString(p2borderL, borderT - 20, p2score);
		}
	}
	//if the board has been set to blind, then apply the blindness effect
	if (whoNotified.getNotifType().blindOn) applyBlind(player);
	//if the board wants its blindness to be removed, do so
	if (whoNotified.getNotifType().blindOff) {
		if (player == 1) removeBlind(b1);
		else removeBlind(b2);
	}
	//clear all notifications in preparation of next block
	whoNotified.clearNotifs();
}	

//this method will draw the rectangle that applies blindness to the graphics
void GraphicsDisplay::applyBlind(size_t player) {
	int fog = 8;
	if (player == 1) {
		xw.fillRectangle((2 * tw) + p1borderL,
		(5 * tw) + borderT, 7 * tw, 10 * tw, fog);
	}
        else {
		xw.fillRectangle((2 * tw) + p2borderL,
		(5 * tw) + borderT, 7 * tw, 10 * tw, fog);
	}
}

//this method will remove the blindness and redraw the necessary blocks
void GraphicsDisplay::removeBlind(Board* b) {
	size_t blockSize = tw - 0.01;
	int black = 9;
	const vector<vector<Tile>> &tiles = b->getTheBoard();
	//first, redraw black background
	if (b->getPlayer() == 1) {
                xw.fillRectangle((2 * tw) + p1borderL,
                (5 * tw) + borderT, 7 * tw, 10 * tw, black);
        }
        else {
                xw.fillRectangle((2 * tw) + p2borderL,
                (5 * tw) + borderT, 7 * tw, 10 * tw, black);
	}
	//then draw the tiles on top
	for (int x = 5; x < 15; x++) {
		for (int y = 2; y < 9; y++) {
			if (tiles[x][y].getInfo().occupied) {
				char piece = tiles[x][y].getInfo().myPiece;
                                int colour = m[piece];
				if (b->getPlayer() == 1) {
					xw.fillRectangle((y * tw) + p1borderL,
                                	(x * tw) + borderT, blockSize, blockSize, colour);
				} else {
					xw.fillRectangle((y * tw) + p2borderL,
                                	(x * tw) + borderT, blockSize, blockSize, colour);
				}
			}
		}
	}
}


//Clear method that will clear the GraphicsDisplay and also print the winner
void GraphicsDisplay::displayWinner(size_t player) {
	if (player == 1) {
		xw.drawString((dw / 2) - 45, (dh / 2), "Player One won!");
	} else {
		xw.drawString((dw / 2) - 45, (dh / 2), "Player Two won!");
	}
	xw.drawString((dw / 2) - 65, (dh / 2) + 30, "Enter any key to exit.");
}

GraphicsDisplay::~GraphicsDisplay() {}
