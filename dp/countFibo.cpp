// Problem: https://www.acmicpc.net/problem/1003

#include <iostream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> countFibo(int num) {
    // index 0 : count 0
    // index 1 : count 1
    vector<int> count = {0, 0};
    int memo0 [num + 1];
    int memo1 [num + 1];

    for (int i = 0; i <= num; i++) {
        if (i == 0) {
            // base case
            memo0[i] = 1;
            memo1[i] = 0;
        } else if (i == 1) {
            // base case
            memo0[i] = 0;
            memo1[i] = 1;
        } else {
            memo0[i] = memo0[i-1] + memo0[i-2];
            memo1[i] = memo1[i-1] + memo1[i-2];
        }
    }

    count[0] = memo0[num];
    count[1] = memo1[num];

    return count;
}

TEST_CASE("countFibo") {
    SECTION("count 0s and 1s, when input is 0") {
        int num = 0;
        REQUIRE(countFibo(num)[0] == 1);
        REQUIRE(countFibo(num)[1] == 0);

    }

    SECTION("count 0s and 1s, when input is 0") {
        int num = 1;
        REQUIRE(countFibo(num)[0] == 0);
        REQUIRE(countFibo(num)[1] == 1);
    }

    SECTION("count 0s and 1s, when input is 3") {
        int num = 3;
        REQUIRE(countFibo(num)[0] == 1);
        REQUIRE(countFibo(num)[1] == 2);
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int numTestCase = 0;
    cin >> numTestCase;

    vector<int> testCase;
    testCase.reserve(numTestCase);

    for (int i = 0; i < numTestCase; i++) {
        int num = 0;
        cin >> num;
        testCase.push_back(num);
    }

    for (int i = 0; i < numTestCase; i++) {
        int num = testCase[i];
        vector<int> count = countFibo(num);
        cout << count[0] << " " << count[1] << "\n";
    }

    return 0;
}
