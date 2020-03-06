// Problem: https://www.acmicpc.net/problem/7576

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

const int MAX_SIZE = 1000;
int box[MAX_SIZE][MAX_SIZE];
bool checked[MAX_SIZE][MAX_SIZE];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};


bool isInBoundary(int boundX, int boundY, int x, int y) {
    return (x >= 0) && (x < boundX) && (y >= 0) && (y < boundY);
}

int getMinDate(int width, int height) {
    int day = 0;
    std::queue<std::vector<int>> bfsQueue;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(box[y][x] == 1) {
                std::vector<int> posAndDay = {y, x, day};
                bfsQueue.push(posAndDay);
            }
        }
    }

    while(!bfsQueue.empty()) {
        int y = bfsQueue.front()[0], x = bfsQueue.front()[1];
        int currentDay = bfsQueue.front()[2];
        if (currentDay > day) {
            day = currentDay;
            continue;
        }
        bfsQueue.pop();
        checked[y][x] = true;

        for (int i = 0; i < 4; i++) {
            int newY = y + dy[i];
            int newX = x + dx[i];
            if (isInBoundary(width, height, newX, newY)) {
                if (box[newY][newX] == 0 && !checked[newY][newX]) {
                    box[newY][newX] = 1;
                    std::vector<int> posAndDay = {newY, newX, currentDay + 1};
                    bfsQueue.push(posAndDay);
                }
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(box[y][x] == 0) {
                return -1;
            }
        }
    }
    
    return day;
}

int main() {
    int width = 0, height = 0;
    std::cin >> width >> height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cin >> box[y][x];
        }
    }
    
    memset(checked, false, sizeof(checked));

    std::cout << getMinDate(width, height) << "\n";

    return 0;
}
