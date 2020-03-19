// Problem: https://programmers.co.kr/learn/courses/30/lessons/60058

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

bool isValid(string &s) {
    bool ret = false;
    stack<char> parentheses;
    for (char& c :s) {
        if (c == '(') {
            parentheses.push(c);
        } else {
            if (parentheses.empty()) {
                return ret;
            }
            parentheses.pop();
        }
    }
    return ret = true;
}

TEST_CASE("isValid") {
    SECTION("example1") {
        string s = "(()))(";
        REQUIRE(isValid(s) == false);
    }
    SECTION("example2") {
        string s = "(())()";
        REQUIRE(isValid(s) == true);
    }
}

vector<string> split(string &s) {
    vector<string> uAndv;
    int countLeft = 0, countRight = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            countLeft++;
        } else {
            countRight++;
        }

        if (countLeft == countRight) {
            string u = s.substr(0, i + 1);
            string v = s.substr(i + 1);
            uAndv.push_back(u);
            uAndv.push_back(v);
            break;
        }
    }

    return uAndv;
}

TEST_CASE("split") {
    SECTION("example1") {
        string s = "(()))(";
        vector<string> uAndv = split(s);
        string u = uAndv[0], v = uAndv[1];
        REQUIRE(u == "(())");
        REQUIRE(v == ")(");
    }
}

void reverseDirection(string &s) {
    for (char& c :s) {
        if (c == '(') {
            c = ')';
        } else {
            c = '(';
        }
    }
}


string solution(string p) {
    string answer = "";
    // STEP 1
    if (p.size() == 0) {
        return answer;
    }
    // STEP 2
    vector<string> uAndv = split(p);
    string u = uAndv[0], v = uAndv[1];
    // STEP 3
    if (isValid(u)) {
        return u + solution(v);
    }
    // STEP 4
    answer = "(" + solution(v) + ")";
    reverseDirection(u);
    answer += u.substr(1, u.size() - 2);

    return answer;
}

TEST_CASE("solution") {
    SECTION("example1") {
        string p = "(()())()";
        REQUIRE(solution(p) == "(()())()");
    }
    SECTION("example2") {
        string p = ")(";
        REQUIRE(solution(p) == "()");
    }
    SECTION("example3") {
        string p = "()))((()";
        REQUIRE(solution(p) == "()(())()");
    }
}
