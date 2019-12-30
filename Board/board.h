#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>
#include "textdisplay.h"
#include "tile.h"
#include "tileinfo.h"
#include "block.h"
#include "AbsLevel.h"
#include "blockpart.h"
#include "AbsBoard.h"
#include "notiftype.h"

class TextDisplay;
class Observer;

class Board : public Subject, public AbsBoard {
	size_t width; //width of board
	size_t height; //height of board
	size_t score; //score of board
       	size_t level; //level of board
	size_t player; //corresponding player
	size_t hiscore; // current high score across both boards
	bool blind; //whether blind effect is on
	bool heavy; //whether heavy effect is on
	bool force; //whether force effect is on 
	bool effectNeeded; //whether conditions are met for an effect to be applied
	bool dead; //whether player has lost
	Block* curBlock; //pointer to current block in play
	Block* nextBlock; //pointer to next block to be played
	AbsLevel *curLevel; //pointer to the current level
	NotifInfo notifications; //notification structure for graphics
	vector<vector<Tile>> theBoard; //vector of all the boards tiles
	vector<vector<Blockpart>> restingBlocks; //vector of vector of all the block parts resting
	public:
       		Board(size_t width, size_t height, size_t level, size_t player);
		~Board();
		void create(); //Fills in the board object
		void setPiece(size_t x, size_t y, char piece); //plays piece at (x, y)
		void unsetPiece(size_t x, size_t y); //removes piece at (x, y)
		void setObserver(Observer *ob); //Adds ob to the boards list of observers
		void notifyObservers() override; //calls the observers notify function
		bool validMove(int xShift, int yShift, int rotationShift); //returns whether a transform is valid
		void moveBlock(int xShift, int yShift, int rotationShift); //applies a transform to a block
		void restBlock(int levelGenerated); //adds the block to the restingBlocks vector
		void checkLines(); //Checks whether any lines are cleared and adjusts board as required
		size_t getScore() const; //Gets the current score
		void setCurBlock(Block* curBlock); //Updates the current block
		void setNextBlock(Block* nextBlock); //Updates the next block
		Block* getCurBlock(); //returns the current block
		Block* getNextBlock(); //returns the next block
		AbsLevel* getCurLevel(); //returns the curLevel
		size_t getLevel(); //returns the current level size_t
		void unsetBlock(); //Removes current block from the board tiles
		void setCurLevel(size_t level, bool random, string file = ""); //sets curLevel, optional file param
		size_t getPlayer(); //returns the current player
		void apply(Board &board) override; //Apply method for effects
		bool isBlind() const; //returns whether board is blind
		void setBlind(bool blind); //sets whether board is blind
		bool isHeavy() const; //returns whether board is heavy
                void setHeavy(bool heavy); //sets whether board is heavy
		bool isForce() const; //returns whether board has force active
                void setForce(bool force); //sets whether board has force active
		bool isEffectNeeded() const; //returns whether effect is needed
		void setEffectNeeded(bool effectNeeded); //sets whether effect is needed
		void resetBoard(); //Clears out the board for a restart
		size_t getHiScore(); //returns high score
		void setHiScore(size_t hiscore); //sets high score
		void setDead(bool dead); //sets whether player is dead
		bool getDead(); //returns whether player is dead
		NotifInfo getNotifType(); //Returns a structure to know which notif was sent
                void clearNotifs(); //Clears out notification strucutre
                size_t getWidth(); //Returns width
                size_t getHeight(); //Returns height
                const vector<vector<Tile>>& getTheBoard(); //Returns reference to theBoard
		friend ostream &operator<<(ostream &out, const Board &g); //operator << for printing
};

#endif
