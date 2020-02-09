#include <iostream>
#include "SudokuSolver.h"

using namespace std;

SudokuSolver::SudokuSolver(const string inputPath, const string outputPath)
{
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	data = new int*[SQUARE_LENGTH];
	for (auto i = 0; i < SQUARE_LENGTH; ++i)
	{
		data[i] = new int[SQUARE_LENGTH];
	}
}

SudokuSolver::~SudokuSolver()
{
	delete checkArray;
	for (auto iRow = 0; iRow < SQUARE_LENGTH; ++iRow)
	{
		delete data[iRow];
	}
	delete data;
}

void SudokuSolver::SetPathFile(const string inputPath, const string outputPath)
{
	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

void SudokuSolver::LoadFile() const
{
	auto inputFile = new ifstream(inputPath.c_str(), fstream::in);
	if (inputFile->is_open())
	{
		for (auto iRow = 0; iRow < SQUARE_LENGTH; ++iRow)
		{
			for (auto iCol = 0; iCol < SQUARE_LENGTH; ++iCol)
			{
				*inputFile >> data[iRow][iCol];
			}
		}
		inputFile->close();
	}
	delete inputFile;
	LogData();
}

void SudokuSolver::SaveFile() const
{
	auto outputFile = new ofstream(outputPath.c_str(), fstream::out);
	if (outputFile->is_open())
	{
		for (auto iRow = 0; iRow < SQUARE_LENGTH; ++iRow)
		{
			for (auto iCol = 0; iCol < SQUARE_LENGTH; ++iCol)
			{
				*outputFile << data[iRow][iCol];
				if (iCol != SQUARE_LENGTH - 1)
				{
					*outputFile << " ";
				}
			}
			*outputFile << endl;
		}
		outputFile->close();
	}
	delete outputFile;
}

void SudokuSolver::Solve()
{
	LoadFile();
	if (!IsValid())
	{
		cout << "Your input invalid!!!";
		return;
	}
	if (CheckWithOffset(0, 0))
	{
		SaveFile();
	}
	else
	{
		cout << "Can't solve this board!!!";
	}
}

bool SudokuSolver::IsValid() const
{
	for (auto iRow = 0; iRow < SQUARE_LENGTH; ++iRow)
	{
		if (!IsValidRow(iRow))
		{
			return false;
		}
	}
	for (auto iCol = 0; iCol < SQUARE_LENGTH; ++iCol)
	{
		if (!IsValidCol(iCol))
		{
			return false;
		}
	}
	for (auto iRow = 0; iRow < MINI_SQUARE_LENGTH; ++iRow)
	{
		for (auto iCol = 0; iCol < MINI_SQUARE_LENGTH; ++iCol)
		{
			if (!IsValidMiniSquare(iRow, iCol))
			{
				return false;
			}
		}
	}
	return true;
}

bool SudokuSolver::IsValidRow(const int iRow) const
{
	ResetCheckArray();
	for (auto iCol = 0; iCol < SQUARE_LENGTH; ++iCol)
	{
		const auto index = data[iRow][iCol];
		if (checkArray[index] <= 0)
		{
			if (index != 0)
			{
				checkArray[index]++;
			}
		}
		else
		{
#ifdef __DEBUG
			cout << "Row " << iRow;
			LogError(iRow, iCol);
#endif
			return false;
		}
	}
	return true;
}

bool SudokuSolver::IsValidCol(const int iCol) const
{
	ResetCheckArray();
	for (auto iRow = 0; iRow < SQUARE_LENGTH; ++iRow)
	{
		const auto index = data[iRow][iCol];
		if (checkArray[index] <= 0)
		{
			if (index != 0)
			{
				checkArray[index]++;
			}
		}
		else
		{
#ifdef __DEBUG
			cout << "Col " << iCol;
			LogError(iRow, iCol);
#endif
			return false;
		}
	}
	return true;
}

bool SudokuSolver::IsValidMiniSquare(int sRow, int sCol) const
{
	ResetCheckArray();
	sRow *= MINI_SQUARE_LENGTH;
	sCol *= MINI_SQUARE_LENGTH;
	for (auto i = 0; i < SQUARE_LENGTH; ++i)
	{
		const auto offetRow = i / MINI_SQUARE_LENGTH;
		const auto offetCol = i % MINI_SQUARE_LENGTH;
		const auto index = data[sRow + offetRow][sCol + offetCol];
		if (checkArray[index] <= 0)
		{
			if (index != 0)
			{
				checkArray[index]++;
			}
		}
		else
		{
#ifdef __DEBUG
			cout << "Square {" << sRow << ", " << sCol << "}";
			LogError(sRow + offetRow, sCol + offetCol);
#endif
			return false;
		}
	}
	return true;
}

void SudokuSolver::ResetCheckArray() const
{
	for (auto i = 0; i < SQUARE_LENGTH; ++i)
	{
		checkArray[i + 1] = 0;
	}
}

bool SudokuSolver::CheckWithOffset(int iRow, int iCol)
{
	if (iCol == SQUARE_LENGTH)
	{
		iRow += 1;
		iCol = 0;
	}
	if (iRow == SQUARE_LENGTH)
	{
		cout << "Done!!!" << endl;
		LogData();
		return true;
	}
	if (data[iRow][iCol] == 0)
	{
		for (auto test = 1; test <= SQUARE_LENGTH; ++test)
		{
			data[iRow][iCol] = test;
			if (IsValidCol(iCol) && IsValidRow(iRow) && IsValidMiniSquare(iRow / 3, iCol / 3))
			{
				if (CheckWithOffset(iRow, iCol + 1))
				{
					return true;
				}
			}
		}
		data[iRow][iCol] = 0;
		return false;
	}
	else
	{
		return CheckWithOffset(iRow, iCol + 1);
	}
}

void SudokuSolver::LogError(const int iRow, const int iCol) const
{
	cout << " is invalid in {" << iRow << ", " << iCol << "}  (" << data[iRow][iCol] << ")" << endl;
}

void SudokuSolver::LogData() const
{
	cout << endl;
	for (auto row = 0; row < SQUARE_LENGTH; ++row)
	{
		cout << " | ";
		for (auto col = 0; col < SQUARE_LENGTH; ++col)
		{
			cout << data[row][col];
			if (col % 3 == 2)
			{
				cout << " | ";
			}
			else
			{
				cout << "|";
			}
		}
		if (row % 3 == 2)
		{
			cout << "\n  -----------------------";
		}
		cout << "\n";
	}
}
