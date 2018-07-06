#include <iostream>
#include <fstream>

#include "Sudoku.h"

using namespace std;

int main()
{
	ReadFile(myArray, INPUT_NAME_FILE);
	//    cout << "\Sudoku_Solve\n\n";
	cout << "\nInput:\n";
	LogArr(myArray);
	if (CheckValid(myArray))
	{
		//cout << "dau vao ok";
		const auto out = SolveGame(myArray, 0, 0);
		getchar();
		return out;
	}
	else
	{
		cout << "Rat tiec khong the giai dc";
		getchar();
		return 1;
	}
}

int SolveGame(int arr[MAX_SQ][MAX_SQ], const int row, const int col)
{
	auto checkResult = -1;
	auto isFirst = false;
	if (countRun == false)
	{
		countRun = true;
		isFirst = true;
	}
	if (col == MAX_SQ)
	{
		if (row == MAX_SQ - 1)
		{
			cout << "\nOutput:\n";
			LogArr(arr);
			WriteFile(arr, OUTPUT_NAME_FILE);
			//exit(0);
			return 0;
		}
		else
		{
			checkResult = SolveGame(arr, row + 1, 0);
			if (checkResult == 0)
			{
				return checkResult;
			}
		}
	}
	else if (arr[row][col] == 0)
	{
		for (auto k = 1; k <= MAX_SQ; k++)
		{
			if (IsValid(arr, row, col, k))
			{
				arr[row][col] = k;
				checkResult = SolveGame(arr, row, col + 1);
				if (checkResult == 0) return checkResult;
				arr[row][col] = 0;
			}
		}
	}
	else
	{
		checkResult = SolveGame(arr, row, col + 1);
		if (checkResult == 0) return checkResult;
	}
	if (isFirst)
	{
		cout << "Khong co loi giai";
	}
	return 1;
}

void ReadFile(int arr[MAX_SQ][MAX_SQ], const string& file_name)
{
	using namespace std;
	ifstream file(file_name.c_str());
	if (file.is_open())
	{
		for (auto row = 0; row < MAX_SQ; ++row)
		{
			for (auto col = 0; col < MAX_SQ; ++col)
			{
				file >> arr[row][col];
			}
		}
		file.close();
	}
}

void LogArr(int arr[MAX_SQ][MAX_SQ])
{
	cout << "\n";

	for (auto row = 0; row < MAX_SQ; ++row)
	{
		cout << " | ";
		for (auto col = 0; col < MAX_SQ; ++col)
		{
			cout << myArray[row][col];
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

void WriteFile(int arr[MAX_SQ][MAX_SQ], const string& out_file_name)
{
	ofstream file2(out_file_name.c_str(), ofstream::out);
	for (int row = 0; row < MAX_SQ; ++row)
	{
		for (int col = 0; col < MAX_SQ; ++col)
		{
			file2 << arr[row][col] << " ";
		}
		file2 << "\n";
	}
	file2.close();
}

bool IsValid(int arr[MAX_SQ][MAX_SQ], int row, int col, int k)
{
	for (auto i = 0; i < MAX_SQ; i++)
	{
		if (arr[row][i] == k)
		{
			return false;
		}
	}
	for (auto i = 0; i < MAX_SQ; i++)
	{
		if (arr[i][col] == k)
		{
			return false;
		}
	}
	const auto a = row / 3;
	const auto b = col / 3;
	for (auto i = 3 * a; i < 3 * a + 3; i++)
	{
		for (auto j = 3 * b; j < 3 * b + 3; j++)
		{
			if (arr[i][j] == k)
			{
				return false;
			}
		}
	}
	return true;
}

//kiem tra mang ban dau
bool CheckValid(int arr[MAX_SQ][MAX_SQ])
{
	int arrCheck[MAX_SQ + 1];

	//check các hàng
	for (auto row = 0; row < MAX_SQ; row++)
	{
		ResetArr(arrCheck);
		for (auto col = 0; col < MAX_SQ; col++)
		{
			if (arr[row][col] < 0 || arr[row][col] > MAX_SQ)
			{
				//giá trị ko hợp lí.
				arr[row][col] = 0;
			}

			if (arr[row][col] != 0 && arrCheck[arr[row][col]] != 0)
			{
				//arrCheck[arr[row][col]] != 0 tức là đã tồn tại
				return false;
			}
			else
			{
				arrCheck[arr[row][col]] = 1;
			}
		}
	}

	//check các cột
	for (auto col = 0; col < MAX_SQ; col++)
	{
		ResetArr(arrCheck);
		for (auto row = 0; row < MAX_SQ; row++)
		{
			if (arr[row][col] != 0 && arrCheck[arr[row][col]] != 0)
			{
				return false;
			}
			arrCheck[arr[row][col]] = 1;
		}
	}

	//check các ô 3x3
	for (auto rowSq = 0; rowSq < 3; ++rowSq)
	{
		for (auto colSq = 0; colSq < 3; ++colSq)
		{
			ResetArr(arrCheck);
			for (auto row = 3 * rowSq; row < 3 * rowSq + 3; row++)
			{
				for (auto col = 3 * colSq; col < 3 * colSq + 3; col++)
				{
					if (arr[row][col] != 0 && arrCheck[arr[row][col]] != 0)
					{
						return false;
					}
					arrCheck[arr[row][col]] = 1;
				}
			}
		}
	}

	return true;
}

//đặt lại cái giá trị mảng check về 0
void ResetArr(int arr[MAX_SQ + 1])
{
	for (auto i = 0; i < MAX_SQ + 1; i++)
	{
		arr[i] = 0;
	}
}
