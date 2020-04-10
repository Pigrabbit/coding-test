// Problem: https://www.acmicpc.net/problem/13460

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

#define vec vector

const char EMPTY = '.';
const char WALL = '#';
const char HOLE = 'O';
const char RED_MARBLE = 'R';
const char BLUE_MARBLE = 'B';

const int MAX_HEIGHT = 10, MAX_WIDTH = 10;
char board[MAX_HEIGHT + 1][MAX_WIDTH + 1];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, - 1, 0, 0};

bool isInRange(int y, int x, int height, int width) {
    return (y >= 0) && (y < height) && (x >= 0) && (x < width);
}

int bfs(int height, int width, vec<int> &redPos, vec<int> &bluePos) {
    queue<vec<int>> bfsQueue;
    // red y, red x, blue y, blue x, time
    int visited[MAX_HEIGHT][MAX_WIDTH][MAX_HEIGHT][MAX_WIDTH] = {0, };
    visited[redPos[0]][redPos[1]][bluePos[0]][bluePos[1]] = 1;
    int ret = -1;
    bfsQueue.push({redPos[0], redPos[1], bluePos[0], bluePos[1], 0});

    while(!bfsQueue.empty()) {
        vec<int> cur = bfsQueue.front();
        int curRedY = bfsQueue.front()[0], curRedX = bfsQueue.front()[1];
        int curBlueY = bfsQueue.front()[2], curBlueX = bfsQueue.front()[3];
        int curCount = bfsQueue.front()[4];
        bfsQueue.pop();
        if (curCount > 10) {
            break;
        }
        if (board[curRedY][curRedX] == HOLE && board[curBlueY][curBlueX] != HOLE) {
            cout << "Update return: " << curCount << "\t";
            cout << "Red Pos: (" << curRedY << ", " << curRedX << ") Blue Pos: (" << curBlueY << ", " << curBlueX << ") \n";
            ret = curCount;
            break;
        }
        if (board[curRedY][curRedX] == HOLE && board[curBlueY][curBlueX] == HOLE) {
            continue;
        }
        if (board[curRedY][curRedX] != HOLE && board[curBlueY][curBlueX] == HOLE) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            vec<int> next = cur;

            // move red
            while (true) {
                // 벽이 아니면 밀기 가능
                if (board[next[0] + dy[i]][next[1] + dx[i]] != WALL) {
                    next[0] += dy[i];
                    next[1] += dx[i];
                }
                // 밀다가 구멍 만나면 종료 조건
                if (board[next[0]][next[1]] == HOLE) {
                    break;
                }
                // 벽을 만나면 더 이상 못 밀어
                if (board[next[0] + dy[i]][next[1] + dx[i]] == WALL) {
                    break;
                }
            }

            // move blue
            while (true) {
                if (board[next[2] + dy[i]][next[3] + dx[i]] != WALL) {
                    next[2] += dy[i];
                    next[3] += dx[i];
                }
                if (board[next[2]][next[3]] == HOLE) {
                    break;
                }
                if (board[next[2] + dy[i]][next[3] + dx[i]] == WALL) {
                    break;
                }
            }

            if (next[0] == next[2] && next[1] == next[3]) {
                // 굴리기 종료 후, 두 구슬의 위치가 같은 경우
                if (board[next[0]][next[1]] != HOLE) {
                    int distRedMoved = abs((next[0] - curRedY) + (next[1] - curRedX));
                    int distBlueMoved = abs((next[2] - curBlueY) + (next[3] - curBlueX));
                    if (distRedMoved > distBlueMoved) {
                        next[0] -= dy[i];
                        next[1] -= dx[i];
                    }
                    else {
                        next[2] -= dy[i];
                        next[3] -= dx[i];
                    }
                }
            }

            if (visited[next[0]][next[1]][next[2]][next[3]] == 0) {
                visited[next[0]][next[1]][next[2]][next[3]] = 1;
                next[4] = curCount + 1;
                cout << "Red Pos: (" << next[0] << ", " << next[1] << ") Blue Pos: (" << next[2] << ", " << next[3] << ") count: " << next[4]<< "\n";
                bfsQueue.push(next);
            }
        }
    }

    return ret;
}

int main() {
    int height = 0, width = 0;
    cin >> height >> width;

    string row;
    vec<int> redPos, bluePos;
    for (int y = 0; y < height; y++) {
        cin >> row;
        for (int x = 0; x < width; x++) {
            board[y][x] = row[x];
            if (board[y][x] == RED_MARBLE) {
                redPos = {y, x};
            }  
            else if (board[y][x] == BLUE_MARBLE) {
                bluePos = {y, x};
            }
        }
    }

    cout << bfs(height, width, redPos, bluePos) << "\n";
}