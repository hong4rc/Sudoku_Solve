#pragma once

#include "Sudoku.h"

class SudokuSolver
{
public:
    static void solve(Sudoku&);
private:
    static bool checkPosition(Sudoku&, int, int);
};
