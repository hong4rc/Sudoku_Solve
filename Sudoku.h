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
bool countRun = 0;

