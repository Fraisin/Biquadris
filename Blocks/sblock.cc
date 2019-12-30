#include <vector>
#include <string>
#include "block.h"
#include "sblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Srotation0 {"....", "....", ".SS.", "SS.."}; //Default rotation
std::vector<std::string> Srotation1 {"....", "S...", "SS..", ".S.."}; //90 Degrees Clockwise rotation
std::vector<std::string> Srotation2 {"....", "....", ".SS.", "SS.."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Srotation3 {"....", "S...", "SS..", ".S.."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Sblock::Sblockvector = {Srotation0, Srotation1, Srotation2, Srotation3};

//Defining preview matrix
const std::vector<size_t> Sblock::Spreview {1, 2, 4, 5};

//Creates a block with the top left of the 4x4 grid at (x, y)
Sblock::Sblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Return the char pertaining to the block
char Sblock::getType() { return 'S'; }

//Returns the preview vector
std::vector<size_t> Sblock::getPreview() { return Spreview; }

//returns the block vector
std::vector<std::vector<std::string>> Sblock::getBlock() {return Sblockvector;}

Sblock::~Sblock() {}
