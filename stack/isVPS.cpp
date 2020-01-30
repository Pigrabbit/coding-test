// Problem: https://www.acmicpc.net/problem/9012

#include <iostream>
#include <string>
#include <stack>
// #define CATCH_CONFIG_MAIN
// #include "../lib/catch.hpp"

using namespace std;

bool isVPS(string ps) {
    stack<char> parentheses;

    for (char parenthesis: ps) {
        if (parenthesis == '(') {
            parentheses.push('(');
        } else if (parenthesis == ')') {
            if (parentheses.empty()) {
                return false;
            } else {
                parentheses.pop();
            }
        }
    }

    if (!parentheses.empty()) {
        return false;
    }

    return true;
}

// TEST_CASE("isVPS") {
//     SECTION("with single parenthesis") {
//         string ps = "(";
//         REQUIRE(isVPS(ps) == false);
//     }

//     SECTION("with single pair of parenthesis, in order") {
//         string ps = "()";
//         REQUIRE(isVPS(ps) == true);
//     }

//     SECTION("with single reversed pair of parenthesis") {
//         string ps = ")(";
//         REQUIRE(isVPS(ps) == false);
//     }

//     SECTION("example 1, not VPS") {
//         string ps = "(())())";
//         REQUIRE(isVPS(ps) == false);
//     }

//     SECTION("example 2, not VPS") {
//         string ps = "(((()())()";
//         REQUIRE(isVPS(ps) == false);
//     }

//     SECTION("example 3, VPS") {
//         string ps = "(()())((()))";
//         REQUIRE(isVPS(ps) == true);
//     }

//     SECTION("example 4, not VPS") {
//         string ps = "((()()(()))(((())))()";
//         REQUIRE(isVPS(ps) == false);
//     }

//     SECTION("example 5, VPS") {
//         string ps = "()()()()(()()())()";
//         REQUIRE(isVPS(ps) == true);
//     }

//     SECTION("example 6, not VPS") {
//         string ps = "(()((())()(";
//         REQUIRE(isVPS(ps) == false);
//     }
// }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int numTestCase;
    cin >> numTestCase;

    for (int i = 0; i < numTestCase; i++) {
        string result = "NO";
        string ps;
        cin >> ps;
        if (isVPS(ps)) { result = "YES"; }
        cout << result << "\n";
    }

    return 0;
}