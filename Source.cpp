#include <iostream>
#include "Sudoku.h"
#include "SudokuSolver.h"

int main()
{
    ifstream inputFile("input.txt", fstream::in);
    ofstream outputFile("output.txt", fstream::out);
    Sudoku sudoku(&inputFile);
    SudokuSolver::solve(sudoku, 2000);
    cout.rdbuf(outputFile.rdbuf());
    cout << sudoku;
    system("pause");
    return 0;
}
