#include "SudokuSolver.h"

int main()
{
	auto solver = new SudokuSolver("input.txt", "output.txt");
	solver->Solve();
	delete solver;
}