// Problem: https://www.acmicpc.net/problem/7562

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

// Clock wise:  1,2  4,5  7,8  10,11
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int getMinMove(vector<int> &startPos, vector<int> &destPos, int boardSize) {
    if (startPos == destPos) return 0;
    int moves = INT_MAX;

    bool checked[boardSize][boardSize];
    memset(checked, false, sizeof(checked));
    queue<vector<int>> bfsQueue;
    bfsQueue.push({startPos[0], startPos[1], 0});

    while (!bfsQueue.empty()) {
        int curX = bfsQueue.front()[1], curY = bfsQueue.front()[0];
        int timesMoved = bfsQueue.front()[2];
        bfsQueue.pop();

        for (int i = 0; i < 8; i++) {
            int newX = curX + dx[i], newY = curY + dy[i];
            if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize) {
                if (newX == destPos[1] && newY == destPos[0]) {
                    moves = min(moves, timesMoved + 1);
                }
                if (!checked[newY][newX]) {
                    checked[newY][newX] = true;
                    bfsQueue.push({newY, newX, timesMoved + 1});
                }
            }
        }
    }

    return moves;
}

TEST_CASE("getMinMove") {
    SECTION("example 1") {
        vector<int> curPos = {0, 0};
        vector<int> destPos = {7, 0};
        int boardSize = 8;
        REQUIRE(getMinMove(curPos, destPos, boardSize) == 5);
    }
    SECTION("example 2") {
        vector<int> curPos = {0, 0};
        vector<int> destPos = {30, 50};
        int boardSize = 100;
        REQUIRE(getMinMove(curPos, destPos, boardSize) == 28);
    }
    SECTION("example 3") {
        vector<int> curPos = {1, 1};
        vector<int> destPos = {1, 1};
        int boardSize = 10;
        REQUIRE(getMinMove(curPos, destPos, boardSize) == 0);
    }
}

int main() {
    int numTestCase = 0, boardSize = 0;
    cin >> numTestCase;
    vector<int> answers(numTestCase, 0);
    
    for (int i = 0; i < numTestCase; i++) {
        cin >> boardSize;
        // pos: (y, x)
        vector<int> curPos(2, 0), destPos(2, 0);
        cin >> curPos[1] >> curPos[0] >> destPos[1] >> destPos[0];
        answers[i] = getMinMove(curPos, destPos, boardSize);
    }

    for (auto answer: answers) {
        cout << answer << "\n";
    }

    return 0;
}

