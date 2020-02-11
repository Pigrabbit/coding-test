// Problem: https://www.acmicpc.net/problem/14502

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
// #define CATCH_CONFIG_MAIN
// #include "../lib/catch.hpp"

using namespace std;

const int NUM_DIRECTION = 4;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};


vector<vector<pair<int, int>>> getCombination(int** map, int n, int m) {
    vector<vector<pair<int, int>>> comb;
    vector<pair<int, int>> zeroCoordinates;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 0) {
                zeroCoordinates.push_back(make_pair(j, i));
            }
        }
    }

    vector<int> indice;
    for (int i = 0; i < 3; i++) {
        indice.push_back(1);
    }
    for (int i = 0; i < zeroCoordinates.size() - 3; i++) {
        indice.push_back(0);
    }

    sort(indice.begin(), indice.end());
    do {
        vector<pair<int, int>> coordinates;
        for (int i = 0; i < indice.size(); i++) {
            if (indice[i] == 1) {
                coordinates.push_back(zeroCoordinates[i]);
            }
        }
        comb.push_back(coordinates);
    } while (next_permutation(indice.begin(), indice.end()));

    return comb;
}

// TEST_CASE("getCombination") {
//     SECTION("example 1") {
//         int n = 4;
//         int m = 6;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 0, 0, 1, 0};
//         int row2[] = {1, 0, 0, 1, 0, 2};
//         int row3[] = {1, 1, 1, 0, 0, 2};
//         int row4[] = {0, 0, 0, 1, 0, 2};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;
//         map[3] = row4;

//         vector<vector<pair<int, int>>> comb = getCombination(map, n, m);
//         // for (auto i: comb) {
//         //     for (auto ii: i) {
//         //         cout << "(" << ii.first << ", " << ii.second << ") ";
//         //     }
//         //     cout << "\n";
//         // }
//         cout << "\n";
//     }
//     SECTION("example 2") {
//         int n = 3;
//         int m = 3;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 2};
//         int row2[] = {0, 1, 1};
//         int row3[] = {1, 0 ,0};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;

//         vector<vector<pair<int, int>>> comb = getCombination(map, n, m);
//         // for (auto i: comb) {
//         //     for (auto ii: i) {
//         //         cout << "(" << ii.first << ", " << ii.second << ") ";
//         //     }
//         //     cout << "\n";
//         // }
//         cout << "\n";
//     }
// }

