#include <vector>
#include <string>
#include "block.h"
#include "cblock.h"

// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Crotation0 {"....", "....", "....", "*..."}; //Default rotation
std::vector<std::string> Crotation1 {"....", "....", "....", "*..."}; //90 Degrees Clockwise rotation
std::vector<std::string> Crotation2 {"....", "....", "....", "*..."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Crotation3 {"....", "....", "....", "*..."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Cblock::Cblockvector = {Crotation0, Crotation1, Crotation2, Crotation3};

//Defining preview matrix
const std::vector<size_t> Cblock::Cpreview {0, 0, 0, 0};

//Creates a block with the top left of the 4x4 grid at (x, y)
Cblock::Cblock() : Block(5, 0, 0, false, false) {}

//Returns the char pertaining to the block
char Cblock::getType() { return '*'; }

//Returns the preview vector
std::vector<size_t> Cblock::getPreview() { return Cpreview; }

//Returns the block vector
std::vector<std::vector<std::string>> Cblock::getBlock() {
        return Cblockvector;
}

Cblock::~Cblock() {}
