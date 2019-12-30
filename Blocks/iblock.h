#ifndef IBLOCK_H
#define IBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Iblock : public Block {
	static const std::vector<std::vector<std::string>> Iblockvector; //vector of block orientations
	static const std::vector<size_t> Ipreview; //preview vector

	public:	                        
		Iblock(bool levelHeavy); //Sets the (x, y) coordinates for the the block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector	
		virtual std::vector<size_t> getPreview() override; //returns preview vector
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Iblock() override;
};

#endif
