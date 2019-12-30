#include <vector>
#include <string>
#include "block.h"
#include "oblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Orotation0 {"....", "....", "OO..", "OO.."}; //Default rotation
std::vector<std::string> Orotation1 {"....", "....", "OO..", "OO.."}; //90 Degrees Clockwise rotation
std::vector<std::string> Orotation2 {"....", "....", "OO..", "OO.."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Orotation3 {"....", "....", "OO..", "OO.."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Oblock::Oblockvector = {Orotation0, Orotation1, Orotation2, Orotation3};

//Defining preview matrix
const std::vector<size_t> Oblock::Opreview {0, 1, 4, 5};

//Creates a block with the top left of the 4x4 grid at (x, y)
Oblock::Oblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Oblock::getType() { return 'O'; }

//Returns the preview vector
std::vector<size_t> Oblock::getPreview() { return Opreview; }

//returns the block vector
std::vector<std::vector<std::string>> Oblock::getBlock() {return Oblockvector;}

Oblock::~Oblock() {}
