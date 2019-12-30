#include <vector>
#include <string>
#include "block.h"
#include "lblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Lrotation0 {"....", "....", "..L.", "LLL."}; //Default rotation
std::vector<std::string> Lrotation1 {"....", "L...", "L...", "LL.."}; //90 Degrees Clockwise rotation
std::vector<std::string> Lrotation2 {"....", "....", "LLL.", "L..."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Lrotation3 {"....", "LL..", ".L..", ".L.."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Lblock::Lblockvector = {Lrotation0, Lrotation1, Lrotation2, Lrotation3};

//Defining preview matrix
const std::vector<size_t> Lblock::Lpreview {2, 4, 5, 6};

//Creates a block with the top left of the 4x4 grid at (x, y)
Lblock::Lblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Lblock::getType() { return 'L'; }

//Returns the preview vector
std::vector<size_t> Lblock::getPreview() { return Lpreview; }

//returns the block vector
std::vector<std::vector<std::string>> Lblock::getBlock() {return Lblockvector;}

Lblock::~Lblock() {}
