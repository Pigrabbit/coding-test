// Problem: https://www.acmicpc.net/problem/17070

#include <iostream>
#include <vector>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int MAX_SIZE = 16;

const int HORIZONTAL = 0;
const int DIAGONAL = 1;
const int VERTICAL = 2;

int home[MAX_SIZE + 1][MAX_SIZE + 1];
int cache[MAX_SIZE + 1][MAX_SIZE + 1][3];
// [status][dir]
// status: horizontal, diagonal, vertical
// dir: right, diagnoal, down
int dx[3][3] = {
    {1, 1, -1},
    {1, 1, 0},
    {-1, 1, 0}
};

int dy[3][3] = {
    {0, 1, -1},
    {0, 1, 1},
    {-1, 1, 1}
};


// recursive하게 풀자
// (n, n) 까지 가는 방법의 수
// = (n, n-1) 에 [가로]인 상태로 놓여져있고, [가로]로 다음에 민다.
// + (n-1, n) 에 [세로]인 상태로 놓여져있고, [세로]로 다음에 민다.
// + (n-1, n-1) 에 [가로, 세로, 또는 대각선]인 상태로 놓여져있고, [대각선]으로 다음에 민다.
// 각 이동하는데 빈 칸이 충분히 있는지 확인해야 한다.
bool isInRange(int y, int x, int size) {
    return (x >= 1) && (x <= size) && (y >= 1) && (y <= size);
}

bool isValid(int y, int x, int status, int size) {
    bool isValid = false;
    if (status == DIAGONAL) {
        if (home[y][x] == 0 && home[y-1][x] == 0 && home[y][x-1] == 0) {
            isValid = true;
        }
    } else {
        if (home[y][x] == 0) {
            isValid = true;
        }   
    }
    return isValid;
}

int getWays(int y, int x, int status, int size) {
    if (y == size && x == size) {
        return 1;
    }
    int & ret = cache[y][x][status];
    if (ret != -1) {
        return ret;
    }
    ret = 0;
    for (int dir = 0; dir < 3; dir++) {
        if (dx[status][dir] == -1 || dy[status][dir] == -1) {
            continue;
        }
        int newX = x + dx[status][dir], newY = y + dy[status][dir], newStatus = dir;
        if (isInRange(newY, newX, size) && isValid(newY, newX, newStatus, size)) {
            ret += getWays(newY, newX, newStatus, size);
        }
    }

    return ret;
}

TEST_CASE("getWays") {
    SECTION("example 1") {
        std::memset(cache, -1, sizeof(cache));
        int size = 3;
        int homeIn[size+1][size+1] = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };
        for (int y = 0; y <= size; y++) {
            for (int x = 0; x <= size; x++) {
                home[y][x] = homeIn[y][x];
            }
        }
        REQUIRE(getWays(1, 2, HORIZONTAL, size) == 1);
    }
    SECTION("example 2") {
        std::memset(cache, -1, sizeof(cache));
        int size = 4;
        int homeIn[size+1][size+1] = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };
        for (int y = 0; y <= size; y++) {
            for (int x = 0; x <= size; x++) {
                home[y][x] = homeIn[y][x];
            }
        }
        REQUIRE(getWays(1, 2, HORIZONTAL, size) == 3);
    }
    SECTION("example 3") {
        std::memset(cache, -1, sizeof(cache));
        int size = 5;
        int homeIn[size+1][size+1] = {
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
        };
        for (int y = 0; y <= size; y++) {
            for (int x = 0; x <= size; x++) {
                home[y][x] = homeIn[y][x];
            }
        }
        REQUIRE(getWays(1, 2, HORIZONTAL, size) == 0);
    }
    SECTION("example 4") {
        std::memset(cache, -1, sizeof(cache));
        int size = 6;
        int homeIn[size+1][size+1] = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0}
        };
        for (int y = 0; y <= size; y++) {
            for (int x = 0; x <= size; x++) {
                home[y][x] = homeIn[y][x];
            }
        }
        REQUIRE(getWays(1, 2, HORIZONTAL, size) == 13);
    }
}

int main() {
    int size = 0;
    std::cin >> size;
    for (int y = 1; y <= size; y++) {
        for (int x = 1; x <= size; x++) {
            std::cin >> home[y][x];
        }
    }
    std::memset(cache, -1, sizeof(cache));

    std::cout << getWays(1, 2, HORIZONTAL, size) << "\n";
    
    return 0;
}
