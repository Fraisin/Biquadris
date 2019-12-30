#include <vector>
#include <string>
#include "block.h"
#include "jblock.h"


// Setting the static const variables

// Defining Block Rotations
std::vector<std::string> Jrotation0 {"....", "....", "J...", "JJJ."}; //Default rotation
std::vector<std::string> Jrotation1 {"....", "JJ..", "J...", "J..."}; //90 Degrees Clockwise rotation
std::vector<std::string> Jrotation2 {"....", "....", "JJJ.", "..J."}; //180 Degrees Clockwise Rotation
std::vector<std::string> Jrotation3 {"....", ".J..", ".J..", "JJ.."}; //270 Degrees Clockwise Rotation
const std::vector<std::vector<std::string>> Jblock::Jblockvector = {Jrotation0, Jrotation1, Jrotation2, Jrotation3};

//Defining preview matrix
const std::vector<size_t> Jblock::Jpreview {0, 4, 5, 6};

//Creates a block with the top left of the 4x4 grid at (x, y)
Jblock::Jblock(bool heavy) : Block(0, 0, 0, heavy, false) {}

//Returns the char pertaining to the block
char Jblock::getType() { return 'J'; }

//Returns the preview vector
std::vector<size_t> Jblock::getPreview() { return Jpreview; }

//returns the block vector
std::vector<std::vector<std::string>> Jblock::getBlock() {return Jblockvector;}

Jblock::~Jblock() {}
