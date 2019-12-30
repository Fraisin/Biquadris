#include <vector>
#include <string>
#include "block.h"

using namespace std;

Block::Block(size_t x, size_t y, size_t rotation, bool levelHeavy, bool effectHeavy) : 
	x{x}, y{y}, rotation{rotation}, levelHeavy{levelHeavy}, effectHeavy{effectHeavy} {}

size_t  Block::getX() {return x;}

size_t  Block::getY() {return y;}

size_t  Block::getRotation() {return rotation;}

void Block::setX(size_t x) {this->x = x;}

void Block::setY(size_t y) {this->y = y;}

void Block::setRotation(size_t rotation) {this->rotation = rotation;}

bool Block::isEffectHeavy() {return effectHeavy;}

void Block::setEffectHeavy(bool effectHeavy) {this->effectHeavy = effectHeavy;}

bool Block::isLevelHeavy() {return levelHeavy;}

Block::~Block() {}
