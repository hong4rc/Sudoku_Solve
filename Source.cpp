#include <iostream>
#include "Sudoku.h"
#include "SudokuSolver.h"

int main()
{
    ifstream inputFile("input.txt", fstream::in);
    Sudoku sudoku(&inputFile);
    SudokuSolver::solve(sudoku);
    system("pause");
    return 0;
}
