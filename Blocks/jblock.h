#ifndef JBLOCK_H
#define JBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Jblock : public Block {
	static const std::vector<std::vector<std::string>> Jblockvector; //vector of block orientations
	static const std::vector<size_t> Jpreview; //preview vector

	public:
		Jblock(bool heavy); //Sets the (x, y) coordinates for the top left of the 4x4 block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector
		virtual std::vector<size_t> getPreview() override; //returns preview vector
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Jblock() override;
};

#endif
