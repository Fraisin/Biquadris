#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <string>

//Block is an abstract class that the 8 basic blocks are built off of
class Block {
	
	//x and y are the coords of the top left piece of the block.
	// rotation is the current rotation index where 0 is default, 1 is rotated 90 degrees, etc.
	protected:
		size_t x, y, rotation; //variables pertaining to x, y, and rotation
		bool levelHeavy, effectHeavy; //whether the block is heavy
	
	public:
		virtual std::vector<std::vector<std::string>> getBlock() = 0; //returns the Block vector
		virtual std::vector<size_t> getPreview() = 0;   //returns the vector of indices for the preview display
		virtual char getType() = 0; //Returns the char of the block
		size_t getX(); //returns X coordinate
		size_t getY(); //returns Y coordinate
	       	size_t getRotation(); //returns rotation index
		void setX(size_t x); //sets X coordinate
		void setY(size_t y); //sets Y coordinate
		void setRotation(size_t rotation); //sets rotation index
		bool isLevelHeavy(); //returns whether a block is level heavy
		bool isEffectHeavy(); //returns whether a block if effect heavy
		void setEffectHeavy(bool effectHeavy); //sets whether a block is effect heavy
		Block(size_t x, size_t y, size_t rotation, bool levelHeavy, bool effectHeavy);
		virtual ~Block();
};

#endif
