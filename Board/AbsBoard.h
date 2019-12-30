#ifndef ABSBOARD_H
#define ABSBOARD_H

class Board;

class AbsBoard {
public:
  virtual void apply(Board &board) = 0; //Apply method that differs for effects
  virtual ~AbsBoard();
};

#endif
