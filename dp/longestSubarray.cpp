// Problem: https://www.acmicpc.net/problem/11053

#include <iostream>
#include <limits.h>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int getLengthLongest(vector<int> &arr) {
    int tmp = 0;
    int longestLength = INT_MIN;

    vector<int> dp = {0, 1}; // contains the longest length corresponds to length

    if (arr.size() < 2) {
        return dp[arr.size()];
    }

    for (int i = 2; i <= arr.size(); i++) {
        dp.push_back(1);
    }

    for (int i = 2; i <= arr.size(); i++) {
        for (int j = 1; j < i; j++) {
            if (arr[i-1] > arr[j-1]) {
                tmp = dp[j] + 1; // length when append the current element to subArray
                dp[i] = max(tmp, dp[i]); // find whether it tmp is longer than before
            }
            longestLength = max(longestLength, dp[i]);
        }
    }

    return longestLength;
}

TEST_CASE("getLengthLongest") {
    SECTION("example 1") {
        vector<int> arr = {10, 20, 10, 30, 20, 50};
        REQUIRE(getLengthLongest(arr) == 4);
    }

    SECTION("example 2") {
        vector<int> arr = {1, 2, 1, 4, 3, 4};
        REQUIRE(getLengthLongest(arr) == 4);
    }

    SECTION("with no element") {
        vector<int> arr = {};
        REQUIRE(getLengthLongest(arr) == 0);
    }

    SECTION("with single element") {
        vector<int> arr = {2};
        REQUIRE(getLengthLongest(arr) == 1);
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int arrLength = 0;
    cin >> arrLength;

    vector<int> arr;
    arr.reserve(arrLength);

    for (int i = 0; i < arrLength; i++) {
        int num = 0;
        cin >> num;
        arr.push_back(num);
    }

    cout << getLengthLongest(arr) << "\n";

    return 0;
}
