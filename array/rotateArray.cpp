// Problem: https://www.acmicpc.net/problem/17406

#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>

const int MAX_WIDTH= 50, MAX_HEIGHT = 50;
const int MAX_OPERATION = 6;
const int NUM_ARGS = 3;
int grid[MAX_WIDTH+1][MAX_HEIGHT+1];

std::vector<std::vector<int>> operations;

void pull(int fromY, int fromX, int toY, int toX){
    grid[toY][toX] = grid[fromY][fromX];
}

void rotateLayerCW(int upLeftY, int upLeftX, int bottomRightY, int bottomRightX) {
    int tmp = grid[upLeftY][upLeftX];
    int x = upLeftX, y = upLeftY;

    while (y < bottomRightY) {
        pull(y + 1, x, y, x);
        y++;
    }

    while (x < bottomRightX) {
        pull(y, x + 1, y, x);
        x++;
    }

    while (y > upLeftY) {
        pull(y - 1, x, y, x);
        y--;
    }

    while (x > upLeftX + 1) {
        pull(y, x - 1, y, x);
        x--;
    }
    
    grid[y][x] = tmp;
}

void rotateLayerAntiCW(int upLeftY, int upLeftX, int bottomRightY, int bottomRightX) {
    int tmp = grid[upLeftY][upLeftX];
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
    grid[y][x] = tmp;
}


void rotateArray(int r, int c, int s) {
    for (int i = s; i > 0; i--) {
        rotateLayerCW(r-i, c-i, r+i, c+i);
    }
}

void undoRotation(int r, int c, int s) {
    for (int i = s; i > 0; i--) {
        rotateLayerAntiCW(r-i, c-i, r+i, c+i);
    }
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

void printGrid(int height, int width) {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int height = 0, width = 0, numOp = 0;
    std::cin >> height >> width >> numOp;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            std::cin >> ::grid[i][j];
        }
    }
    for (int i = 0; i < numOp; i++) {
        std::vector<int> operation;
        for (int j = 0; j < NUM_ARGS; j++){
            int input = 0;
            std::cin >> input;
            operation.push_back(input);
        }
        ::operations.push_back(operation);
    }

    std::sort(operations.begin(), operations.end());
    int minArrayVal = INT_MAX;

    do {
        for (auto operation: operations) {
            int r = operation[0];
            int c = operation[1];
            int s = operation[2];
            rotateArray(r, c, s);
            // std::cout << "rotate: (" << r << ", "<< c << ", " << s << ")\n";
            // printGrid(height, width);
        }

        int localMin = getArrayVal(height, width);
        // std::cout << "local min: " << localMin << "\n";
        minArrayVal = std::min(minArrayVal, localMin);
        // std::cout << "updated min: " << minArrayVal << "\n";
        
        for (auto rIt =  operations.rbegin(); rIt != operations.rend(); ++rIt) {
            int r = (*rIt)[0];
            int c = (*rIt)[1];
            int s = (*rIt)[2];
            // std::cout << "undo rotation: (" << r << ", "<< c << ", " << s << ")\n";
            undoRotation(r, c, s);
            // printGrid(height, width);
        }
    } while (std::next_permutation(operations.begin(), operations.end()));

    std::cout << minArrayVal << "\n";
    
    return 0;
}
