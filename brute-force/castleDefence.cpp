// Problem: https://www.acmicpc.net/problem/17135

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

const int EMPTY = 0;
const int ENEMY = 1;
const int ARCHER = 2;
const int DEAD = 3;

const int MAX_HEIGHT = 15, MAX_WIDTH = 15;
int map[MAX_HEIGHT + 2][MAX_WIDTH + 1];
int tmp[MAX_HEIGHT + 2][MAX_WIDTH + 1];

void shoot(int archerX, int range, int height, int width) {
    for (int d = 1; d <= std::min(range, height); d++) {
        int leftLimit = std::max(1, archerX - d + 1), rightLimit = std::min(width, archerX+d-1);
        for (int targetX = leftLimit; targetX <= rightLimit; targetX++) {
            int targetY = height - std::abs(d - std::abs(archerX - targetX)) + 1;
            if (tmp[targetY][targetX] == ENEMY || tmp[targetY][targetX] == DEAD) {
                tmp[targetY][targetX] = DEAD;
                return;
            }
        }
    }
}

int getKilledEnemy(std::vector<int> & archerPos, int numEnemies, int height, int width, int range) {
    int killed = 0, survived = 0, archerSize = archerPos.size();
    
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            tmp[i][j] = map[i][j];
        }
    }
    for (int i = 0; i < archerSize; i++) {
        tmp[height + 1][archerPos[i]] = ARCHER;
    }

    while(killed + survived < numEnemies) {
        // check which enemy that archer could shoot
        for (int x = 1; x <= width; x++) {
            if (tmp[height + 1][x] == ARCHER) {
                shoot(x, range, height, width);
            }
        }
        for (int y = height; y > 0; y--) {
            for (int x = 1; x <= width; x++) {
                if (tmp[y][x] == DEAD) {
                    killed++;
                    tmp[y][x] = EMPTY;
                }
                else if (tmp[y][x] == ENEMY) {
                    if (y == height) {
                        survived++;
                        tmp[y][x] = EMPTY;
                    }
                    else {
                        tmp[y+1][x] = ENEMY;
                        tmp[y][x] = EMPTY;
                    }
                }
            }
        }
    }
    
    return killed;
}

int main() {
    int height = 0, width = 0, range = 0, numEnemy = 0;
    int maxKilled = -1;
    std::cin >> height >> width >> range;

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            std::cin >> map[y][x];
            if (map[y][x] == 1) {
                numEnemy++;
            }  
        }
    }

    std::vector<int> perm(width, 0);
    std::fill(perm.begin() + width - 3, perm.begin() + width, 1);
    int permSize = perm.size();
    
    do {
        std::vector<int> archerPos;
        for (int i = 0; i < permSize; i++) {
            if (perm[i] == 1) {
                archerPos.push_back(i + 1);
            }
        }

        std::memset(tmp, 0, sizeof(tmp));
        int killed = getKilledEnemy(archerPos, numEnemy, height, width, range);
        maxKilled = std::max(maxKilled, killed);
    } while(std::next_permutation(perm.begin(), perm.end()));

    std::cout << maxKilled << "\n";

    return 0;
}
