#ifndef ZBLOCK_H
#define ZBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Zblock : public Block {
	static const std::vector<std::vector<std::string>> Zblockvector; //vector of block orientations
	static const std::vector<size_t> Zpreview; //preview vector

	public:
		Zblock(bool heavy); //Sets the (x, y) coordinates for the top left of the 4x4 block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector
		virtual std::vector<size_t> getPreview() override; //returns preview vector
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Zblock() override;
};

#endif
