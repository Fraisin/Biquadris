#ifndef TBLOCK_H
#define TBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Tblock : public Block {
	static const std::vector<std::vector<std::string>> Tblockvector; //vector of block orientations
	static const std::vector<size_t> Tpreview; //preview vector

	public:
		Tblock(bool heavy); //Sets the (x, y) coordinates for the top left of the 4x4 block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector
		virtual std::vector<size_t> getPreview() override; //returns preview vector
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Tblock() override;
};

#endif
