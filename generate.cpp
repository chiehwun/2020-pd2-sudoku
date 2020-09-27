#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "sudoku.h"
// #define DEBUG
using namespace std;
int rand_int(int low, int up);
int main() {
    srand(time(NULL));
    vector<vector<int>> input {
        {1, 9, 8, 2, 3, 4, 6, 5, 7},
        {6, 3, 4, 1, 5, 7, 8, 9, 2},
        {7, 5, 2, 9, 6, 8, 1, 3, 4},
        {4, 1, 6, 8, 9, 2, 3, 7, 5},
        {2, 7, 5, 6, 4, 3, 9, 8, 1},
        {9, 8, 3, 7, 1, 5, 2, 4, 6},
        {3, 6, 7, 5, 2, 9, 4, 1, 8},
        {5, 2, 9, 4, 8, 1, 7, 6, 3},
        {8, 4, 1, 3, 7, 6, 5, 2, 9},
    };
    Sudoku sudoku_root(input);
    int Lb[] = {0, 1, 0, 0, 0, 0}, Ub[] = {0, 9, 2, 2, 3, 1};
    int x=0, y=0, count = 0;
    bool unq = false;
    Sudoku sudoku_gen;
    do {
#ifdef DEBUG
        cout << boolalpha << '(' << ++count << ')' << endl;
#endif
        for(int i=1; i <= 5; i++) {
            x = rand_int(Lb[i], Ub[i]);
            y = rand_int(Lb[i], Ub[i]);
            sudoku_root.transCode(i, x, y);
        }
        sudoku_gen = sudoku_root.generate(sudoku_root.su);
        unq = sudoku_gen.isSolUniq();
#ifdef DEBUG
        cout << "isSolUniq: " << unq << endl << endl;
#endif
    } while(!unq);
    sudoku_gen.print(sudoku_gen.su);
    return 0;
}

int rand_int(int low, int up) {
    return (int)((random()/(RAND_MAX+1.0))*(up - low + 1.0) + low);
}
