// Problem: https://www.acmicpc.net/problem/14888

#include <iostream>
#include <vector>
#include <limits.h>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

long long max = LLONG_MIN;
long long min = LLONG_MAX;

void getMinMax(vector<int> &numbers, int index, long long current, 
    int plus, int minus, int mul, int div) {
    if (index == numbers.size()) {
        if (current > ::max) { ::max = current; }
        if (current < ::min) { ::min = current; }
        return;
    }
    // dfs
    if (plus > 0)  { getMinMax(numbers, index + 1, current + numbers[index], plus - 1, minus, mul, div); }
    if (minus > 0) { getMinMax(numbers, index + 1, current - numbers[index], plus, minus - 1, mul, div); }
    if (mul > 0)   { getMinMax(numbers, index + 1, current * numbers[index], plus, minus, mul - 1, div); }
    if (div > 0)   { getMinMax(numbers, index + 1, current / numbers[index], plus, minus, mul, div - 1); }
}


TEST_CASE("getMinMax") {
    SECTION("example 1") {
        vector<int> numbers = {5, 6};
        int plus = 0;
        int minus = 0;
        int mul = 1;
        int div = 0;
        getMinMax(numbers, 1, numbers[0], plus, minus, mul, div);
        REQUIRE(::min == 30);
        REQUIRE(::max == 30);
    }

    SECTION("example 2") {
        vector<int> numbers = {3, 4, 5};
        int plus = 1;
        int minus = 0;
        int mul = 1;
        int div = 0;
        getMinMax(numbers, 1, numbers[0], plus, minus, mul, div);
        REQUIRE(::min == 17);
        REQUIRE(::max == 35);
    }

    SECTION("example 3") {
        vector<int> numbers = {1, 2, 3, 4, 5, 6};
        int plus = 2;
        int minus = 1;
        int mul = 1;
        int div = 1;
        getMinMax(numbers, 1, numbers[0], plus, minus, mul, div);
        REQUIRE(::min == -24);
        REQUIRE(::max == 54);
    }

    SECTION("example 4") {
        vector<int> numbers = {1, 2};
        int plus = 0;
        int minus = 1;
        int mul = 0;
        int div = 0;
        getMinMax(numbers, 1, numbers[0], plus, minus, mul, div);
        REQUIRE(::min == -1);
        REQUIRE(::max == -1);
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int length = 0;
    cin >> length;

    vector<int> numbers;
    numbers.reserve(length);

    for (int i = 0; i < length; i++) {
        int num = 0;
        cin >> num;
        numbers.push_back(num);
    }

    int plus, minus, mul, div = 0;
    cin >> plus;
    cin >> minus;
    cin >> mul;
    cin >> div;

    getMinMax(numbers, 1, numbers[0], plus, minus, mul, div);

    cout << ::max << "\n";
    cout << ::min << "\n";

    return 0;
}
