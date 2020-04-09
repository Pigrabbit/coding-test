// Problem: https://www.acmicpc.net/problem/5427

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

#define vec vector

const char EMPTY = '.';
const char WALL = '#';
const char SANG_GEUN = '@';
const char FIRE = '*';

const int MAX_HEIGHT = 1000, MAX_WIDTH = 1000;
char building[MAX_HEIGHT][MAX_WIDTH];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

using namespace std;

bool isInRange(int y, int x, int height, int width) {
    return (y < height) && (y >= 0) && (x < width) && (x >= 0);
}

int escape(int height, int width, vec<int> & sanggeunPos, vec<vec<int>> & fire) {
    int minMoves = 987654321;
    int fireArrival[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    memset(fireArrival, 0, sizeof(fireArrival));
    queue<vec<int>> bfsQueue;
    for (int i = 0; i < fire.size(); i++) {
        bfsQueue.push(fire[i]);
    }

    while(!bfsQueue.empty()) {
        int curY = bfsQueue.front()[0], curX = bfsQueue.front()[1];
        bfsQueue.pop();
        for (int i = 0; i < 4; i++) {
            int newY = curY + dy[i], newX = curX + dx[i];
            if (!isInRange(newY, newX, height, width)) continue;
            if (building[newY][newX] == EMPTY || building[newY][newX] == SANG_GEUN) {
                if (fireArrival[newY][newX] == 0) {
                    fireArrival[newY][newX] = fireArrival[curY][curX] + 1;
                    bfsQueue.push({newY, newX});
                }
            }
        }
    }

    int sanggeunArrival[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    memset(sanggeunArrival, 0, sizeof(sanggeunArrival));
    bfsQueue.push(sanggeunPos);

    while (!bfsQueue.empty()) {
        int curY = bfsQueue.front()[0], curX = bfsQueue.front()[1];
        bfsQueue.pop();
        for (int i = 0; i < 4; i++) {
            int newY = curY + dy[i], newX = curX + dx[i];
            if (isInRange(newY, newX, height, width)) {
                if (building[newY][newX] == EMPTY && sanggeunArrival[newY][newX] == 0) {
                    sanggeunArrival[newY][newX] = sanggeunArrival[curY][curX] + 1;
                    bfsQueue.push({newY, newX});
                }
            }
            else {
                if (fireArrival[curY][curX] == 0 || sanggeunArrival[curY][curX] < fireArrival[curY][curX]) {
                    if (minMoves == 987654321 || minMoves > sanggeunArrival[curY][curX] + 1) {
                        minMoves = sanggeunArrival[curY][curX] + 1;
                    }
                }
            }
        }
    }

    return minMoves;
}

int main() {
    int numTestCase = 0;
    cin >> numTestCase;
    
    vec<string> answer;
    int width = 0, height = 0;
    
    while (numTestCase--) {
        memset(building, '\0', sizeof(building));
        cin >> width >> height;  
        string strIn;
        vec<vec<int>> fire;
        vec<int> sanggeunPos;

        for (int y = 0; y < height; y++) {
            cin >> strIn;
            for (int x = 0; x < width; x++) {
                building[y][x] = strIn[x];
                if (strIn[x] == FIRE) fire.push_back({y, x});
                else if(strIn[x] == SANG_GEUN) sanggeunPos = {y, x};
            }
        }
        
        int result = escape(height, width, sanggeunPos, fire);
        if (result != 987654321) answer.push_back(to_string(result));
        else answer.push_back("IMPOSSIBLE");
    }

    for (auto a: answer) {
        cout << a << "\n";
    }

    return 0;
}
