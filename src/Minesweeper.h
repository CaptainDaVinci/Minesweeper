#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include "Cell.h"

auto constexpr RED = "\x1b[31;1m";
auto constexpr GREEN = "\x1b[32;1m";
auto constexpr BLUE = "\x1b[34;1m";
auto constexpr TILE = "\x1b[30;47m";
auto constexpr RESET = "\x1b[0m";
auto constexpr CLEAR = "\x1b[2J";

class Minesweeper
{
  private:
    const static int GRIDSIZE = 20;
    std::array<std::array<Cell, GRIDSIZE>, GRIDSIZE> board;
    const int totalMines = 40;

  public:
    Minesweeper() { generateMines(); }

    void display(bool revealMines = false) const;
    void drawLine(void) const;
    void generateMines(void);
    int getBoardSize(void) const;
    bool isMine(int row, int col) const;
    void reveal(int row, int col);
    int mineNear(const int row, const int col) const;
    bool mineAt(int row, int col) const;
    void placeFlag(int row, int col);
    bool isWon(void) const;

};

#endif