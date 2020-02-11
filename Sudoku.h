#pragma once

#include <fstream>
#include <list>

using namespace std;

class Sudoku
{
public:
    Sudoku(ifstream*);
    ~Sudoku();
    int& at(int, int) const;
    int& at(int) const;
    bool isValid();
    bool isValid(void(*next)(int&, int&), int row, int col);
    bool isValidRow(const int);
    bool isValidCol(const int);
    bool isValidMiniSquare(const int, const int);
    void capture();
    void setLimit(int);
    int getLimit();
    bool isFull();
    void clear();
    int count();

    static const int MINI_SQUARE_LENGTH = 3;
    static const int SQUARE_LENGTH = MINI_SQUARE_LENGTH * MINI_SQUARE_LENGTH;
    friend ostream& operator << (ostream& out, const Sudoku& c);
private:
    int* data;
    int limit = 0;
    list<int*> *results;
    int check1to9[SQUARE_LENGTH] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    void resetCheck();
    static void nextRow(int& row, int& col);
    static void nextCol(int& row, int& col);
    static void nextSquare(int& row, int& col);
};
