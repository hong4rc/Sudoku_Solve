#pragma once
#include <string>
#include <fstream>
//#define __DEBUG

using namespace std;
const int MINI_SQUARE_LENGTH = 3;
const int SQUARE_LENGTH = MINI_SQUARE_LENGTH * MINI_SQUARE_LENGTH;

class SudokuSolver
{
public:
	SudokuSolver(string inputPath, string outputPath);
	~SudokuSolver();
	void SetPathFile(string inputPath, string outputPath);
	void LoadFile() const;
	void SaveFile() const;
	void Solve();
	bool IsValid() const;
	bool IsValidRow(int) const;
	bool IsValidCol(int) const;
	bool IsValidMiniSquare(int, int) const;
	void ResetCheckArray() const;
	bool CheckWithOffset(int, int);
private:
	string inputPath;
	string outputPath;
	int* checkArray = new int[SQUARE_LENGTH + 1];
	int** data;
	void LogError(int, int) const;
	void LogData() const;
};
