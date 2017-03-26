#ifndef CELL_H
#define CELL_H

enum State
{
    flag = '*',
    seen = ' ',
    mine = '#',
    unseen = '+'
};

class Cell
{
  private:
    State state;
    int value;
    bool containsMine;

  public:
    Cell() : state{unseen}, value(0), containsMine(false) {}

    char getState(void) const;
    bool isMine(void) const;
    int getValue(void) const;
    void setValue(int val);
    void setState(State c);
    
};

#endif