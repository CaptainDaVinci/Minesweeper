#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>

void getValues(unsigned int &posi, unsigned int &posj);
auto constexpr RED = "\x1b[31;1m";
auto constexpr GREEN = "\x1b[32;1m";
auto constexpr BLUE = "\x1b[34;1m";
auto constexpr TILE = "\x1b[30;47m";
auto constexpr RESET = "\x1b[0m";

class mineSweeper
{
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> mask;

  public:
    mineSweeper(const int size) : board(size, std::vector<char>(size, '+')),
                                  mask(size, std::vector<bool>(size, false)) {}
    void display(bool reveal = false)
    {
        std::cout << "   ";

        for (size_t i = 0; i < board.size(); ++i)
            std::cout << std::setw(3)
                      << i << " ";
        drawLine();

        size_t col = 0;
        for (size_t i = 0; i < board.size(); ++i)
        {

            std::cout << std::setw(2)
                      << col++ << " |";

            for (size_t j = 0; j < board.size(); ++j)
            {
                if (reveal && mask[i][j])
                {
                    std::cout << RED << " # ";
                }
                else
                {
                    if (board[i][j] == '+')
                        std::cout << TILE << ' ' << board[i][j] << ' ';
                    else
                        std::cout << GREEN << ' ' << board[i][j] << ' ';
                }

                std::cout << RESET << "|";
            }

            drawLine();
        }
    }

    void drawLine(void)
    {
        std::cout << std::endl
                  << "   ";

        for (size_t i = 0; i < board.size(); ++i)
            std::cout << "----";

        std::cout << std::endl;
    }

    void generateMines(void)
    {
        unsigned int mines = (board.size() == 16 ? 40 : 10);

        for (size_t k = 0; k < mines; ++k)
        {
            size_t i = rand() / (RAND_MAX / board.size() + 1);
            size_t j = rand() / (RAND_MAX / board.size() + 1);

            mask[i][j] = true;
        }
    }

    bool isMine(const unsigned int posi, const unsigned int posj)
    {
        return mask[posi][posj];
    }

    void reveal(const unsigned int posi, const unsigned int posj)
    {
        if (board[posi][posj] == ' ')
            return;

        board[posi][posj] = mineNear(posi, posj);
        if (board[posi][posj] != ' ')
            return;

        if (posj != 0)
            reveal(posi, posj - 1);

        if (posj < board[0].size() - 1)
            reveal(posi, posj + 1);

        if (posi != 0)
            reveal(posi - 1, posj);

        if (posi < board[0].size() - 1)
            reveal(posi + 1, posj);
    }

    char mineNear(const size_t i, const size_t j)
    {
        unsigned int mines = 0;

        for (size_t rowCount = 0, row = i - 1; rowCount < 3; ++rowCount, ++row)
            for (size_t colCount = 0, col = j - 1; colCount < 3; ++colCount, ++col)
                mines += mineAt(row, col);

        if (mines == 0)
            return ' ';
        return mines + 48;
    }

    unsigned int mineAt(const int i, const int j)
    {
        return (i >= 0 && j >= 0 
        && static_cast<unsigned>(i) < board.size() 
        && static_cast<unsigned>(j) < board.size() 
        && mask[i][j]);
    }
};

unsigned const gridSize = 8;

int main()
{
    mineSweeper game(gridSize);

    srand(static_cast<unsigned>(time(NULL)));
    game.display();
    game.generateMines();

    while (true)
    {
        std::cout << "Enter the Row and Coloumn: ";
        unsigned int posi, posj;
        getValues(posi, posj);

        if (game.isMine(posi, posj))
        {
            system("clear");
            std::cout << "Oops! "
                      << "You stepped on a mine!"
                      << std::endl;
            game.display(1);
            return 0;
        }

        game.reveal(posi, posj);

        system("clear");
        game.display();
    }
}

void getValues(unsigned int &posi, unsigned int &posj)
{
    while (true)
    {
        std::cin >> posi >> posj;

        try
        {
            if (posi >= gridSize || posj >= gridSize)
                throw std::out_of_range("Range Exceeded!");
            break;
        }
        catch (std::out_of_range err)
        {
            std::cout << std::endl
                      << err.what()
                      << std::endl
                      << "Try again: ";
        }
    }
}