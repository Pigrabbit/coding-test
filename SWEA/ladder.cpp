// Problem: 1210

#include <iostream>
#include <cstring>
#include <vector>

#define vec vector

using namespace std;

const int WIDTH = 100, HEIGHT = 100;
int board[HEIGHT+1][WIDTH+1];

int main() {
    int numTestCase = 10;

    for (int i = 1; i <= numTestCase; i++) {
        int testCaseIndex = 0;
        cin >> testCaseIndex;

        vec<int> start;
        memset(board, 0, sizeof(board));
        // Get Input
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                cin >> board[y][x];
                if (board[y][x] == 2) start = {y, x}; 
            }
        }
        
        int curY = start[0], curX = start[1];
        while (curY > 0) {
            // check if cur path is edge of the board
            bool isRightEnd = (curX == WIDTH - 1)? true : false;
            bool isLeftEnd = (curX == 0)? true : false;

            if (isRightEnd) {
                bool toLeft = false;
                while (true) {
                    if (curY == 0) break;
                    if (board[curY][curX-1] == 1) {
                        toLeft = true;
                        break;
                    }
                    curY--;
                }

                if (toLeft && curX - 1 >= 0) {
                    while (true) {
                        if (curX < 0) break;
                        if (board[curY][curX-1] == 0) break;
                        curX--;
                    }
                    curY--;
                    if (curY == 0) break;
                }
            }
            else if (isLeftEnd) {
                bool toRight = false;
                while (true) {
                    if (curY == 0) break;
                    if (board[curY][curX+1] == 1) {
                        toRight = true;
                        break;
                    }
                    curY--;
                }

                if (toRight && curX + 1 < WIDTH) {
                    while (true) {
                        if (curX > WIDTH - 1) break;
                        if (board[curY][curX+1] == 0) break;
                        curX++;
                    }
                    curY--;
                    if (curY == 0) break;
                }
            }
            else {
                bool toLeft = false;
                bool toRight = false;
                while (true) {
                    if (curY == 0) break;
                    if (board[curY][curX - 1] == 1) {
                        toLeft = true;
                        break;
                    }
                    if (board[curY][curX + 1] == 1) {
                        toRight = true;
                        break;
                    }
                    curY--;
                }
                if (curY == 0) break;

                if (toLeft && curX - 1 >= 0) {
                    while (true) {
                        if(curX < 0) break;
                        if (board[curY][curX-1] == 0) break;
                        curX--;
                    }
                    curY--;
                    if (curY == 0) break;
                }

                if (toRight && curX + 1 < WIDTH) {
                    while(true) {
                        if (curX > WIDTH) break;
                        if (board[curY][curX + 1] == 0) break;
                        curX++;
                    }
                    curY--;
                    if(curY == 0) break;
                }
            }
        }

    if (curY == 0) cout << "#" << testCaseIndex << " " << curX << "\n";
    }

    return 0;
}
