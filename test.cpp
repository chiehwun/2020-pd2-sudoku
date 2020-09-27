#include <iostream>
// #define DEBUG
using namespace std;
int main() {
    for(int ci=0; ci < 9; ci++) {
        for(int cj=0; cj < 9; cj++) {
            cout << "i=" << ci/3*3 + cj/3 << "  j=" << cj%3 + ci%3*3 << endl;
        }
    }
#ifdef DEBUG
    cout << "DEDE" << endl;
#endif
    return 0;
}
