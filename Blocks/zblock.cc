#include <vector>
#include <string>
#include "block.h"
#include "zblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Zrotation0 {"....", "....", "ZZ..", ".ZZ."}; //Default rotation
std::vector<std::string> Zrotation1 {"....", ".Z..", "ZZ..", "Z..."}; //90 Degrees Clockwise rotation
std::vector<std::string> Zrotation2 {"....", "....", "ZZ..", ".ZZ."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Zrotation3 {"....", ".Z..", "ZZ..", "Z..."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Zblock::Zblockvector = {Zrotation0, Zrotation1, Zrotation2, Zrotation3};

//Defining preview matrix
const std::vector<size_t> Zblock::Zpreview {0, 1, 5, 6};

//Creates a block with the top left of the 4x4 grid at (x, y)
Zblock::Zblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Zblock::getType() { return 'Z'; }

//Returns the preview vector
std::vector<size_t> Zblock::getPreview() { return Zpreview; }

//returns the block vector
std::vector<std::vector<std::string>> Zblock::getBlock() {return Zblockvector;}

Zblock::~Zblock() {}