// Todo 1: diffuseVirus
// Input: N X M grid, not diffused
// Output: N x M grid, diffused
int** diffuseVirus(int** map, int n, int m) {
    int** diffusedMap = new int*[n];
    for (int i = 0; i < n; i++) {
        diffusedMap[i] = new int[m];
        for (int j = 0; j < m; j++) {
            diffusedMap[i][j] = map[i][j];
        }
    }

    bool** visited = new bool*[n];
    for (int i = 0; i < n; i++) {
        visited[i] = new bool[m];
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    // store (x, y) pos
    queue <pair<int, int>> bfsQueue;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 2) {
                // virus detected
                // cout << "virus detected at (" << j << ", " << i << ")\n";
                visited[i][j] = true;
                bfsQueue.push(make_pair(j, i));

                while (bfsQueue.size() > 0) {
                    int curX = bfsQueue.front().first, curY =bfsQueue.front().second;
                    // cout << "\tlooking at (" << curX << ", " << curY << ")\n";
                    visited[curY][curX] = true;
                    bfsQueue.pop();
                    for (int k = 0; k < NUM_DIRECTION; k++) {
                        int neighborX = curX + dx[k];
                        int neighborY = curY + dy[k];
                        if (neighborX >=0 && neighborX < m && neighborY >= 0 && neighborY < n) {
                            if (!visited[neighborY][neighborX]) {
                                if (map[neighborY][neighborX] == 0) {
                                    // cout << "\t\tVirus: Time to diffuse!\n";
                                    diffusedMap[neighborY][neighborX] = 2;
                                    bfsQueue.push(make_pair(neighborX, neighborY));
                                } else if (map[neighborY][neighborX] == 2){
                                    // cout << "\t\tvirus detected at (" << neighborX << ", " << neighborY << ")\n";
                                    bfsQueue.push(make_pair(neighborX, neighborY));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return diffusedMap;
}

// TEST_CASE("diffuseVirus") {
//     SECTION("example 1") {
//         int n = 3;
//         int m = 3;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 2};
//         int row2[] = {0, 1, 1};
//         int row3[] = {1, 0 ,0};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;

//         int** diffusedMap = diffuseVirus(map, n, m);
//         // for (int i = 0; i < n; i++) {
//         //     for (int j = 0; j < m; j++) {
//         //         cout << diffusedMap[i][j]  << " "; 
//         //     }
//         //     cout << "\n";
//         // }
//         REQUIRE(diffusedMap[0][0] == 2);
//         REQUIRE(diffusedMap[0][1] == 2);
//         REQUIRE(diffusedMap[1][0] == 2);
//     }
//     SECTION("example 2") {
//         int n = 4;
//         int m = 6;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 0, 0, 1, 0};
//         int row2[] = {1, 0, 0, 1, 0, 2};
//         int row3[] = {1, 1, 1, 0, 0, 2};
//         int row4[] = {0, 0, 0, 1, 0, 2};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;
//         map[3] = row4;

//         int** diffusedMap = diffuseVirus(map, n, m);
//         // for (int i = 0; i < n; i++) {
//         //     for (int j = 0; j < m; j++) {
//         //         cout << diffusedMap[i][j]  << " "; 
//         //     }
//         //     cout << "\n";
//         // }
//         REQUIRE(diffusedMap[0][5] == 2);
//         REQUIRE(diffusedMap[1][4] == 2);
//         REQUIRE(diffusedMap[2][3] == 2);
//         REQUIRE(diffusedMap[2][4] == 2);
//         REQUIRE(diffusedMap[3][4] == 2);
//     }
// }

// Todo 2: buildWall
// Input: N x M grid, 3 pos (y, x) to build wall
// Output: N x M grid, wall built

int** buildWall(int** map, vector<pair<int, int>> coordinate, int n, int m) {
    int** wallBuiltdMap = new int*[n];
    for (int i = 0; i < n; i++) {
        wallBuiltdMap[i] = new int[m];
        for (int j = 0; j < m; j++) {
            wallBuiltdMap[i][j] = map[i][j];
        }
    }

    vector<pair<int, int>>::iterator it;
    for (it = coordinate.begin(); it != coordinate.end(); ++it) {
        int curX = (*it).first, curY = (*it).second;
        wallBuiltdMap[curY][curX] = 1;
    }

    return wallBuiltdMap;
}

// TEST_CASE("buildWall") {
//     SECTION("example 1") {
//         int n = 4;
//         int m = 6;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 0, 0, 1, 0};
//         int row2[] = {1, 0, 0, 1, 0, 2};
//         int row3[] = {1, 1, 1, 0, 0, 2};
//         int row4[] = {0, 0, 0, 1, 0, 2};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;
//         map[3] = row4;

//         vector<pair<int, int>> coordinates = {make_pair(4, 0), make_pair(3, 1), make_pair(3, 3)};

//         int** wallBuiltMap = buildWall(map, coordinates, n, m);

//         // for (int i = 0; i < n; i++) {
//         //     for (int j = 0; j < m; j++) {
//         //         cout << wallBuiltMap[i][j]  << " "; 
//         //     }
//         //     cout << "\n";
//         // }
//         cout << "\n";
//         REQUIRE(wallBuiltMap[0][4] == 1);
//         REQUIRE(wallBuiltMap[1][3] == 1);
//         REQUIRE(wallBuiltMap[3][3] == 1);
//     }
// }

// Todo 3: getSafetyArea
// Input: N x M grid
// Output: saftety area

int getSafetyArea(int** map, int n, int m) {
    int safetyArea = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 0) {
                safetyArea++;
            }
        }
    }
    return safetyArea;
}

// TEST_CASE("getSafetyArea") {
//     SECTION("example 1") {
//         int n = 4;
//         int m = 6;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 0, 0, 1, 0};
//         int row2[] = {1, 0, 0, 1, 0, 2};
//         int row3[] = {1, 1, 1, 0, 0, 2};
//         int row4[] = {0, 0, 0, 1, 0, 2};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;
//         map[3] = row4;
        
//         REQUIRE(getSafetyArea(map, n, m) == 14);
//     }
//     SECTION("example 2") {
//         int n = 3;
//         int m = 3;
//         int** map = new int*[n];
//         for (int i = 0; i < n; i++) {
//             map[i] = new int[m];
//         }

//         int row1[] = {0, 0, 2};
//         int row2[] = {0, 1, 1};
//         int row3[] = {1, 0 ,0};

//         map[0] = row1;
//         map[1] = row2;
//         map[2] = row3;

//         vector<vector<pair<int, int>>> comb = getCombination(map, n, m);
        
//         vector<int> safetyAreas;
//         for (auto i: comb) {
//             int** wallBuiltMap = buildWall(map, i, n, m);
//             int** diffusedMap = diffuseVirus(wallBuiltMap, n, m);
//             int safetyArea = getSafetyArea(diffusedMap, n, m);
//             safetyAreas.push_back(safetyArea);
//         }

//         sort(safetyAreas.begin(), safetyAreas.end());
//         cout << safetyAreas.back() << "\n";
//     }
// }

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    int** map = new int*[n];
    for (int i = 0; i < n; i++) {
        map[i] = new int[m];
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    vector<vector<pair<int, int>>> comb = getCombination(map, n, m);
    cout << "number of combinations: " << comb.size() << "\n";
        
    vector<int> safetyAreas;

    for (auto i: comb) {
        int** wallBuiltMap = buildWall(map, i, n, m);
        int** diffusedMap = diffuseVirus(wallBuiltMap, n, m);
        int safetyArea = getSafetyArea(diffusedMap, n, m);
        // cout << "safety area: " << safetyArea << "\n";
        safetyAreas.push_back(safetyArea);
    }

    sort(safetyAreas.begin(), safetyAreas.end());

    cout << safetyAreas.back() << "\n";

    return 0;
}
