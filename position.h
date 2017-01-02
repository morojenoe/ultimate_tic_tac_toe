#ifndef STRATEGY_POSITION_H
#define STRATEGY_POSITION_H


struct pos {
  int r, c;

  pos(int r, int c);

  int posInMacroboard() const;
  int posInBoard() const;
  pos nextSquareToMove() const;
};


#endif //STRATEGY_POSITION_H
