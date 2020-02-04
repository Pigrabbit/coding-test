#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int NUM_DIRECTION = 4;
// const int MAX_WIDTH = 25, MAX_HEIGHT = 25;
vector<vector<int>> map;
vector<vector<bool>> visited;
vector<int> complexes;
// left, right, up, down
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

vector<vector<bool>> numberingDFS(vector<vector<int>> const &map, int curX, int curY, vector<vector<bool>> &visited) {

    return visited;
}

bool isHouse(vector<vector<int>> const &map, int posX, int posY) {
    return map[posY][posX];
}

bool hasNeighbor(vector<vector<int>> const &map, int posX, int posY, int N) {
    for (int i = 0; i < NUM_DIRECTION; i++) {
        int curX = posX + dx[i];
        int curY = posY + dy[i];
        if (curX >= 0 && curX < N && curY >=0 && curY < N) {
            if (isHouse(map, curX, curY)) {
                return true;
            }
        }
    }

    return false;
}

TEST_CASE("isHouse") {
    vector<vector<int>> map;
    int N = 7;
    map.reserve(N);
    map = {
        {0, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 0}
    };
    int curX = 1, curY = 1;
    REQUIRE(isHouse(map, curX, curY) == true);
    REQUIRE(isHouse(map, 4, 3) == true);
}

TEST_CASE("hasNeighbor") {
    vector<vector<int>> map;
    int N = 7;
    map.reserve(N);
    map = {
        {0, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 0}
    };
    int curX = 1, curY = 1;
    REQUIRE(hasNeighbor(map, curX, curY, N) == true);
    REQUIRE(hasNeighbor(map, 3, 3, N) == true);
    REQUIRE(hasNeighbor(map, 6, 6, N) == false);
}

// TEST_CASE("numberingDFS") {
//     SECTION("example 1") {
//         vector<vector<int>> map;
//         int N = 7;
//         map.reserve(N);
//         map = {
//             {0, 1, 1, 0, 1, 0, 0},
//             {0, 1, 1, 0, 1, 0, 1},
//             {1, 1, 1, 0, 1, 0, 1},
//             {0, 0, 0, 0, 1, 1, 1},
//             {0, 1, 0, 0, 0, 0, 0},
//             {0, 1, 1, 1, 1, 1, 0},
//             {0, 1, 1, 1, 0, 0, 0}
//         };
//         REQUIRE(*map[0] == 0);
//     }
// }
