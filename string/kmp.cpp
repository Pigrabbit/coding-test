// Problem: https://www.acmicpc.net/problem/16916

#include <iostream>
#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

// KMP algorithm
vector<int> getPrefixTable(string & needle) {
    vector<int> prefixTable(needle.length(), 0);
    int needleLength = needle.size();

    int begin = 1, matched = 0;
    while (begin + matched < needleLength) {
        if (needle[begin + matched] == needle[matched]) {
            ++matched;
            prefixTable[begin + matched - 1] = matched;
        } else {
            if (matched == 0) {
                begin++;
            } else {
                begin += matched - prefixTable[matched - 1];
                matched = prefixTable[matched - 1];
            }
        }
    }

    return prefixTable;
}

// KMP algorithm
int isSubstring(string & haystack, string & needle, vector<int> & prefixTable) {
    int needleInHaystack = 0;
    int begin = 0, matched = 0;
    int haystackLength = haystack.size();
    int needleLength = needle.size();

    // iterate through haystack string
    while (begin <= haystackLength - needleLength) {
        if (matched < needleLength && haystack[begin + matched] == needle[matched]) {
            // when characters are matched
            ++matched;
            if (matched == needleLength) {
                // when the last character of needle string is matched
                needleInHaystack = 1;
            }
        } else {
            if (matched == 0) {
                // no character sequence in common.
                ++begin;
            } else {
                // some sequence was in common, but found unmatched
                // update position to start next searching 
                begin += matched - prefixTable[matched - 1];
                matched = prefixTable[matched - 1];
            }
        }
    }

    return needleInHaystack;
}

void printVector(vector<int> vec) {
    for (auto i: vec) {
        cout << i << " ";
    }
    cout << "\n";
}

TEST_CASE("isSubstring") {
    SECTION("example1") {
        string haystack = "colacocacola";
        string needle = "cocacola";
        vector<int> prefixTable = getPrefixTable(needle);
        REQUIRE(isSubstring(haystack, needle, prefixTable) == 1);
    }
}

TEST_CASE("prefixTable") {
    SECTION("no repeating substring") {
        string needle = "abcdefgh";
        vector<int> prefixTable = getPrefixTable(needle);
        printVector(prefixTable);
        REQUIRE(prefixTable[7] == 0);
    }
    SECTION("repeating sequence") {
        string needle = "cocacola";
        vector<int> prefixTable = getPrefixTable(needle);
        printVector(prefixTable);
        REQUIRE(prefixTable[0] == 0);
        REQUIRE(prefixTable[1] == 0);
        REQUIRE(prefixTable[2] == 1);
        REQUIRE(prefixTable[3] == 0);
        REQUIRE(prefixTable[4] == 1);
        REQUIRE(prefixTable[5] == 2);
        REQUIRE(prefixTable[6] == 0);
        REQUIRE(prefixTable[7] == 0);
    }
}

int main() {
    string haystack, needle;
    cin >> haystack;
    cin >> needle;

    vector<int> prefixTable = getPrefixTable(needle);
    cout << isSubstring(haystack, needle, prefixTable) << "\n";

    return 0;
}
