#include <vector>
#include <string>
#include "block.h"
#include "tblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Trotation0 {"....", "....", "TTT.", ".T.."}; //Default rotation
std::vector<std::string> Trotation1 {"....", ".T..", "TT..", ".T.."}; //90 Degrees Clockwise rotation
std::vector<std::string> Trotation2 {"....", "....", ".T..", "TTT."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Trotation3 {"....", "T...", "TT..", "T..."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Tblock::Tblockvector = {Trotation0, Trotation1, Trotation2, Trotation3};


//Defining preview matrix
const std::vector<size_t> Tblock::Tpreview {0, 1, 2, 5};

//Creates a block with the top left of the 4x4 grid at (x, y)
Tblock::Tblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Tblock::getType() { return 'T'; }

//Returns the preview vector
std::vector<size_t> Tblock::getPreview() { return Tpreview; }

//Returns the block vector
std::vector<std::vector<std::string>> Tblock::getBlock() {return Tblockvector;}

Tblock::~Tblock() {}
