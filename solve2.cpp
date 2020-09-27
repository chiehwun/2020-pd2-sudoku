#include <iostream>
#include "sudoku.h"
// #define DEBUG
using namespace std;
int main() {
#ifdef DEBUG
    cout << "You are now in DEBUG mode!" << endl <<
         "Wish you have a good luck, dude." << endl;
#endif
    Sudoku sudoku;
    vector<vector<int>> input(9, vector<int>(9, 0));
    for(int s=1; s <= 15; s++) {
        cout << endl;
        cout << "<" << s << ">" << endl;
        char c;
        for(int i=0; i < 9; i++) {
            for(int j=0; j < 9; j++) {
                cin >> c;
                if(c == '.')
                    input[i][j] = 0;
                else
                    input[i][j] = c-'0';
            }
        }
        sudoku.su = input;
#ifdef DEBUG
        cout << "input: " << endl;
        sudoku.print(sudoku.su);
#endif
        int numSu = sudoku.solve();
#ifdef DEBUG
        cout << "\n\noutput:" << endl;
#endif
        cout << numSu << endl;
#ifndef DEBUG
        if(numSu == 1)
            sudoku.print(sudoku.UnqSol);
#endif
#ifdef DEBUG
        cout << "UnqSol:" << endl;
        sudoku.print(sudoku.UnqSol);
#endif
    }
    return 0;
}
