#include <iostream>
#include <list>
#include "Sudoku.h"
#include "SudokuSolver.h"

Sudoku::Sudoku(ifstream* inputFile)
{
    results = new list<int*>();
    this->data = new int[SQUARE_LENGTH * SQUARE_LENGTH];
    if (inputFile->is_open())
    {
        char c;
        for (auto i = 0; i < SQUARE_LENGTH * SQUARE_LENGTH; ++i)
        {
            *inputFile >> c;
            if (c == '.' || c == '_' || c == '0')
            {
                this->data[i] = 0;
                continue;
            }
            if (c > '0' && c <= '9')
            {
                this->data[i] = c - '0';
            }
            else
            {
                throw std::range_error("Invalid input");
            }

        }
        inputFile->close();
    }
}

Sudoku::~Sudoku()
{
    delete[] this->data;
    for (auto result : *results)
    {
        delete[] result;
    }
    delete results;
}

int& Sudoku::at(int row, int col) const
{
    return this->data[row * SQUARE_LENGTH + col];
}

bool Sudoku::isValid()
{
    for (auto row = 0; row < SQUARE_LENGTH; ++row)
    {
        if (!isValidRow(row))
        {
            return false;
        }
    }

    for (auto col = 0; col < SQUARE_LENGTH; ++col)
    {
        if (!isValidCol(col))
        {
            return false;
        }
    }

    for (auto row = 0; row < MINI_SQUARE_LENGTH; ++row)
    {
        for (auto col = 0; col < MINI_SQUARE_LENGTH; ++col)
        {
            if (!isValidMiniSquare(row * MINI_SQUARE_LENGTH, col * MINI_SQUARE_LENGTH))
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isValid(void(*next)(int&, int&), int row, int col)
{
    this->resetCheck();
    for (auto i = 0; i < SQUARE_LENGTH; next(row, col), ++i)
    {
        const auto index = this->at(row, col) - 1;
        if (index < 0)
        {
            continue;
        }
        if (check1to9[index] <= 0)
        {
            ++check1to9[index];
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValidRow(const int row)
{
    return isValid(nextCol, row, 0);
}

bool Sudoku::isValidCol(const int col)
{
    return isValid(nextRow, 0, col);
}

bool Sudoku::isValidMiniSquare(const int row, const int col)
{
    return isValid(nextSquare, row, col);
}

void Sudoku::capture()
{
    if (!isValid())
    {
        throw std::exception("Can't capture with invalid board");
    }
    int* tmp = new int[SQUARE_LENGTH * SQUARE_LENGTH];
    for (auto i = 0; i < SQUARE_LENGTH * SQUARE_LENGTH; ++i)
    {
        tmp[i] = data[i];
    }
    results->push_back(tmp);
}

void Sudoku::resetCheck()
{
    memset(check1to9, 0, sizeof(check1to9));
}

void Sudoku::nextRow(int& row, int& col)
{
    ++row;
}

void Sudoku::nextCol(int& row, int& col)
{
    ++col;
}

void Sudoku::nextSquare(int& row, int& col)
{
    ++col;
    if (col % Sudoku::MINI_SQUARE_LENGTH == 0)
    {
        col -= Sudoku::MINI_SQUARE_LENGTH;
        ++row;
    }
}

ostream& operator<<(ostream& out, const Sudoku& board)
{
    out << "Found " << board.results->size() << " result" << endl;
    int i = 0;
    for (auto result : *board.results)
    {
        out << "result " << ++i << endl;
        for (auto row = 0; row < Sudoku::SQUARE_LENGTH; ++row)
        {
            out << " | ";
            for (auto col = 0; col < Sudoku::SQUARE_LENGTH; ++col)
            {
                out << result[row * Sudoku::SQUARE_LENGTH + col];
                if (col % 3 == 2)
                {
                    out << " | ";
                }
                else
                {
                    out << "|";
                }
            }
            if (row % 3 == 2)
            {
                out << "\n  -----------------------";
            }
            out << "\n";
        }
    }
    return out;
}
