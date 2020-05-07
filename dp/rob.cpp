// Problem: https://programmers.co.kr/learn/courses/30/lessons/42897

#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

#include <string>
#include <vector>
#include <cstring>
#include <iostream>

#define v vector

using namespace std;

const int MAX_HOUSE = 1000000;
int cache[MAX_HOUSE + 1];
int numHouse;

int rob(const v<int> &money, int idx) {
    if (idx >= numHouse-1) return 0;
    int &ret = cache[idx];
    if (ret != -1) return ret;

    return ret = max(money[idx] + rob(money, idx+2), rob(money, idx + 1));
}

int solution(vector<int> money) {
    int answer = 0;
    numHouse = money.size();

    memset(cache, -1, sizeof(cache));
    v<int> money1 = v<int>(money.begin(), money.end() - 1);
    int tmp1 = rob(money, 0);

    for (int i = 0; i < numHouse; i++) cache[i] = -1;
    v<int> money2 = v<int>(money.begin()+1, money.end());
    int tmp2 = rob(money, 0);

    return answer = max(tmp1, tmp2);
}

TEST_CASE("solution") {
    SECTION("example1") {
        v<int> money = {1, 2, 3, 1};
        int exp = 4;
        REQUIRE(solution(money) == exp);
    }
}
