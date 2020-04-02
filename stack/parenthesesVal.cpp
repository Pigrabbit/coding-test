// Problem: https://www.acmicpc.net/problem/2504

#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int getVal(string s) {
    if (s == "[]") return 3;
    if (s == "()") return 2;

    int roundOpened = 0, squareOpened = 0;
    int startPos = 0, value = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') roundOpened++;
        else if(s[i] == '[') squareOpened++;
        else if(s[i] == ')') {
            if (roundOpened < 1) return 0;
            roundOpened--;
        }
        else if(s[i] == ']') {
            if (squareOpened < 1) return 0;
            squareOpened--;
        }

        if (roundOpened == 0 && squareOpened == 0) {
            string correctParenthese = s.substr(startPos + 1, i - startPos - 1);

            if (s[i] == ')') {
                if (i - startPos > 2) value += 2 * getVal(correctParenthese);
                else value += 2;
            }
            else if (s[i] == ']') {
                if (i - startPos > 2) value += 3 * getVal(correctParenthese);
                else value += 3;
            }

            startPos = i + 1;
        }
    }

    if (roundOpened != 0 || squareOpened != 0) return 0;

    return value;
}

TEST_CASE("getVal") {
    SECTION("with invalid pairs") {
        string invalidPair = "[[[(])";
        REQUIRE(getVal(invalidPair) == 0);
    }

    SECTION("with valid single pair") {
        string validSquaredSinglePair = "[]";
        string validRoundedSinglePair = "()";
        REQUIRE(getVal(validSquaredSinglePair) == 3);
        REQUIRE(getVal(validRoundedSinglePair) == 2);
    }

    SECTION("example 1") {
        string s = "()[[]]";
        REQUIRE(getVal(s) == 11);
    }

    SECTION("example 2") {
        string s = "(()[[]])";
        REQUIRE(getVal(s) == 22);
    }

    SECTION("example 3") {
        string s = "([])";
        REQUIRE(getVal(s) == 6);
    }

    SECTION("example 4") {
        string s = "(()[[]])([])";
        REQUIRE(getVal(s) == 28);
    }
}

int main() {
    string inputStr;
    cin >> inputStr;

    cout << getVal(inputStr) << "\n";

    return 0;
}
