#include <iostream>
#include "sudoku.h"
// #define DEBUG
using namespace std;
int main() {
    vector<vector<int>> input(9, vector<int>(9, 0));
    for(int i=0; i < 9; i++)
        for(int j=0; j < 9; j++)
            cin >> input[i][j];
    Sudoku sudoku(input);
#ifdef DEBUG
    cout << "You are now in DEBUG mode!" << endl <<
         "Wish you have a good luck, dude." << endl;
    cout << "input: " << endl;
    sudoku.print(sudoku.su);
#endif
    int numSu = sudoku.solve();
#ifdef DEBUG
    cout << "\n\noutput:" << endl;
#endif
    cout << numSu << endl;
#ifndef DEBUG
    if(numSu == 1) {
        sudoku.print(sudoku.UnqSol);
    }
#endif
#ifdef DEBUG
    cout << "UnqSol:" << endl;
    sudoku.print(sudoku.UnqSol);
#endif
    return 0;
}
