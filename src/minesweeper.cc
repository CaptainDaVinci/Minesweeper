#include "Minesweeper.h"

void Minesweeper::display(bool revealMines) const
{
    std::cout << CLEAR;
    std::cout << "   ";
    for (size_t i = 0; i < GRIDSIZE; ++i)
        std::cout << std::setw(3)
                  << i << " ";
    drawLine();

    int j = 0;
    for (auto const &row : board)
    {
        std::cout << std::setw(2)
                  << j++ << " |";
        for (auto const &col : row)
        {
            if (col.getState() == seen && col.getValue() == 0)
                std::cout << ' ' << static_cast<char>(seen) << ' ';

            else if (revealMines && col.isMine() && col.getState() == flag)
                std::cout << RED << ' ' << static_cast<char>(flag) << ' ';

            else if (col.getState() == flag)
                std::cout << BLUE << ' ' << static_cast<char>(flag) << ' ';

            else if (revealMines && col.isMine())
                std::cout << RED << ' ' << static_cast<char>(mine) << ' ';

            else if (col.getState() == seen && col.getValue() != 0)
                std::cout << GREEN << ' ' << col.getValue() << ' ';
            else
                std::cout << TILE << ' ' << static_cast<char>(unseen) << ' ';
            std::cout << RESET << '|';
        }
        drawLine();
    }
}

void Minesweeper::drawLine(void) const
{
    std::cout << "\n   ";

    for (size_t i = 0; i < board.size(); ++i)
        std::cout << "----";

    std::cout << '\n';
}

void Minesweeper::generateMines(void)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dt(0, GRIDSIZE - 1);

    for (int i = 0; i < totalMines; ++i)
    {
        int row, col;

        do
        {
            row = dt(mt);
            col = dt(mt);

        } while (isMine(row, col));

        std::cout << row << ' ' << col << '\n';
        board[row][col].setState(mine);
    }
}

int Minesweeper::getBoardSize(void) const
{
    return GRIDSIZE;
}

bool Minesweeper::isMine(int row, int col) const
{
    return board[row][col].isMine();
}

void Minesweeper::reveal(int row, int col)
{
    if (board[row][col].getState() == seen)
        return;

    board[row][col].setValue(mineNear(row, col));

    if (board[row][col].getValue() != 0)
    {
        board[row][col].setState(seen);
        return;
    }

    board[row][col].setState(seen);

    if (col != 0)
        reveal(row, col - 1);

    if (col < GRIDSIZE - 1)
        reveal(row, col + 1);

    if (row != 0)
        reveal(row - 1, col);

    if (row < GRIDSIZE - 1)
        reveal(row + 1, col);
}

int Minesweeper::mineNear(const int row, const int col) const
{
    int mines = 0;

    for (int rcount = 0, i = row - 1; rcount < 3; ++rcount, ++i)
        for (int ccount = 0, j = col - 1; ccount < 3; ++ccount, ++j)
            mines += mineAt(i, j);

    return mines;
}

bool Minesweeper::mineAt(int row, int col) const
{
    return (row >= 0 && col >= 0 && row < GRIDSIZE && col < GRIDSIZE && board[row][col].isMine());
}

void Minesweeper::placeFlag(int row, int col)
{
    if(board[row][col].getState() != seen)
        board[row][col].setState(flag);
}

bool Minesweeper::isWon(void) const
{
    int count = 0;

    for (auto const &row : board)
    {
        for (auto const &col : row)
        {
            if (col.getState() == seen || col.getState() == flag)
                count++;
        }
    }

    if (GRIDSIZE * GRIDSIZE - count == 0)
        return true;

    return false;
}
