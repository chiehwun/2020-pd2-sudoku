#include <iostream>
#include "sudoku.h"
using namespace std;
int main() {
    vector<vector<int>> input(9, vector<int>(9, 0));
    for(int i=0; i < 9; i++)
        for(int j=0; j < 9; j++)
            cin >> input[i][j];

    Sudoku sudoku(input);
    int ins=0, x=0, y=0;
    do {
        cin >> ins;
        switch(ins) {
        case 0:
            sudoku.print(sudoku.su);
            break;
        case 1:
        case 2:
        case 3:
            cin >> x >> y;
            break;
        case 4:
        case 5:
            cin >> x;
            break;
        default:
            exit(1);
        }
        sudoku.transCode(ins, x, y);
    } while(ins != 0);
    return 0;
}
