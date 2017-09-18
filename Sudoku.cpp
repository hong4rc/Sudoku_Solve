#include <iostream>
#include <fstream>

#define MAX_SQ 9
//#define NEXT_COL col + 1
//#define NEXT_ROW row + 1
#define MAX_SQ 9
#define INPUT_NAME_FILE "INPUT.TXT"
#define OUTPUT_NAME_FILE "OUTPUT.TXT"

using namespace std;

int myArray[MAX_SQ][MAX_SQ];
void logArr(int arr[MAX_SQ][MAX_SQ]);

void readFile(int arr[MAX_SQ][MAX_SQ], const string &file_name);
void writeFile(int arr[MAX_SQ][MAX_SQ], const string &out_file_name);


int solveGame(int arr[MAX_SQ][MAX_SQ], int x, int y);
   
bool isValid(int arr[MAX_SQ][MAX_SQ], int x, int y, int k);
bool checkValid(int arr[MAX_SQ][MAX_SQ]);
void resetArr(int arr[MAX_SQ + 1]);

int main() {
    readFile(myArray, INPUT_NAME_FILE);
    cout << "\nInput:";
    logArr(myArray);
    if(checkValid(myArray)){
        cout << "ok";
        solveGame(myArray, 0, 0);
    } else{
        cout << "Rat tiec khong the giai dc";
    }
    getchar();
}

int solveGame(int arr[MAX_SQ][MAX_SQ], int row, int col) {
	int checkResult = -1;
    if (col == MAX_SQ) {
        if (row == MAX_SQ - 1) {
            cout << "\nOutput:";
            logArr(arr);
            writeFile(arr, OUTPUT_NAME_FILE);
            //exit(0);
            return 0;
        } else {
            checkResult = solveGame(arr, row + 1, 0);
            if(checkResult == 0) return checkResult;
        }
    } else if (arr[row][col] == 0) {
        for (int k = 1; k <= MAX_SQ; k++) {
            if (isValid(arr, row, col, k)) {
                arr[row][col] = k;
                checkResult = solveGame(arr, row, col + 1);
                if(checkResult == 0) return checkResult;
                arr[row][col] = 0;
            }
        }
    } else {
        checkResult = solveGame(arr, row, col + 1);
        if(checkResult == 0) return checkResult;
    }
    return -1;
}


void readFile(int arr[MAX_SQ][MAX_SQ], const string &file_name) {
    using namespace std;
    ifstream file(file_name.c_str());
    if (file.is_open()) {

        for (int row = 0; row < MAX_SQ; ++row) {
            for (int col = 0; col < MAX_SQ; ++col) {
                file >> arr[row][col];
            }
        }
    }
    file.close();
}

void logArr(int arr[MAX_SQ][MAX_SQ]) {
    cout << "\n";

    for (int row = 0; row < MAX_SQ; ++row) {
        for (int col = 0; col < MAX_SQ; ++col) {
            cout << myArray[row][col] << "|";
        }
        if (row % 3 == 2) {
            cout << "\n------------------";
        }
        cout << "\n";
    }
}

void writeFile(int arr[MAX_SQ][MAX_SQ], const string &out_file_name) {
    ofstream file2(out_file_name.c_str(), ofstream::out);
    for (int row = 0; row < MAX_SQ; ++row) {
        for (int col = 0; col < MAX_SQ; ++col) {
            file2 << arr[row][col] << " ";
        }
        file2 << "\n";
    }
    file2.close();
}

bool isValid(int arr[MAX_SQ][MAX_SQ], int row, int col, int k) {
    for (int i = 0; i < MAX_SQ; i++) {
        if (arr[row][i] == k) return false;
    }
    for (int i = 0; i < MAX_SQ; i++) {
        if (arr[i][col] == k) return false;
    }
    int a = row / 3, b = col / 3;
    for (int i = 3 * a; i < 3 * a + 3; i++) {
        for (int j = 3 * b; j < 3 * b + 3; j++) {
            if (arr[i][j] == k) return false;
        }
    }
    return true;
}


bool checkValid(int arr[MAX_SQ][MAX_SQ]){
    int arrCheck[MAX_SQ + 1];
    for(int row = 0; row < MAX_SQ; row++){
        resetArr(arrCheck);
        for(int col = 0; col < MAX_SQ; col++){
            if(arr[row][col] < 0 || arr[row][col] > MAX_SQ){
                arr[row][col] = 0;
            }
            
            if(arr[row][col] != 0 && arrCheck[arr[row][col]] != 0){
                return false;
            } else {
                arrCheck[arr[row][col]] = 1;
            }
        }
    }

    for(int col = 0; col < MAX_SQ; col++){
        resetArr(arrCheck);
        for(int row = 0; row < MAX_SQ; row++){
            
            if(arr[row][col] != 0 && arrCheck[arr[row][col]] != 0){
                return false;
            } else {
                arrCheck[arr[row][col]] = 1;
            }
        }
    }
    
    for(int rowSq = 0; rowSq < 3; ++rowSq ){
        for(int colSq = 0; colSq < 3; ++colSq ){
            resetArr(arrCheck);
            for (int row = 3 * rowSq; row < 3 * rowSq + 3; row++) {
                for (int col = 3 * colSq; col < 3 * colSq + 3; col++) {
                    
                    if(arr[row][col] != 0 && arrCheck[arr[row][col]] != 0){
                        return false;
                    } else {
                        arrCheck[arr[row][col]] = 1;
                    }
                }
            }
        }
    }
    
    return true;
}

void resetArr(int arr[MAX_SQ + 1]){
    for(int i = 0; i < MAX_SQ + 1; i++){
        arr[i] = 0;
    }
}
