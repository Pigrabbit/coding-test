// Problem: https://programmers.co.kr/learn/courses/30/lessons/60059

#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<vector<int>> rotateCW90(vector<vector<int>> & key, int m) {
    // transpose
    // vector<vector<int>> rotatedKey(m, vector<int> (m));
    vector<vector<int>> rotatedKey = key;
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < m; x++) {
            if (y != x) {
                rotatedKey[y][x] = key[x][y];
            }
        }
    }
    // reverse by row
    for (int y = 0; y < m; y++) {
        for (int front = 0, back = m - 1; front < back; front++, back--) {
            int tmp = rotatedKey[y][back];
            rotatedKey[y][back] = rotatedKey[y][front];
            rotatedKey[y][front] = tmp;
        }
    }
    return rotatedKey;
}

TEST_CASE("rotateCW90") {
    SECTION("example") {
        vector<vector<int>> key = {
            {0, 0, 0},
            {1, 0 ,0},
            {0, 1, 0}
        };
        vector<vector<int>> rotated = rotateCW90(key, 3);
        cout << "\nrotated key\n";
        for(auto row: rotated) {
            for (auto el: row) {
                cout << el << " ";
            }
            cout << "\n";
        }
        REQUIRE(rotated[0][1] == 1);
    }
    SECTION("example 2") {
        vector<vector<int>> key = {
            {1, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        };
        vector<vector<int>> rotated = rotateCW90(key, 5);
        vector<vector<int>> rotated2 = rotateCW90(rotated, 5);
        vector<vector<int>> rotated3 = rotateCW90(rotated2, 5);
        cout << "\nrotated key\n";
        for(auto row: rotated3) {
            for (auto el: row) {
                cout << el << " ";
            }
            cout << "\n";
        }
        REQUIRE(rotated3[0][0] == 0);
    }
}

vector<vector<int>> expandLock(vector<vector<int>> & lock, int m, int n) {
    int expandedLen = 2 * (m - 1) + n;
    vector<vector<int>> expanded(expandedLen, (vector<int> (expandedLen, 0)));

    for (int y = 0; y < expandedLen; y++) {
        for (int x = 0; x < expandedLen; x++) {
            if (x >= m - 1 && x < m + n - 1 && y >= m - 1 && y < m + n -1) {
                expanded[y][x] = lock[y - m + 1][x - m + 1];
            }
        }
    }
    return expanded;
}

TEST_CASE("expanded") {
    SECTION("example 1") {
        vector<vector<int>> lock = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        int m = 3, n =3;
        vector<vector<int>> exp = expandLock(lock, m , n);
        cout << "\nexpanded lock\n";
        for(auto row: exp) {
            for (auto el: row) {
                cout << el << " ";
            }
            cout << "\n";
        }
        REQUIRE(exp[0][0] == 0);
    }
}

bool check(int y, int x, vector<vector<int>> & key, vector<vector<int>> & expandedLock, int m, int n) {
    vector<vector<int>> tmpLock = expandedLock;
    bool canOpen = true;
    for (int i = y; i < y + m; i++) {
        for (int j = x; j < x + m; j++) {
            tmpLock[i][j] += key[i - y][j - x];
        }
    }

    for (int y = m - 1; y < m + n - 1; y++) {
        for (int x = m - 1; x < m + n -1; x++) {
            if (tmpLock[y][x] != 1) {
                return false;
            }
        }
    }
    return canOpen;
}

TEST_CASE("check") {
    SECTION("example 1") {
        vector<vector<int>> lock = {
            {1, 1, 0},
            {1, 1, 0},
            {1, 1, 1}
        };
        vector<vector<int>> key = {
            {0, 0, 0},
            {1, 0, 0},
            {1, 0, 0}
        };
        int m = 3, n = 3, x = 4, y = 1;
        vector<vector<int>> exp = expandLock(lock, m, n);
        REQUIRE(check(y, x, key, exp, m, n) == true);
    }
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    int keySize = key.size(), lockSize = lock.size();

    vector<vector<int>> expandedLock = expandLock(lock, keySize, lockSize);
    int len = expandedLock.size();
    bool canOpen = false;
    int numRotation = 4;
    
    while(numRotation) {
        for (int y = 0; y + keySize <= len; y++) {
            for (int x = 0; x + keySize <= len; x++) {
                canOpen = check(y, x, key, expandedLock, keySize, lockSize);
                if (canOpen) {
                    return answer = canOpen;
                }
            }
        }
        key = rotateCW90(key, keySize);
        numRotation--;
    }

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<vector<int>> lock = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };
        vector<vector<int>> key = {
            {0, 0, 0},
            {1, 0, 0},
            {0, 1, 1}
        };
        REQUIRE(solution(key, lock) == true);
    }
    SECTION("example 2") {
        vector<vector<int>> lock = {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
        };
        vector<vector<int>> key = {
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1}
        };
        REQUIRE(solution(key, lock) == true);
    }
    SECTION("example 3") {
        vector<vector<int>> lock = {
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1},
        };
        vector<vector<int>> key = {
            {1, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        };
        REQUIRE(solution(key, lock) == true);
    }
    SECTION("example 4") {
        vector<vector<int>> lock = {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
        };
        vector<vector<int>> key = {
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };
        REQUIRE(solution(key, lock) == true);
    }
    SECTION("example 5") {
        vector<vector<int>> lock = {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0},
        };
        vector<vector<int>> key = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 1}
        };
        REQUIRE(solution(key, lock) == true);
    }
}

