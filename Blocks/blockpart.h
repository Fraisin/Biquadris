#ifndef BLOCKPART_H
#define BLOCKPART_H

//A block is has 4 'parts'. This class is used to track the resting parts
//and is isolated from block to minimize the amount of data stored by the board
//at any given point in time.

class Blockpart {
	int y; //Y coodinate of part
	int levelGenerated; //the level the block was generated
	bool cleared; //Whether the part is cleared;
	public:
		Blockpart(int y, int levelGenerated);
		~Blockpart();
		int getY(); //Returns the y coordinate of the part
		int getLevelGenerated(); //Returns the level it was generated
		bool getCleared(); //Returns whether the part was cleared from the board
		void setY(int y); //Sets the Y coordinate of the part
		void setCleared(bool cleared); //Sets the cleared boolean
};

#endif
