// Problem: https://www.acmicpc.net/problem/16926

#include <iostream>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int MAX_HEIGHT = 300, MAX_WIDTH = 300;

int arr[MAX_HEIGHT+1][MAX_WIDTH+1];

void pull(int fromY, int fromX, int toY, int toX){
    arr[toY][toX] = arr[fromY][fromX];
}

void rotateSingleLayer(int upLeftY, int upLeftX, int bottomRightY, int bottomRightX) {
    int tmp = arr[upLeftY][upLeftX];
    int x = upLeftX, y = upLeftY;

    while (x < bottomRightX) {
        pull(y, x + 1, y, x);
        x++;
    }
    while (y < bottomRightY) {
        pull(y + 1, x, y, x);
        y++;
    }
    while (x > upLeftX) {
        pull(y, x - 1, y, x);
        x--;
    }
    while (y > upLeftY + 1) {
        pull(y - 1, x, y, x);
        y--;
    }
    arr[y][x] = tmp;
}

void rotateArray(int height, int width) {
    int upLeftY = 1, upLeftX = 1;
    int bottomRightY = height, bottomRightX = width;
    
    for (int i = 0; (height - 2*i - 1 > 0) && (width - 2*i -1 > 0); i++) {
        rotateSingleLayer(upLeftY + i, upLeftX + i, bottomRightY - i, bottomRightX - i);
    }
}

int main() {
    int N = 0, M = 0, R = 0;
    std::cin >> N >> M >> R;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            std::cin >> arr[y][x];
        }
    }

    for (int i = 0; i < R; i++) {
        rotateArray(N, M);
    }

    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            std::cout << arr[y][x] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}


TEST_CASE("pull") {
    int N = 4, M = 4;
    int arrIn[N + 1][M + 1] = {
        {0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4},
        {0, 5, 6, 7, 8},
        {0, 9, 8, 7, 6},
        {0, 5, 4, 3, 2}
    };
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            arr[y][x] = arrIn[y][x];
        }
    }

    SECTION("example 1") {
        int startX = 1, startY = 1;
        pull(startY, startX + 1, startY, startX);
        REQUIRE(arr[1][1] == 2);
        
        pull(startY, startX + 2, startY, startX +1);
        REQUIRE(arr[1][2] == 3);

        pull(startY, startX + 3, startY, startX + 2);
        REQUIRE(arr[1][3] == 4);
        
        pull(startY + 1, startX + 3, startY, startX + 3);
        REQUIRE(arr[1][4] == 8);
    }
}

TEST_CASE("rotateSingleLayer") {
    int N = 4, M = 4;
    int arrIn[N + 1][M + 1] = {
        {0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4},
        {0, 5, 6, 7, 8},
        {0, 9, 8, 7, 6},
        {0, 5, 4, 3, 2}
    };
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            arr[y][x] = arrIn[y][x];
        }
    }

    SECTION("example1") {
        int upLeftX = 1, upLeftY = 1, bottomRightX = 4, bottomRightY = 4;
        rotateSingleLayer(upLeftY, upLeftX, bottomRightY, bottomRightX);
        rotateSingleLayer(upLeftY + 1, upLeftX + 1, bottomRightY - 1, bottomRightX - 1);

        int answer[N + 1][M + 1] = {
            {0, 0, 0, 0, 0},
            {0, 2, 3, 4, 8},
            {0, 1, 7, 7, 6},
            {0, 5, 6, 8, 2},
            {0, 9, 5, 4, 3}
        };
        for (int y = 1; y <= N; y++) {
            for (int x = 1; x <= M; x++) {
                // std::cout << "comparing: [" << y << "][" << x << "]\n";
                REQUIRE(arr[y][x] == answer[y][x]);
            }
        }
    }
}

TEST_CASE("rotateArray") {
    int N = 4, M = 4;
    int arrIn[N + 1][M + 1] = {
        {0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4},
        {0, 5, 6, 7, 8},
        {0, 9, 8, 7, 6},
        {0, 5, 4, 3, 2}
    };
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            arr[y][x] = arrIn[y][x];
        }
    }
    SECTION("example1") {
        rotateArray(N, M);

        int answer[N + 1][M + 1] = {
            {0, 0, 0, 0, 0},
            {0, 2, 3, 4, 8},
            {0, 1, 7, 7, 6},
            {0, 5, 6, 8, 2},
            {0, 9, 5, 4, 3}
        };
        for (int y = 1; y <= N; y++) {
            for (int x = 1; x <= M; x++) {
                // std::cout << "comparing: [" << y << "][" << x << "]\n";
                REQUIRE(arr[y][x] == answer[y][x]);
            }
        }
    }
}
