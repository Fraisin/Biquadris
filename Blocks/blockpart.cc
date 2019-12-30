#include "blockpart.h"

using namespace std;

Blockpart::Blockpart(int y, int levelGenerated) : y{y}, levelGenerated{levelGenerated}, cleared{false} {}

Blockpart::~Blockpart() {}

int Blockpart::getY() {return y;}

int Blockpart::getLevelGenerated() {return levelGenerated;}

bool Blockpart::getCleared() {return cleared;}

void Blockpart::setY(int y) {this->y = y;}

void Blockpart::setCleared(bool cleared) {this->cleared = cleared;}
