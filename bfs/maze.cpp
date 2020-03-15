// Problem: https://www.acmicpc.net/problem/2178

#include <iostream>
#include <vector>
#include <queue>

const int MAX_HEIGHT = 100, MAX_WIDTH = 100;
const int PATH = 1;
const int WALL = 0;

int maze[MAX_HEIGHT + 1][MAX_WIDTH + 1];

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};

bool isInRange(int y, int x, int height, int width) {
    return (x >= 1) && (x <= width) && (y >= 1) && (y <= height);
}
    
int bfs(int height, int width) {
    bool discovered[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    int distance[MAX_HEIGHT + 1][MAX_WIDTH + 1];

    std::queue<std::vector<int>> bfsQueue;
    int startX = 1, startY = 1;
    std::vector<int> startPos = {startX, startY};
    discovered[startY][startX] = true;
    distance[startY][startX] = 1;

    bfsQueue.push(startPos);
    while(!bfsQueue.empty()) {
        int curX = bfsQueue.front()[0], curY = bfsQueue.front()[1];
        bfsQueue.pop();

        for(int dir = 0; dir < 4; dir++) {
            int newX = curX + dx[dir], newY = curY + dy[dir];
            if (isInRange(newY, newX, height, width)) {
                if (!discovered[newY][newX] && maze[newY][newX] == PATH) {
                    discovered[newY][newX] = true;
                    distance[newY][newX] = distance[curY][curX] + 1;
                    std::vector<int> newPos = {newX, newY};
                    bfsQueue.push(newPos);
                }
            }
        }
    }

    return distance[height][width];
}

int main() {
    int height = 0, width = 0;
    std::cin >> height >> width;

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            scanf("%1d", &maze[y][x]);
        }
    }

    std::cout << bfs(height, width) << "\n";

    return 0;
}
