// Problem: https://programmers.co.kr/learn/courses/30/lessons/60057

#include <string>
#include <vector>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int solution(string s) {
    int answer = 0;
    int length = s.length();
    answer = length;

    for (int zipLength = 1; zipLength < length / 2 + 1; zipLength++) {
        int start = 0;
        int tmpLen = length;
        int count = 1;

        string pattern = s.substr(0, zipLength);
        string next = s.substr(0 + zipLength, zipLength);

        while (start + 2 * zipLength <= length) {
            if (pattern == next) {
                // pattern matched!
                if (count == 1 || to_string(count + 1).length() > to_string(count).length() ) {
                    tmpLen = tmpLen - zipLength + 1;
                } else {
                    tmpLen = tmpLen - zipLength;
                }
                
                start += zipLength;
                next = s.substr(start + zipLength, zipLength);
                count += 1;
            } else {
                // pattern unmatched!
                count = 1;
                pattern = next;
                start += zipLength;
                next = s.substr(start + zipLength, zipLength);
            }
        }
        answer = min(answer, tmpLen);
    }

    return answer;
}

TEST_CASE("solutiokn") {
    SECTION("testcase 1") {
        string s = "aabbaccc";
        REQUIRE(solution(s) == 7);
    }
    SECTION("testcase 2") {
        string s = "ababcdcdababcdcd";
        REQUIRE(solution(s) == 9);
    }
    SECTION("testcase 3") {
        string s = "abcabcdede";
        REQUIRE(solution(s) == 8);
    }
    SECTION("testcase 4") {
        string s = "abcabcabcabcdededededede";
        REQUIRE(solution(s) == 14);
    }
    SECTION("testcase 5") {
        string s = "xababcdcdababcdcd";
        REQUIRE(solution(s) == 17);
    }
    SECTION("length 1 string") {
        string s = "x";
        REQUIRE(solution(s) == 1);
    }
}
