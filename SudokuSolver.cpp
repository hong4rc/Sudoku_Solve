#include <iostream>
#include "SudokuSolver.h"

using namespace std;

void SudokuSolver::solve(Sudoku& board, int limit)
{
    if (!board.isValid())
    {
        cout << "Your input invalid!!!";
        return;
    }
    board.setLimit(limit);
    checkPosition(board, 0, 0);
}

bool SudokuSolver::checkPosition(Sudoku& board, int row, int col)
{
    if (col == Sudoku::SQUARE_LENGTH)
    {
        row += 1;
        col = 0;
    }
    if (row == Sudoku::SQUARE_LENGTH)
    {
        board.capture();
        return true;
    }
    if (board.at(row, col) == 0)
    {
        bool found = false;
        for (auto test = 1; test <= Sudoku::SQUARE_LENGTH; ++test)
        {
            board.at(row, col) = test;
            if (board.isValidCol(col) && board.isValidRow(row)
                && board.isValidMiniSquare(row - row % Sudoku::MINI_SQUARE_LENGTH, col - col % Sudoku::MINI_SQUARE_LENGTH))
            {
                if (checkPosition(board, row, col + 1))
                {
                    found = true;
                    if (board.isFull())
                    {
                        return found;
                    }
                }
            }
        }
        board.at(row, col) = 0;
        return found;
    }
    else
    {
        return checkPosition(board, row, col + 1);
    }
}
