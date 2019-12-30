#ifndef OBLOCK_H
#define OBLOCK_H
#include <vector>
#include <string>
#include "block.h"


class Oblock : public Block {
	static const std::vector<std::vector<std::string>> Oblockvector; //vector of block orientations
	static const std::vector<size_t> Opreview; //preview vector

	public:
		Oblock(bool heavy); //Sets the (x, y) coordinates for the top left of the 4x4 block
		virtual std::vector<std::vector<std::string>> getBlock() override; //Returns the block vector
		virtual std::vector<size_t> getPreview() override; //returns the preview vector
		virtual char getType() override; //returns the char corresponding to the block
		virtual ~Oblock() override;
};

#endif
