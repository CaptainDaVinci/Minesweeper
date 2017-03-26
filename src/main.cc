#include <iostream>
#include <sstream>
#include "Minesweeper.h"

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