#pragma once

#include "Sudoku.h"

class SudokuSolver
{
public:
    static int solve(Sudoku&, int limit = 300);
private:
    static bool checkPosition(Sudoku&, int, int);
};
