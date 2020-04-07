// Problem: https://programmers.co.kr/learn/courses/30/lessons/17677

#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

#define vec vector

using namespace std;

vec<string> preprocess(string str) {
    regex r("[a-zA-Z]{2}");
    vec<string> ret;
    while (str.size() > 1) {
        string twoLetters = str.substr(0, 2);
        if (regex_match(twoLetters, r)) {
            // 대문자로 바꾸기
            transform(twoLetters.begin(), twoLetters.end(), twoLetters.begin(), ::toupper);
            ret.push_back(twoLetters);
        }
        str.erase(0, 1);
    }

    cout << "After Preprocess\n";
    for (auto el: ret) {
        cout << el << " ";
    }
    cout << "\n";
    return ret;
}

TEST_CASE("preprocess") {
    SECTION("example 1") {
        string s = "shake hands";
        cout << s << "\n";
        vec<string> ret = preprocess(s);
        for (auto el: ret) {
            cout << el << "\n";
        }
        REQUIRE(ret.size() == 7);
    }
    SECTION("without special letters, only Upper case") {
        string s = "FRANCE";
        cout << s << "\n";
        vec<string> ret = preprocess(s);
        for (auto el: ret) {
            cout << el << "\n";
        }
        REQUIRE(ret.size() == 5);
    }
    SECTION("without special letters, with lower case") {
        string s = "FraNCe";
        cout << s << "\n";
        vec<string> ret = preprocess(s);
        for (auto el: ret) {
            cout << el << "\n";
        }
        REQUIRE(ret.size() == 5);
    }
    SECTION("with special letters") {
        string s = "F_RENCH+";
        cout << s << "\n";
        vec<string> ret = preprocess(s);
        for (auto el: ret) {
            cout << el << "\n";
        }
        REQUIRE(ret.size() == 4);
    }
}

int solution(string str1, string str2) {
    int answer = 0;
    vec<string> set1 = preprocess(str1);
    vec<string> set2 = preprocess(str2);

    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());

    vector<string> intersection;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(intersection));

    vector<string> unionVector;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(unionVector));

    double numIntersection = intersection.size(), numUnion = unionVector.size();
    double jacard = 65536.0;
    if (numUnion != 0) jacard = (numIntersection / numUnion) * 65536;
    answer = floor(jacard);

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        string str1 = "FRANCE";
        string str2 = "french";
        int answer = solution(str1, str2);
        REQUIRE(answer == 16384);
    }
    SECTION("example 2") {
        string str1 = "handshake";
        string str2 = "shake hands";
        int answer = solution(str1, str2);
        REQUIRE(answer == 65536);
    }
    SECTION("example 3") {
        string str1 = "aa1+aa2";
        string str2 = "AAAA12";
        int answer = solution(str1, str2);
        REQUIRE(answer == 43690);
    }
    SECTION("example 4") {
        string str1 = "E=M*C^2";
        string str2 = "e=m*c^2";
        int answer = solution(str1, str2);
        REQUIRE(answer == 65536);
    }
}


