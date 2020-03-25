// Problem: https://programmers.co.kr/learn/courses/30/lessons/43105

#include <string>
#include <vector>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_HEIGHT = 500;
int cache[MAX_HEIGHT + 1][MAX_HEIGHT + 1];

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int floors = triangle.size();
    
    memset(cache, 0, sizeof(cache));
    for (int i = 0; i < triangle[floors - 1].size(); i++) {
        cache[floors][i] = triangle[floors - 1][i]; 
    }

    for (int i = floors-1; i > 0; i--) {
        vector<int> numbers = triangle[i-1];
        for (int j = 0; j < numbers.size(); j++) {
            cache[i][j] = max(cache[i+1][j] + numbers[j], cache[i+1][j+1] + numbers[j]);
        }
    }

    answer = cache[1][0];
    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<vector<int>> triangle = {
            {7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5}
        };
        REQUIRE(solution(triangle) == 30);
    }
}
