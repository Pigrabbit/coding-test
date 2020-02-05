// Problem: https://www.acmicpc.net/problem/2667

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int NUM_DIRECTION = 4;
const int MAX_WIDTH = 25, MAX_HEIGHT = 25;
const int MAX_COMPLEX = 500;

vector<vector<int>> map(MAX_HEIGHT, vector<int>(MAX_WIDTH, 0));
vector<vector<bool>> visited(MAX_HEIGHT, vector<bool>(MAX_WIDTH, false));
vector<int> complexes(MAX_COMPLEX, 0);

int complexID = 1;
// left, right, up, down
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


bool isHouse(int posX, int posY) {
    return ::map[posY][posX];
}

void dfs(int curX, int curY, int N) {
    visited[curY][curX] = true;
    complexes[complexID] += 1;

    for (int i = 0; i < NUM_DIRECTION; i++) {
        int X = curX + dx[i];
        int Y = curY + dy[i];
        if (X >= 0 && X < N && Y >=0 && Y < N) {
            if (isHouse(X, Y) && !visited[Y][X]) {
                dfs(X, Y, N);
            }
        }
    }
}

void numberingHouse(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isHouse(j, i) && !visited[i][j]) {
                dfs(j, i, N);
                complexID++;
            }
        }    
    }
    ::complexes = {::complexes.begin()+1, ::complexes.begin()+complexID};
    sort(::complexes.begin(), ::complexes.end());
}

TEST_CASE("isHouse") {
    int N = 7;
    ::map = {
        {0, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 0}
    };
    int curX = 1, curY = 1;
    REQUIRE(isHouse(curX, curY) == true);
    REQUIRE(isHouse(4, 3) == true);
}

TEST_CASE("hasNeighbor") {
    int N = 7;
    ::map = {
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

TEST_CASE("numberingDFS") {
    SECTION("example 1") {
        ::map = {
            {0, 1, 1, 0, 1, 0, 0},
            {0, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 1, 1},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 0, 0, 0}
        };
        int N = 7;
        numberingHouse(::map, N);
        
        REQUIRE(::complexes[0] == 7);
        REQUIRE(::complexes[1] == 8);
        REQUIRE(::complexes[2] == 9);
    }
}


int main() {
    int N = 0;
    cin >> N;

    int val;
    char ch;
    string line;
    getline(cin, line);

    for(vector<vector<int>>::iterator it=::map.begin(); it!=::map.begin()+N; ++it) {
        getline(cin, line);
        stringstream ss(line);
        int index = 0;
        while(ss>>ch) {
            val = ch - '0';
            (*it)[index] = val;
            index++;
        }
    }

    numberingHouse(N);

    ::complexID--;
    cout << ::complexID << "\n";

    for (vector<int>::iterator it=::complexes.begin(); it!=::complexes.end(); ++it) {
        cout << (*it) << "\n";
    }

    return 0;
}
