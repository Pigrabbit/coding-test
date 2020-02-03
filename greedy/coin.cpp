// Problem: https://www.acmicpc.net/problem/11047

#include <iostream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int minCoinNeeded(vector<int> &descValues, int target) {
    int numCoin = 0;
    for(auto i: descValues) {
        while(i <= target) {
            target -= i;
            numCoin++;
        }
        if (target == 0) {
            return numCoin;
        }
    }
    return -1;
}

TEST_CASE("minCoinNeeded") {
    SECTION("example1") {
        int target = 4200;
        vector<int> values = {50000, 10000, 5000, 1000, 500, 100, 50, 10, 5, 1};
        REQUIRE(minCoinNeeded(values, target) == 6);
    }
    SECTION("example2") {
        int target = 4790;
        vector<int> values = {50000, 10000, 5000, 1000, 500, 100, 50, 10, 5, 1};
        REQUIRE(minCoinNeeded(values, target) == 12);
    }
}

int main() {
    int numValues = 0, target = 0;
    int value = 0;
    vector<int> descValue;

    cin >> numValues >> target;

    for (int i = 0; i < numValues; i++) {
        cin >> value;
        descValue.insert(descValue.begin(), value);
    }

    cout << minCoinNeeded(descValue, target) << "\n";

    return 0;
}
