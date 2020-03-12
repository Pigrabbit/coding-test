// Problem: https://www.acmicpc.net/problem/2206

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX_WIDTH = 1000, MAX_HEIGHT = 1000;

int map[MAX_HEIGHT + 1][MAX_WIDTH + 1];
int shortestDistance[MAX_HEIGHT + 1][MAX_WIDTH + 1][2];
bool visited[MAX_HEIGHT + 1][MAX_WIDTH + 1][2];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};


bool isInRange(int height, int width, int x, int y) {
    return (x >= 1) && (x <= width) && (y >= 1) && (y <= height);
}


int getShortestPath(int height, int width) {
    std::queue<std::vector<int>> bfsQueue;
    int startX = 1, startY = 1, wallBreaker = 1;
    int ret = -1;
    shortestDistance[startY][startX][wallBreaker] = 1;
    visited[startY][startX][wallBreaker] = true;
    std::vector<int> start = {startX, startY, wallBreaker};
    bfsQueue.push(start);

    while(!bfsQueue.empty()) {
        int curX = bfsQueue.front()[0], curY = bfsQueue.front()[1];
        int leftWallBreaker = bfsQueue.front()[2];
        bfsQueue.pop();

        if (curY == height && curX == width) {break;}

        for (int i = 0; i < 4; i++) {
            int newX = curX + dx[i], newY = curY + dy[i];
            if (isInRange(height, width, newX, newY)) {
                if (map[newY][newX] == 0 && !visited[newY][newX][leftWallBreaker]) {
                    // can move
                    visited[newY][newX][leftWallBreaker] = true;
                    shortestDistance[newY][newX][leftWallBreaker] = shortestDistance[curY][curX][leftWallBreaker] + 1;
                    std::vector<int> next = {newX, newY, leftWallBreaker};
                    bfsQueue.push(next);
                } else if (map[newY][newX] == 1 && leftWallBreaker == 1 && !visited[newY][newX][leftWallBreaker - 1]) {
                    // cannot move so break the wall!
                    visited[newY][newX][leftWallBreaker-1] = true;
                    shortestDistance[newY][newX][leftWallBreaker-1] = shortestDistance[curY][curX][leftWallBreaker] + 1;
                    std::vector<int> next = {newX, newY, leftWallBreaker-1};
                    bfsQueue.push(next);
                }
            }
        }
    }

    if (shortestDistance[height][width][0] != 0 && shortestDistance[height][width][1] != 0) {
        return std::min(shortestDistance[height][width][0], shortestDistance[height][width][1]);
    }
    else if (shortestDistance[height][width][0] == 0 && shortestDistance[height][width][1] != 0) {
        return shortestDistance[height][width][1];
    }
    else if (shortestDistance[height][width][0] != 0 && shortestDistance[height][width][1] == 0) {
        return shortestDistance[height][width][0];
    }
    return -1;
}

int main() {
    int height = 0, width = 0;
    std::cin >> height >> width;

    for (int y = 1; y <= height; ++y) {
        for (int x = 1; x <= width; ++x) {
            scanf("%1d", &map[y][x]);
        }
    }

    std::memset(shortestDistance, 0, sizeof(shortestDistance));
    std::memset(visited, false, sizeof(visited));

    std::cout << getShortestPath(height, width) << "\n";

    return 0;
}
