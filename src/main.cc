#include <iostream>
#include <iomanip>
#include <array>
#include <random>
#include <sstream>
#include "Minesweeper.h"

// auto constexpr RED = "\x1b[31;1m";
// auto constexpr GREEN = "\x1b[32;1m";
// auto constexpr BLUE = "\x1b[34;1m";
// auto constexpr TILE = "\x1b[30;47m";
// auto constexpr RESET = "\x1b[0m";
// auto constexpr CLEAR = "\x1b[2J";

// enum State
// {
//     flag = '*',
//     seen = ' ',
//     mine = '#',
//     unseen = '+'
// };

// class Cell
// {
//   private:
//     State state;
//     int value;
//     bool containsMine;

//   public:
//     Cell() : state{unseen}, value(0), containsMine(false) {}
//     char getState(void) const
//     {
//         return state;
//     }

//     bool isMine(void) const
//     {
//         return containsMine;
//     }

//     int getValue(void) const
//     {
//         return value;
//     }

//     void setValue(int val)
//     {
//         value = val;
//     }

//     void setState(State c)
//     {
//         if(c == mine)
//             containsMine = true;

//         state = c;
//     }
// };

// class Minesweeper
// {
//   private:
//     const static int GRIDSIZE = 8;
//     std::array<std::array<Cell, GRIDSIZE>, GRIDSIZE> board;
//     const int totalMines = 10;

//   public:
//     Minesweeper() { generateMines(); }

//     void display(bool revealMines = false) const
//     {   
//         std::cout << CLEAR;
//         std::cout << "   ";
//         for (size_t i = 0; i < GRIDSIZE; ++i)
//             std::cout << std::setw(3)
//                       << i << " ";
//         drawLine();

//         int j = 0;
//         for (auto const &row : board)
//         {
//             std::cout << std::setw(2)
//                       << j++ << " |";
//             for (auto const &col : row)
//             {
//                 if (col.getState() == seen && col.getValue() == 0)
//                     std::cout << ' ' << static_cast<char> (seen) << ' ';

//                 else if (revealMines && col.isMine() && col.getState() == flag)
//                     std::cout << RED << ' ' << static_cast<char>(flag) << ' ';

//                 else if (col.getState() == flag)
//                     std::cout <<  BLUE << ' ' << static_cast<char> (flag) << ' ';

//                 else if (revealMines && col.isMine())
//                     std::cout << RED << ' ' << static_cast<char>(mine) << ' ';

//                 else if (col.getState() == seen && col.getValue() != 0)
//                     std::cout << GREEN << ' ' << col.getValue() << ' ';
//                 else
//                     std::cout << TILE << ' ' << static_cast<char>(unseen) << ' ';
//                 std::cout << RESET << '|';
//             }
//             drawLine();
//         }
//     }

//     void drawLine(void) const
//     {
//         std::cout << "\n   ";

//         for (size_t i = 0; i < board.size(); ++i)
//             std::cout << "----";

//         std::cout << '\n';
//     }

//     void generateMines(void)
//     {
//         std::random_device rd;
//         std::mt19937 mt(rd());
//         std::uniform_int_distribution<int> dt(0, GRIDSIZE - 1);

//         for (int i = 0; i < totalMines; ++i)
//         {
//             int row, col;

//             do
//             {
//                 row = dt(mt);
//                 col = dt(mt);

//             } while (isMine(row, col));

//             std::cout << row << ' ' << col << '\n';
//             board[row][col].setState(mine);
//         }
//     }

//     int getBoardSize(void) const
//     {
//         return GRIDSIZE;
//     }

//     bool isMine(int row, int col) const
//     {
//         return board[row][col].isMine();
//     }

//     void reveal(int row, int col)
//     {
//         if (board[row][col].getState() == seen)
//             return ;

//         board[row][col].setValue(mineNear(row, col));

//         if (board[row][col].getValue() != 0)
//         {
//             board[row][col].setState(seen);
//             return;
//         }

//         board[row][col].setState(seen);

//         if (col != 0)
//             reveal(row, col - 1);

//         if (col < GRIDSIZE - 1)
//             reveal(row, col + 1);

//         if (row != 0)
//             reveal(row - 1, col);

//         if (row < GRIDSIZE - 1)
//             reveal(row + 1, col);
//     }

//     int mineNear(const int row, const int col) const
//     {
//         int mines = 0;

//         for (int rcount = 0, i = row - 1; rcount < 3; ++rcount, ++i)
//             for (int ccount = 0, j = col - 1; ccount < 3; ++ccount, ++j)
//                 mines += mineAt(i, j);

//         return mines;
//     }

//     bool mineAt(int row, int col) const
//     {
//         return (row >= 0 && col >= 0 && row < GRIDSIZE && col < GRIDSIZE && board[row][col].isMine());
//     }

//     void placeFlag(int row, int col)
//     {
//         board[row][col].setState(flag);
//     }

//     bool isWon(void)
//     {
//         int count = 0;

//         for(auto const &row : board)
//         {
//             for(auto const &col : row)
//             {
//                 if(col.getState() == seen || col.getState() == flag)
//                     count++;
//             }
//         }

//         if(GRIDSIZE * GRIDSIZE - count == 0)
//             return true;
        
//         return false;
//     }
// };

bool getCoordinate(int &row, int &col, const int GRIDSIZE);

int main()
{
    Minesweeper minesweeper;

    while (true)
    {
        minesweeper.display();
        std::cout << "Enter the Row and coloumn: ";
        int row, col;

        if (getCoordinate(row, col, minesweeper.getBoardSize()))
        {
            minesweeper.placeFlag(row, col);
            if(minesweeper.isWon())
            {
                std::cout << "You Won the Game!\n";
                break;
            }
            continue;
        }

        if (minesweeper.isMine(row, col))
        {
            minesweeper.display(true);
            std::cout << "Oops! You stepped on a mine\n";
            break;
        }

        minesweeper.reveal(row, col);

        if(minesweeper.isWon())
        {
            minesweeper.display(true);
            std::cout << "You Won the game!\n";
            break;
        }
    }
}

bool getCoordinate(int &row, int &col, const int GRIDSIZE)
{
    while (true)
    {
        std::string input;
        getline(std::cin, input);
        std::istringstream ss(input);
        char ch;

        ss >> row >> col >> ch;

        if (row >= GRIDSIZE || row < 0)
        {
            std::cout << "Illegal Input!\n"
                         "Try again\n";
            continue;
        }

        if (col >= GRIDSIZE || col < 0)
        {
            std::cout << "Illegal Input!\n"
                         "Try again\n";
            continue;
        }

        if (ch == 'f' || ch == 'F')
            return true;

        return false;
    }
}