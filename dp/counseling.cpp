// Problem: https://www.acmicpc.net/problem/14501

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_DAYS = 15;

vector<int> timeRequired(MAX_DAYS);
vector<int> price(MAX_DAYS);
vector<int> dp(MAX_DAYS, 0);

// cache[i]: i일까지 일했을 때 올릴 수 있는 최대 수익
int cache[MAX_DAYS];

int getMaxProfit(int days) {
    int maxProfit = -1;
    for (int i = days-1; i >= 0; i--) {
        if (i + timeRequired[i] <= days) {
            // 이 날 상담하면 얻을 수 있는 총 수익
            int tmp = price[i] + cache[i + timeRequired[i]];
            cache[i] = max(cache[i+1], tmp);
        } else {
            cache[i] = max(cache[i], cache[i+1]);
        }
    }
    return cache[0];
}

TEST_CASE("maxProfit") {
    SECTION("example1") {
        memset(cache, 0, sizeof(cache));
        ::timeRequired = {3, 5, 1, 1, 2, 4 ,2};
        ::price = {10, 20, 10, 20, 15, 40, 200};
        int N = 7;
        REQUIRE(getMaxProfit(N) == 45);
    }
    SECTION("example2") {
        memset(cache, 0, sizeof(cache));
        ::timeRequired = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        ::price        = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int N = 10;
        REQUIRE(getMaxProfit(N) == 55);
    }
    SECTION("example3") {
        memset(cache, 0, sizeof(cache));
        ::timeRequired = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        ::price        = {10, 9 ,8, 7, 6, 10, 9, 8, 7, 6};
        int N = 10;
        REQUIRE(getMaxProfit(N) == 20);
    }
    SECTION("example4") {
        memset(cache, 0, sizeof(cache));
        ::timeRequired = {5, 4, 3, 2, 1, 1, 2, 3, 4, 5};
        ::price        = {50, 40, 30, 20, 10, 10, 20, 30, 40, 50};
        int N = 10;
        REQUIRE(getMaxProfit(N) == 90);
    }
}

int main() {
    int N = 0;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int counselTime = 0, counselPrice = 0;
        cin >> counselTime >> counselPrice;
        ::timeRequired[i] = counselTime;
        ::price[i] = counselPrice;
    }
    memset(cache, 0, sizeof(cache));

    cout << getMaxProfit(N) << "\n";

    return 0;
}
