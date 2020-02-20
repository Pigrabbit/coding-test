// Problem: https://www.notion.so/f419e631988c40e499020c225f76cd7e

#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"


const int MAX_WIDTH= 50, MAX_HEIGHT = 50;
const int MAX_OPERATION = 6;
const int NUM_ARGS = 3;
int grid[MAX_WIDTH+1][MAX_HEIGHT+1];
std::vector<std::vector<int>> operations;

void transpose(int r, int c, int s) {
    for (int y = r-s; y <= r+s ; y++) {
        for (int x = c-s + (y-(r-s)); x <= c+s; x++) {
            if ((y-r) != (x-c)) {
                // swap!
                int rowDist = y - r; // -2
                int colDist = x - c; // -1
                int tmp = ::grid[y][x];    
                ::grid[y][x] = ::grid[r+colDist][c+rowDist];
                ::grid[r+colDist][c+rowDist] = tmp;
            }
        }
    }
}

void reverseRowOrder(int r, int c, int s) {
    for (int y = r-s; y <= r+s; y++) {
        for (int front = c-s, back = c+s; front < back; front++, back--) {
            int tmp = ::grid[y][front];
            ::grid[y][front] = ::grid[y][back];
            ::grid[y][back] = tmp;
        }
    }
}

void rotateArray(int r, int c, int s) {
    transpose(r, c, s);
    reverseRowOrder(r, c, s);
}

void undoRotation(int r, int c, int s) {
    reverseRowOrder(r, c, s);
    transpose(r, c, s);
}

int getArrayVal(int height, int width) {
    int result = INT_MAX;

    for (int i = 1; i <= height; i++) {
        int sum = 0;
        for (int j = 1; j <= width; j++) {
            sum += ::grid[i][j];
        }
        result = std::min(result, sum);
    }

    return result;
}

int main() {
    int height = 0, width = 0, numOp = 0;
    std::cin >> height >> width >> numOp;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            std::cin >> ::grid[i][j];
        }
    }

    // std::vector<int> operationIndex;
    for (int i = 0; i < numOp; i++) {
        // operationIndex.push_back(i);
        std::vector<int> operation;
        for (int j = 0; j < NUM_ARGS; j++){
            int input = 0;
            std::cin >> input;
            operation.push_back(input);
        }
        ::operations.push_back(operation);
    }

    int minArrayVal = INT_MAX;

    do {
        for (auto operation: ::operations) {
            int r = operation[0];
            int c = operation[1];
            int s = operation[2];
            rotateArray(r, c, s);
        }

        int localMin = getArrayVal(height, width);
        std::cout << "local min: " << localMin << "\n";
        minArrayVal = std::min(minArrayVal, localMin);
        std::cout << "updated min: " << minArrayVal << "\n";
        
        for (auto rIt =  operations.rbegin(); rIt != ::operations.rend(); ++rIt) {
            int r = (*rIt)[0];
            int c = (*rIt)[1];
            int s = (*rIt)[2];
            std::cout << "undo rotation: (" << r << ", "<< c << ", " << s << ")\n";
            undoRotation(r, c, s);
        }
    } while (std::next_permutation(operations.begin(), operations.end()));

    std::cout << minArrayVal << "\n";
    
    return 0;
}

TEST_CASE("transpose") {
    int r = 2, c = 2, s = 1;

    SECTION("example 1") {
        int r = 3, c = 4, s = 2;
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 6; j++) {
                ::grid[i][j] = 6 * (i - 1) + j;
            }
        }

        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 6; j++) {
                std::cout << ::grid[i][j] << " ";
            }
            std::cout << "\n";
        }
        
        std::cout << ::grid[r][c] << "\n";
        transpose(r, c, s);
        
        std::cout << "\n";
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 6; j++) {
                std::cout << ::grid[i][j] << " ";
            }
            std::cout << "\n";
        }

        REQUIRE(::grid);
        REQUIRE(::grid[1][2] == 4);
        REQUIRE(::grid[1][3] == 7);
        REQUIRE(::grid[2][1] == 2);
        REQUIRE(::grid[2][3] == 8);
        REQUIRE(::grid[3][1] == 3);
        REQUIRE(::grid[3][2] == 6);
    }
    SECTION("example 2") {
        transpose(r, c, s);

        std::cout << "\n";
        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                std::cout << ::grid[i][j] << " ";
            }
            std::cout << "\n";
        }

        REQUIRE(::grid[1][2] == 2);
        REQUIRE(::grid[1][3] == 3);
        REQUIRE(::grid[2][1] == 4);
        REQUIRE(::grid[2][3] == 6);
        REQUIRE(::grid[3][1] == 7);
        REQUIRE(::grid[3][2] == 8);
    }
}

TEST_CASE("reverseRowOrder") {
    int r = 2, c = 2, s = 1;

    SECTION("example1") {
        transpose(r, c, s);
        reverseRowOrder(r, c, s);
        
        std::cout << "\n";
        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                std::cout << ::grid[i][j] << " ";
            }
            std::cout << "\n";
        }

        REQUIRE(::grid[1][1] == 7);
        REQUIRE(::grid[1][3] == 1);
        REQUIRE(::grid[2][1] == 8);
        REQUIRE(::grid[2][3] == 2);
        REQUIRE(::grid[3][1] == 9);
        REQUIRE(::grid[3][3] == 3);
    }
    SECTION("example 2") {
        reverseRowOrder(r, c, s);
        
        std::cout << "\n";
        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                std::cout << ::grid[i][j] << " ";
            }
            std::cout << "\n";
        }

        REQUIRE(::grid[1][1] == 1);
        REQUIRE(::grid[1][3] == 7);
        REQUIRE(::grid[2][1] == 2);
        REQUIRE(::grid[2][3] == 8);
        REQUIRE(::grid[3][1] == 3);
        REQUIRE(::grid[3][3] == 9);
    }
}

TEST_CASE("getArrayVal") {
    SECTION("example 1") {
        int height = 3, width = 3;
        int val = getArrayVal(height, width);

        REQUIRE(val == 12);
    }
}

