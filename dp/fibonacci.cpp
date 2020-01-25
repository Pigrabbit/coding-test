#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

long long fibonacci(int num) {
    if (num == 0 || num == 1) {
        return num;
    }

    long long memo [num + 1];

    for (int i = 0; i <= num; i++){
        if (i == 0) {
            memo[i] = 0;
        } else if (i == 1) {
            memo[i] = 1;
        } else {
            memo[i] = memo[i-1] + memo[i-2];
        }
    }

    return memo[num];
}

TEST_CASE("fibonacci dp") {
    SECTION("fibonacci 0, base case") {
        int num = 0;
        REQUIRE(fibonacci(num) == 0);
    }

    SECTION("fibonacci 1, base case") {
        int num = 1;
        REQUIRE(fibonacci(num) == 1);
    }

    SECTION("fibonacci 2") {
        int num = 2;
        REQUIRE(fibonacci(num) == 1);
    }
    
    SECTION("fibonacci 2") {
        int num = 10;
        REQUIRE(fibonacci(num) == 34);
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int num = 0;
    cin >> num;

    cout << fibonacci(num) << "\n";
    
    return 0;
}