#include <vector>
#include <string>
#include "block.h"
#include "iblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Irotation0 {"....", "....", "....", "IIII"}; //Default rotation
std::vector<std::string> Irotation1 {"I...", "I...", "I...", "I..."}; //90 Degrees Clockwise rotation
std::vector<std::string> Irotation2 {"....", "....", "....", "IIII"}; //180 Degrees Clockwise Rotation
std::vector<std::string> Irotation3 {"I...", "I...", "I...", "I..."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Iblock::Iblockvector = {Irotation0, Irotation1, Irotation2, Irotation3};

//Defining preview matrix
const std::vector<size_t> Iblock::Ipreview {4, 5, 6, 7};

//Creates a block with the top left of the 4x4 grid at (x, y) with specified heavy effects
Iblock::Iblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Iblock::getType() { return 'I'; }

//Returns the preview vector
std::vector<size_t> Iblock::getPreview() { return Ipreview; }

//Returns the block vector
std::vector<std::vector<std::string>> Iblock::getBlock() {return Iblockvector;}

Iblock::~Iblock() {}

