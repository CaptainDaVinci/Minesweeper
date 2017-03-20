#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>

void getValues(unsigned int &posi, unsigned int &posj);
auto constexpr RED = "\x1b[31;1m";
auto constexpr GREEN = "\x1b[32;1m";
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

        for (size_t i = 0; i < board[0].size(); ++i)
            std::cout << std::setw(3)
                      << i << " ";
        drawLine();

        size_t col = 0;
        for (size_t i = 0; i < board[0].size(); ++i)
        {

            std::cout << std::setw(2)
                      << col++ << " | ";

            for (size_t j = 0; j < board[0].size(); ++j)
            {
                if (reveal && mask[i][j])
                    std::cout << RED << '#';
                else
                {
                    if (board[i][j] != '+')
                        std::cout << GREEN << board[i][j];
                    else
                        std::cout << board[i][j];
                }

                std::cout << RESET << " | ";
            }

            drawLine();
        }
    }

    void drawLine(void)
    {
        std::cout << std::endl
                  << "   ";

        for (size_t i = 0; i < board[0].size(); ++i)
            std::cout << "----";

        std::cout << std::endl;
    }

    void generateMines(void)
    {
        for (size_t k = 0; k < 20; ++k)
        {
            size_t i = rand() / (RAND_MAX / board[0].size() + 1);
            size_t j = rand() / (RAND_MAX / board[0].size() + 1);

            mask[i][j] = true;
            std::cout << std::setw(2) << i << ", " << j << std::endl;
        }
    }

    bool isMine(const unsigned int posi, const unsigned int posj)
    {
        return mask[posi][posj];
    }

    void reveal(const unsigned int posi, const unsigned int posj)
    {
        if(board[posi][posj] == ' ')
            return;

        board[posi][posj] = mineNear(posi, posj);
        if(board[posi][posj] != ' ')
            return;
        
        if(posj != 0)
            reveal(posi, posj - 1);

        if(posj < board[0].size() - 1)
            reveal(posi, posj + 1);

        if(posi != 0)
            reveal(posi - 1, posj);        
        
        if(posi < board[0].size() - 1)
            reveal(posi + 1, posj);

    }

    char mineNear(const size_t i, const size_t j)
    {
        unsigned int mines = 0;

        mines += minesAt(i - 1, j - 1);
        mines += minesAt(i - 1, j);
        mines += minesAt(i - 1, j + 1);
        mines += minesAt(i, j - 1);
        mines += minesAt(i, j + 1);
        mines += minesAt(i + 1, j - 1);
        mines += minesAt(i + 1, j);
        mines += minesAt(i + 1, j + 1);

        if (mines == 0)
            return ' ';
        return mines + 48;
    }

    unsigned int minesAt(const int i, const int j)
    {
        return (i >= 0 && j >= 0 && static_cast<unsigned>(i) < board[0].size() && static_cast<unsigned>(j) < board[0].size() && mask[i][j]);
    }
};

unsigned const gridSize = 16;

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
            std::cout << "Oops! "
                      << "You stepped on a mine!"
                      << std::endl;
            game.display(1);
            break;
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