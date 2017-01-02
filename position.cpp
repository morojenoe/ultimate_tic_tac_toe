#include "position.h"

pos::pos(int r, int c) {
  this->r = r;
  this->c = c;
}

int pos::posInMacroboard() const {
  return (this->r/3)*3 + this->c / 3;
}

int pos::posInBoard() const {
  return this->r*9 + this->c;
}

pos pos::nextSquareToMove() const {
  return pos(this->r % 3, this->c % 3);
}
