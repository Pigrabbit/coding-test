// Problem: https://programmers.co.kr/learn/courses/30/lessons/43165

#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int dfs(vector<int> & numbers, int idx, int currentSum, int target) {
    if (idx == -1) {
        if (currentSum == target) {
            return 1;
        }
        return 0;
    }
    int currentNum = numbers[idx];
    return dfs(numbers, idx - 1, currentSum + currentNum, target) + dfs(numbers, idx - 1, currentSum - currentNum, target);
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int numbersSize = numbers.size();
    answer = dfs(numbers, numbersSize - 1, 0, target);

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<int> numbers = {1, 1, 1, 1, 1};
        int target = 3;
        REQUIRE(solution(numbers, target) == 5);
    }
}
