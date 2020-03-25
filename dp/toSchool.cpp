// Problem: https://programmers.co.kr/learn/courses/30/lessons/42898

#include <string>
#include <vector>
#include <cstring>

#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_HEIGHT = 100, MAX_WIDTH = 100;
int cache[MAX_HEIGHT + 1][MAX_WIDTH + 1];

int getPath(int x, int y, vector<vector<int>> & puddles) {
    if (x == 0 || y == 0) {
        return 0;
    }
    if (x == 1 && y == 1) {
        return 1;
    }
    
    int & ret = cache[y][x];
    if (ret != -1) {
        return ret;
    }
    ret = getPath(x - 1, y, puddles) + getPath(x, y - 1, puddles);
    return ret % 1000000007;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < puddles.size(); i++) {
        int y = puddles[i][1], x = puddles[i][0]; 
        cache[y][x] = 0;
    }
    answer = getPath(m, n, puddles);

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        int m = 4, n = 3;
        vector<vector<int>> puddles = {{2, 2}};
        REQUIRE(solution(m, n, puddles) == 4);
    }
}
