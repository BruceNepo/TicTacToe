/**
  Input: 2D Boolean array (n * m)
  Output: Boolean. True - iff, 4 consecutive trues in a straight line (horiz, vert, diagonal - down left, down right)
                   False - otherwise

  F F F F F T F
  F F F F T F F
  F F F T F F F
  F F T F F F F
  F F F F F F F
  **/



#include <iostream>
#include <vector>
using namespace std;

enum {
    lMatch= 4,
};

typedef vector<int > Row ;
typedef vector<Row> Table;

Table data {
    { 0, 1, 1, 0, 0 }, // row 0
    { 1, 1, 1, 1, 1 }, // row 1
    { 0, 1, 1, 0, 0 }, // row 2
    { 0, 1, 1, 1, 0 }, // row 3
    { 1, 1, 1, 1, 1 }, // row 4
    { 1, 1, 1, 1, 1 }, // row 5
    { 0, 1, 1, 0, 0 }, // row 6
};

bool checkD(int i, int j, Table &dCount)
{
    if ( data[i][j] ) {
        if ( i == 0 || j == 0) {
            ++dCount[i][j];
        }
        else {
            if ( data[i - 1][j - 1] ) {
                dCount[i][j] = 1 + dCount[i - 1][j - 1];
            }
            else {
                dCount[i][j] = 1;
            }
        }

        if ( dCount[i][j] >= lMatch ) {
            cout << "D[r" << i << ",c" << j << "]" << endl;
            return true;
        }
    }
    return false;
}

int main() {
    int rSize = data.size();
    int cSize = 0;
    if (rSize) {
        cSize = data[0].size();
    }
    else {
        cout << "No data defined" << endl;
    }

    int   hCount      = 0 ;
    Row   vCount(cSize, 0);
    Table dCount(rSize, vCount);

    auto checkH = [&hCount](int i, int j) {
        if ( data[i][j] ) {
            if ( ++hCount >= lMatch ) {
                cout << "H[r" << i << ",c" << j - lMatch + 1 << "]" << endl;
                return true;
            }
        }
        else {
            hCount = 0;
        }
        return false;
    };

    auto checkV = [&vCount](int i, int j) {
        if ( data[i][j] ) {
            if ( i == 0 ) { // if the first row then just simply ++
                ++vCount[j];
            }
            else { // not the first row then will decide depending on previous row
                if ( data[i - 1][j] ) { // previous true has been counted now if previous was true ++ , otherwise 0
                    ++vCount[j];
                }
                else {
                    vCount[j] = 1; // we have at least one true in current position so it should be set to 1
                }
            }
            if ( vCount[j] >= lMatch ) {
                cout << "V[c" << j << ",r" << i - lMatch + 1 << "]" << endl;
                return true;
            }
        }
        return false;
    };

    for ( int i = 0; i < rSize; i++ ) {
        for ( int j = 0; j < cSize; j++ ) {
            // look for match in current position for row
            if (checkH(i, j)) { /*return true;*/ }

            // look for match in current position for column
            if (checkV(i, j)) { /*return true;*/ }

            // look for match in current postion for diagonal
            if (checkD(i, j, dCount)) { /*return true;*/ }
        }
        hCount = 0;
    }
    cout << "end" << endl;
    return 0;
}
