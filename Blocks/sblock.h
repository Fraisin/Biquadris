#ifndef SBLOCK_H
#define SBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Sblock : public Block {
	static const std::vector<std::vector<std::string>> Sblockvector; //vector of block orientations
	static const std::vector<size_t> Spreview; //preview vector

	public:
		Sblock(bool heavy); //Sets the (x, y) coordinates for the top left of the 4x4 block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector
		virtual std::vector<size_t> getPreview() override; //returns preview vector 
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Sblock() override;
};

#endif
