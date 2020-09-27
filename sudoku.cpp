#include "sudoku.h"
// #define DEBUG
using namespace std;
Sudoku::Sudoku() {
    solNum = 0;
    vector<vector<int>> init(9, vector<int>(9, 0));
    su = sol = UnqSol = init;
}
Sudoku::Sudoku(vector<vector<int>>& board) {
    solNum = 0;
    vector<vector<int>> init(9, vector<int>(9, 0));
    su = sol = UnqSol = init;
    su = board;
}
Sudoku Sudoku::generate(vector<vector<int>>& board) {
    Sudoku clone;
    clone.su = board;
    // shuffle the positions of '0'
    int shuffle[81];
    for(int s=0; s < 81; s++)
        shuffle[s] = s;
    int p1=0, p2=0, temp;
    for(int s=0; s < 81; s++) {
        p1 = (int)((random()/(RAND_MAX+1.0))*(80 + 1.0)+0);
        p2 = (int)((random()/(RAND_MAX+1.0))*(80 + 1.0)+0);
        temp = shuffle[p1];
        shuffle[p1] = shuffle[p2];
        shuffle[p2] = temp;
    }
    // create '0'
    for(int k=0; k < 50; k++) {
        int Ind = shuffle[k];
        clone.dig0(Ind/9, Ind%9);
    }
    return clone;
}
void Sudoku::dig0(int i, int j) {
    su[i][j] = 0;
}
void Sudoku::print(vector<vector<int>>& board) {
    for(int i=0; i < 9; i++) {
        for(int j=0; j < 9; j++) {
            cout << board[i][j] << (j == 8 ? "" : " ");
        }
        cout << endl;
    }
}
void Sudoku::transCode(int ins, int x, int y) {
    switch(ins) {
    case 1:
        swapNum(x, y);
        break;
    case 2:
        swapRow(x, y);
        break;
    case 3:
        swapCol(x, y);
        break;
    case 4:
        rotate(x);
        break;
    case 5:
        flip(x);
        break;
    default:
        break;
    }
}
void Sudoku::swapNum(int x, int y) {
    for(int i=0; i < 9; i++)
        for(int j=0; j < 9; j++) {
            if(su[i][j] == x)
                su[i][j] = y;
            else if(su[i][j] == y)
                su[i][j] = x;
        }
}
void Sudoku::swapRow(int x, int y) {
    for(int i=0; i < 3; i++)
        su[x*3+i].swap(su[y*3+i]);
}
void Sudoku::swapCol(int x, int y) {
    int t=0;
    for(int k=0; k < 3; k++) {
        for(int i=0; i < 9; i++) {
            t = su[i][x*3+k];
            su[i][x*3+k] = su[i][y*3+k];
            su[i][y*3+k] = t;
        }
    }
}
void Sudoku::rotate(int x) {
    int t=0;
    for(int r=0; r < x%4; r++)
        for(int g=0; g < 4; g++)
            for(int k=0; k < 8-g*2; k++) {
                t = su[g+k][g];
                su[g+k][g] = su[8-g][g+k];
                su[8-g][g+k] = su[8-g-k][8-g];
                su[8-g-k][8-g] = su[g][8-g-k];
                su[g][8-g-k] = t;
            }
}
void Sudoku::flip(int x) {
    if(x == 0)
        for(int i=0; i < 4; i++)
            su[i].swap(su[8-i]);
    else {
        int t=0;
        for(int j=0; j < 4; j++) {
            for(int i=0; i < 9; i++) {
                t = su[i][j];
                su[i][j] = su[i][8-j];
                su[i][8-j] = t;
            }
        }
    }

}
int Sudoku::getCellIdx(int i, int j) {
    return (i/3)*3 + j/3;   // cell = 0-8
}
bool Sudoku::update_excl(int mode, int val, int I, int J) {
#ifdef DEBUG
    cout << "(" << val << ")" << endl;
    for(int i=0; i < 9; i++) {
        for(int j=0; j < 9; j++) {
            cout << excl[i][j].test(val) << ' ';
        }
        cout << endl;
    }
    cout << endl;
#endif
    // No solution Case 2
    if( row[I].test(val) || col[J].test(val) ||
            cell[getCellIdx(I, J)].test(val)) {
#ifdef DEBUG
        cout << "No solution case2" << endl;
#endif
        return true;
    }

    row[I].set(val);
    col[J].set(val);
    cell[getCellIdx(I, J)].set(val);
    // Row Update mode=0
    if(mode != 0) {
        for(int j=0; j < 9; j++)
            excl[I][j].set(val);
    }

    // Col Update mode=1
    if(mode != 1) {
        for(int i=0; i < 9; i++)
            excl[i][J].set(val);
    }

    // Cell Update mode=2
    if(mode != 2) {
        int C = getCellIdx(I, J);
        int pi = 0, pj = 0;
        for(int cj=0; cj < 9; cj++) {
            pi = (C/3)*3 + cj/3;
            pj = cj%3 + (C%3)*3;
            excl[pi][pj].set(val);
        }
    }
#ifdef DEBUG
    cout << "[" << val << "]" << endl;
    for(int i=0; i < 9; i++) {
        for(int j=0; j < 9; j++) {
            cout << excl[i][j].test(val) << ' ';
        }
        cout << endl;
    }
    cout << endl;
#endif
    return false;
}
bool Sudoku::validation(vector<vector<int>>& board) {
    sol = board;
    // Reset row, col, cell, excl
    int UMEcount = 0;
    int UMEsolved = 0;
    do {
        UMEsolved = 0;
#ifdef DEBUG
        cout << "UME Start: "<< ++UMEcount << endl;
#endif
        for(int i=0; i < 10; i++) {
            for(int j=0; j < 10; j++) {
                if(j == 0) {
                    row[i].reset();
                    col[i].reset();
                    cell[i].reset();
                }
                excl[i][j].reset();
            }
        }
        // Create row, col, cell
        for(int i=0; i < 9; i++) {
            for(int j=0; j < 9; j++) {
                int val = sol[i][j];
                if(val != 0)
                    // no solution case 1
                    if( row[i].test(val) || col[j].test(val) ||
                            cell[getCellIdx(i, j)].test(val))
                        return false;
                    else {
                        row[i].set(val);
                        col[j].set(val);
                        cell[getCellIdx(i, j)].set(val);
                    }
            }
        }

        // Unit exclusive methods (only one num is possible)
        // * Create excl[][]
        for(int val=1; val <= 9; val++) {
#ifdef DEBUG
            cout << "(" << val << ")" << endl;
#endif
            for(int i=0; i < 9; i++) {
                for(int j=0; j < 9; j++) {
                    if( sol[i][j] != 0 ||
                            row[i].test(val) ||
                            col[j].test(val) ||
                            cell[getCellIdx(i, j)].test(val)) {
                        excl[i][j].set(val);
                    }
#ifdef DEBUG
                    cout << excl[i][j].test(val) << ' ';
#endif
                }
#ifdef DEBUG
                cout << endl;
#endif
            }
#ifdef DEBUG
            cout << endl << endl;
#endif
        }
        // * Detect each layer(val 1-9)
        int solvedNumTot = 0;
        for(int val=1; val <= 9; val++) {
            int solvedNum = 0;
            do {
#ifdef DEBUG
                cout << "GOGOG=" << val << endl;
#endif
                solvedNum = 0;
                // check Row
                int pos = 0, count = 0;
                for(int i=0; i < 9; i++) {
                    pos = count = 0;
                    for(int j=0; j < 9; j++) {
                        if(!excl[i][j].test(val)) {
                            count++;
                            pos = j;
                        }
                    }
                    if(count == 1) {
                        if(sol[i][pos] != 0) {
#ifdef DEBUG
                            cout << "Row_false" << endl;
#endif
                            return false;
                        }
                        if(update_excl(0, val, i, pos))
                            return false;
                        sol[i][pos] = val;
                        ++UMEsolved;
                        ++solvedNum;
#ifdef DEBUG
                        cout << "<R" << val << '.' << solvedNum << '>' << endl;
                        print(sol);
                        cout << endl;
#endif
                    }
                }
                // check Col
                for(int j=0; j < 9; j++) {
                    pos = count = 0;
                    for(int i=0; i < 9; i++) {
                        if(!excl[i][j].test(val)) {
                            count++;
                            pos = i;
                        }
                    }
                    if(count == 1) {
                        if(sol[pos][j] != 0) {
#ifdef DEBUG
                            cout << "Col_false" << endl;
#endif
                            return false;
                        }
                        if(update_excl(1, val, pos, j))
                            return false;
                        sol[pos][j] = val;
                        ++solvedNum;
                        ++UMEsolved;
#ifdef DEBUG
                        cout << "<C" << val << '.' << solvedNum << '>' << endl;
                        print(sol);
                        cout << endl;
#endif
                    }
                }
                // check Cell
                int pi=0, pj=0, piS = 0, pjS = 0;
                for(int ci=0; ci < 9; ci++) {
                    pi = pj = count = 0;
                    for(int cj=0; cj < 9; cj++) {
                        pi = ci/3*3 + cj/3;
                        pj = cj%3 + ci%3*3;
                        if(!excl[pi][pj].test(val)) {
                            count++;
                            piS = pi;
                            pjS = pj;
                        }
                    }
                    if(count == 1) {
                        if(sol[piS][pjS] != 0) {
#ifdef DEBUG
                            cout << "Cell_false" << endl;
#endif
                            return false;
                        }
                        sol[piS][pjS] = val;
                        if(update_excl(2, val, piS, pjS))
                            return false;
                        ++solvedNum;
                        ++UMEsolved;
#ifdef DEBUG
                        cout << "<CL" << val << '.' << solvedNum << '>' << endl;
                        print(sol);
                        cout << endl;
#endif
                    }
                }
                solvedNumTot += solvedNum;
            } while(solvedNum > 0);
        }
    } while(UMEsolved != 0);
#ifdef DEBUG
    cout << "Unit exclusive methods ENDS" << "(" << UMEcount << ")" << endl;
#endif
    return true;
}
bool Sudoku::isSolUniq() {
    return solve() == 1;
}
int Sudoku::solve() {
    if(!validation(su)) // row[], col[], cell[] presetting
        return 0;
#ifdef DEBUG
    cout << "solving..." << endl;
#endif
    solNum = 0;
    solve(0, 0, sol);
#ifdef DEBUG
    cout << "solve end." << endl;
#endif
    if(UnqSol[0][0] == 0)
        return 0;
    return solNum >= 2? 2:1;
}
bool Sudoku::solve(int i, int j, vector<vector<int>>& board) {
    if(j >= 9)
        return solve(i+1, 0, board);
    if(i == 9) {
        solNum++;
#ifdef DEBUG
        cout << solNum << endl;
#endif
        if(solNum >= 2)
            return true;
        UnqSol = sol;
        return false;
    }
    if(board[i][j] != 0)
        return solve(i, j+1, board);
    else {
        for(int val = 1; val <= 9; val++) {
            if(!row[i].test(val) && !col[j].test(val) && !cell[getCellIdx(i, j)].test(val)) {
                row[i].set(val), col[j].set(val), cell[getCellIdx(i, j)].set(val);
                board[i][j] = val;
                if(solve(i, j+1, board))
                    return true;
                board[i][j] = 0;
                row[i].reset(val), col[j].reset(val), cell[getCellIdx(i, j)].reset(val);
            }
        }
    }
    return false;
}
