#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>
#include <cstdlib>
using namespace std;

class Sudoku {
  public:
    Sudoku();
    Sudoku(vector<vector<int>>& board);
    // generate
    static Sudoku generate(vector<vector<int>>& board);
    void dig0(int i, int j);

    // transform
    void transCode(int ins, int x, int y);
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int getCellIdx(int i, int j);
    bool validation(vector<vector<int>>& board);
    bool isSolUniq();
    int solve();
    bool solve(int i, int j, vector<vector<int>>& board);
    bool update_excl(int mode, int val, int I, int J);

    // other methods
    void print(vector<vector<int>>& board);

    // member data
    int solNum;
    vector<vector<int>> su;
    vector<vector<int>> sol;
    vector<vector<int>> UnqSol;

  private:
    bitset<10> row[10];
    bitset<10> col[10];
    bitset<10> cell[10];
    bitset<10> excl[10][10];
};

#endif // SUDOKU_H
