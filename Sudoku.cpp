#include <iostream>
#include <fstream>

#define MAX_SQ 9
#define INPUT_NAME_FILE "INPUT.TXT"
#define OUTPUT_NAME_FILE "OUTPUT.TXT"

using namespace std;
int myArray[MAX_SQ][MAX_SQ];

void readFile(int arr[MAX_SQ][MAX_SQ], const string &file_name);

void logFile(int arr[MAX_SQ][MAX_SQ], const string &out_file_name);

void solveGame(int arr[MAX_SQ][MAX_SQ], int x, int y);

bool isValid(int arr[MAX_SQ][MAX_SQ], int x, int y, int k);

int main() {
    readFile(myArray, INPUT_NAME_FILE);
    logFile(myArray, OUTPUT_NAME_FILE);
    solveGame(myArray, 0, 0);
}


void readFile(int arr[MAX_SQ][MAX_SQ], const string &file_name) {
    using namespace std;
    ifstream file(file_name.c_str());
    if (file.is_open()) {

        for (int i = 0; i < MAX_SQ; ++i) {
            for (int j = 0; j < MAX_SQ; ++j) {
                file >> arr[i][j];
            }
        }
    }
    file.close();
}

void logFile(int arr[MAX_SQ][MAX_SQ], const string &out_file_name) {
    cout << "\n";

    for (int i = 0; i < MAX_SQ; ++i) {
        for (int j = 0; j < MAX_SQ; ++j) {
            cout << myArray[i][j] << "|";
        }
        if (i % 3 == 2) {
            cout << "\n------------------";
        }
        cout << "\n";
    }

    ofstream file2(out_file_name.c_str(), ofstream::out);
    for (int i = 0; i < MAX_SQ; ++i) {
        for (int j = 0; j < MAX_SQ; ++j) {
            file2 << arr[i][j] << " ";
        }
        file2 << "\n";
    }
    file2.close();
}

void solveGame(int arr[MAX_SQ][MAX_SQ], int x, int y) {
    if (y == MAX_SQ) {
        if (x == MAX_SQ - 1) {
            logFile(arr, OUTPUT_NAME_FILE);
            exit(0);
        } else {
            solveGame(arr, x + 1, 0);
        }
    } else if (arr[x][y] == 0) {
        for (int k = 1; k <= MAX_SQ; k++) {
            if (isValid(arr, x, y, k)) {
                arr[x][y] = k;
                solveGame(arr, x, y);
                arr[x][y] = 0;
            }
        }
    } else {
        solveGame(arr, x, y + 1);
    }
}

bool isValid(int arr[MAX_SQ][MAX_SQ], int x, int y, int k) {
    for (int i = 0; i < MAX_SQ; i++) {
        if (arr[x][i] == k) return false;
    }
    for (int i = 0; i < MAX_SQ; i++) {
        if (arr[i][y] == k) return false;
    }
    int a = x / 3, b = y / 3;
    for (int i = 3 * a; i < 3 * a + 3; i++) {
        for (int j = 3 * b; j < 3 * b + 3; j++) {
            if (arr[i][j] == k) return false;
        }
    }
    return true;
}
