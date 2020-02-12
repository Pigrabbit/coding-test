// Problem: https://www.acmicpc.net/problem/14502

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"
#define SPACE    0
#define WALL     1
#define VIRUS    2
#define INFECTED 3

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

// Todo 1: diffuseVirus
// Input: N X M grid, not diffused
// Output: N x M grid, diffused
void diffuseVirus(int** map, int n, int m) {
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
            if (map[i][j] == VIRUS || map[i][j] == INFECTED) {
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
                                if (map[neighborY][neighborX] == SPACE) {
                                    // cout << "\t\tVirus: Time to diffuse!\n";
                                    map[neighborY][neighborX] = INFECTED;
                                    bfsQueue.push(make_pair(neighborX, neighborY));
                                } else if (map[neighborY][neighborX] == VIRUS || map[neighborY][neighborX] == INFECTED){
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

    for (int i = 0; i < n; i++) {
        delete [] visited[i];
    }
}

void revertDiffusion(int** map, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == INFECTED) {
                map[i][j] = SPACE;
            }
        }
    }
}

// Todo 2: buildWall
// Input: N x M grid, 3 pos (y, x) to build wall
// Output: N x M grid, wall built

void buildWall(int** map, vector<pair<int, int>> coordinate) {
    vector<pair<int, int>>::iterator it;

    for (it = coordinate.begin(); it != coordinate.end(); ++it) {
        int curX = (*it).first, curY = (*it).second;
        map[curY][curX] = 1;
    }
}

void destroyWall(int** map, vector<pair<int, int>> coordinate) {
    vector<pair<int, int>>::iterator it;
    for (it = coordinate.begin(); it != coordinate.end(); ++it) {
        int curX = (*it).first, curY = (*it).second;
        map[curY][curX] = 0;
    }
}

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


TEST_CASE("buildWall") {
    SECTION("example 1") {
        int n = 4;
        int m = 6;
        int** map = new int*[n];
        for (int i = 0; i < n; i++) {
            map[i] = new int[m];
        }

        int row1[] = {0, 0, 0, 0, 0, 0};
        int row2[] = {1, 0, 0, 0, 0, 2};
        int row3[] = {1, 1, 1, 0, 0, 2};
        int row4[] = {0, 0, 0, 0, 0, 2};

        map[0] = row1;
        map[1] = row2;
        map[2] = row3;
        map[3] = row4;

        vector<pair<int, int>> coordinates = {make_pair(4, 0), make_pair(3, 1), make_pair(3, 3)};
        
        buildWall(map, coordinates);

        REQUIRE(map[0][4] == 1);
        REQUIRE(map[1][3] == 1);
        REQUIRE(map[3][3] == 1);
    }
}

TEST_CASE("destroyWall") {
    SECTION("example 1") {
        int n = 4;
        int m = 6;
        int** map = new int*[n];
        for (int i = 0; i < n; i++) {
            map[i] = new int[m];
        }

        int row1[] = {0, 0, 0, 0, 0, 0};
        int row2[] = {1, 0, 0, 0, 0, 2};
        int row3[] = {1, 1, 1, 0, 0, 2};
        int row4[] = {0, 0, 0, 0, 0, 2};

        map[0] = row1;
        map[1] = row2;
        map[2] = row3;
        map[3] = row4;

        vector<pair<int, int>> coordinates = {make_pair(4, 0), make_pair(3, 1), make_pair(3, 3)};

        buildWall(map, coordinates);
        destroyWall(map, coordinates);

        REQUIRE(map[0][4] == 0);
    }
}

TEST_CASE("diffuseVirus") {
    SECTION("example 1") {
        int n = 3;
        int m = 3;
        int** map = new int*[n];
        for (int i = 0; i < n; i++) {
            map[i] = new int[m];
        }

        int row1[] = {0, 0, 2};
        int row2[] = {0, 1, 1};
        int row3[] = {1, 0 ,0};

        map[0] = row1;
        map[1] = row2;
        map[2] = row3;

        diffuseVirus(map, n, m);
        
        REQUIRE(map[0][0] == 3);
        REQUIRE(map[0][1] == 3);
        REQUIRE(map[0][2] == 2);
        REQUIRE(map[1][0] == 3);
    }
    SECTION("example 2") {
        int n = 4;
        int m = 6;
        int** map = new int*[n];
        for (int i = 0; i < n; i++) {
            map[i] = new int[m];
        }

        int row1[] = {0, 0, 0, 0, 1, 0};
        int row2[] = {1, 0, 0, 1, 0, 2};
        int row3[] = {1, 1, 1, 0, 0, 2};
        int row4[] = {0, 0, 0, 1, 0, 2};

        map[0] = row1;
        map[1] = row2;
        map[2] = row3;
        map[3] = row4;

        diffuseVirus(map, n, m);
        
        REQUIRE(map[0][5] == 3);
        REQUIRE(map[1][4] == 3);
        REQUIRE(map[2][3] == 3);
        REQUIRE(map[2][4] == 3);
        REQUIRE(map[3][4] == 3);
        REQUIRE(map[3][5] == 2);
    }
}

TEST_CASE("revertDiffusion") {
    SECTION("example 1") {
        int n = 4;
        int m = 6;
        int** map = new int*[n];
        for (int i = 0; i < n; i++) {
            map[i] = new int[m];
        }

        int row1[] = {0, 0, 0, 0, 1, 0};
        int row2[] = {1, 0, 0, 1, 0, 2};
        int row3[] = {1, 1, 1, 0, 0, 2};
        int row4[] = {0, 0, 0, 1, 0, 2};

        map[0] = row1;
        map[1] = row2;
        map[2] = row3;
        map[3] = row4;

        diffuseVirus(map, n, m);
        revertDiffusion(map, n , m);

        REQUIRE(map[0][5] == 0);
        REQUIRE(map[1][4] == 0);
        REQUIRE(map[2][3] == 0);
        REQUIRE(map[2][4] == 0);
        REQUIRE(map[3][4] == 0);
        REQUIRE(map[3][5] == 2);
    }
}

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
    vector<int> safetyAreas;

    for (auto coordinates: comb) {
        buildWall(map, coordinates);
        diffuseVirus(map, n, m);
        int safetyArea = getSafetyArea(map, n, m);
        safetyAreas.push_back(safetyArea);

        revertDiffusion(map, n, m);
        destroyWall(map, coordinates);
    }

    sort(safetyAreas.begin(), safetyAreas.end());

    cout << safetyAreas.back() << "\n";

    return 0;
}
