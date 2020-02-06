// Problem: https://www.acmicpc.net/problem/14501

#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_DAYS = 15;

vector<int> timeRequired(MAX_DAYS);
vector<int> price(MAX_DAYS);
vector<int> dp(MAX_DAYS, 0);

int maxProfit(int N) {
    int maxProfit = INT_MIN;
    int day = N;
    for(vector<int>::iterator it=:: timeRequired.begin()+N-1; it >= ::timeRequired.begin(); --it) {
        int counselTime = *it;
        if (day + counselTime - 1 <= N) {
            ::dp[day-1] = max(::price[day-1] + ::dp[day+counselTime-1], ::dp[day]);
        } else {
            ::dp[day-1] = max(::dp[day-1], ::dp[day]);
        }
        day--;
    }
    maxProfit = ::dp.front();
    return maxProfit;
}

TEST_CASE("maxProfit") {
    SECTION("example1") {
        ::timeRequired = {3, 5, 1, 1, 2, 4 ,2};
        ::price = {10, 20, 10, 20, 15, 40, 200};
        int N = 7;
        REQUIRE(maxProfit(N) == 45);
        ::dp.assign(MAX_DAYS, 0);
    }
    SECTION("example2") {
        ::timeRequired = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        ::price        = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int N = 10;
        REQUIRE(maxProfit(N) == 55);
        ::dp.assign(MAX_DAYS, 0);
    }
    SECTION("example3") {
        ::timeRequired = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        ::price        = {10, 9 ,8, 7, 6, 10, 9, 8, 7, 6};
        int N = 10;
        REQUIRE(maxProfit(N) == 20);
        ::dp.assign(MAX_DAYS, 0);
    }
    SECTION("example4") {
        ::timeRequired = {5, 4, 3, 2, 1, 1, 2, 3, 4, 5};
        ::price        = {50, 40, 30, 20, 10, 10, 20, 30, 40, 50};
        int N = 10;
        REQUIRE(maxProfit(N) == 90);
        ::dp.assign(MAX_DAYS, 0);
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

    cout << maxProfit(N) << "\n";

    return 0;
}
