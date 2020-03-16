// Problem: https://www.acmicpc.net/problem/14502

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int SPACE    = 0;
const int WALL     = 1;
const int VIRUS    = 2;
const int INFECTED = 3;

const int MAX_HEIGHT = 8, MAX_WIDTH = 8;
int map[MAX_HEIGHT + 1][MAX_WIDTH + 1];
int visited[MAX_HEIGHT + 1][MAX_WIDTH + 1];
int maxSafetyArea = -1;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool isInRange(int y, int x, int height, int width) {
    return (y >= 1) && (y <= height) && (x >= 1) && (x <= width);
}

int getSafetyArea(int height, int width) {
    int safetyArea = 0;
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (map[y][x] == SPACE) {
                safetyArea++;
            }
        }
    }

    return safetyArea;
}

int spreadVirusBFS(int height, int width) {
    std::queue<std::vector<int>> bfsQueue;
    bool discovered[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    std::memset(discovered, false, sizeof(discovered));

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (map[y][x] == VIRUS) {
                std::vector<int> virusPos = {x, y};
                discovered[y][x] = true;
                bfsQueue.push(virusPos);
            }
        }
    }
    
    while (!bfsQueue.empty()) {
        int curX = bfsQueue.front()[0], curY = bfsQueue.front()[1];
        bfsQueue.pop();

        for (int dir = 0; dir < 4; dir++) {
            int newX = curX + dx[dir], newY = curY + dy[dir];

            if (isInRange(newY, newX, height, width)) {
                if (!discovered[newY][newX] && map[newY][newX] == SPACE) {
                    // INFECTION case
                    discovered[newY][newX] = true;
                    map[newY][newX] = INFECTED;
                    std::vector<int> infectedPos = {newX, newY};
                    bfsQueue.push(infectedPos);
                }
            }
        }
    }

    int safetyArea = getSafetyArea(height, width);

    // roll back
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (map[y][x] == INFECTED) {
                map[y][x] = SPACE;
            }
        }
    }
    return safetyArea;
}

void dfs(int wallLeft, int height, int width) {
    if (wallLeft == 0) {
        int safetyArea = spreadVirusBFS(height, width);
        maxSafetyArea = std::max(safetyArea, maxSafetyArea);
        return;
    }

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (!visited[y][x] && map[y][x] == SPACE) {
                visited[y][x] = true;
                map[y][x] = WALL;

                dfs(wallLeft - 1, height, width);

                visited[y][x] = false;
                map[y][x] = SPACE;
            }   
        }
    }
    
}

int main() {
    int height = 0, width = 0;
    std::cin >> height >> width;
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            std::cin >> map[y][x];
        }
    }

    int wallLeft = 3;
    dfs(wallLeft, height, width);
    std::cout << maxSafetyArea << "\n";

    return 0;
}

TEST_CASE("spreadVirusBFS") {
    int height = 7, width = 7;
    int mapIn[height + 1][width + 1] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 2, 0},
        {0, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0}
    };
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            map[y][x] = mapIn[y][x];
        }
    }
    SECTION("example 1") {
        int safetyArea = spreadVirusBFS(height, width);
        REQUIRE(safetyArea == 27);
    }
}

TEST_CASE("dfs") {
    SECTION("example 1") {
        int height = 7, width = 7;
        int mapIn[height + 1][width + 1] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 1, 2, 0},
            {0, 0, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0}
        };
        std::memset(map, -1, sizeof(map));
        std::memset(visited, false, sizeof(visited));
        for (int y = 1; y <= height; y++) {
            for (int x = 1; x <= width; x++) {
                map[y][x] = mapIn[y][x];
            }
        }
        int leftWall = 3;
        dfs(leftWall, height, width);
        REQUIRE(maxSafetyArea == 27);
    }
    SECTION("example 2") {
        int height = 4, width = 6;
        maxSafetyArea = -1;
        int mapIn[height + 1][width + 1] = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 2},
            {0, 1, 1, 1, 0, 0, 2},
            {0, 0, 0, 0, 0, 0, 2}
        };
        std::memset(map, -1, sizeof(map));
        std::memset(visited, false, sizeof(visited));
        for (int y = 1; y <= height; y++) {
            for (int x = 1; x <= width; x++) {
                map[y][x] = mapIn[y][x];
            }
        }
        int leftWall = 3;
        dfs(leftWall, height, width);
        REQUIRE(maxSafetyArea == 9);
    }
}

