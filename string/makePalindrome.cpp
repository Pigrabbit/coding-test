// Problem: https://www.acmicpc.net/problem/1213

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

string makePalindrome(string name) {
    string ret;
    unordered_map<char, int> counter;
    for (int i = 0; i < name.size(); i++) {
        if (counter.count(name[i]) > 0) counter[name[i]]++;
        else counter[name[i]] = 1;
    }

    vector<char> keys;
    keys.reserve(counter.size());
    vector<int> values;
    values.reserve(counter.size());
    
    int numOddChars = 0;
    char oddChar = '\0';
    for(auto kv : counter) {
        keys.push_back(kv.first);
        values.push_back(kv.second);
        if (kv.second % 2 == 1) {
            numOddChars++;
            oddChar = kv.first;
        }
    }

    if (numOddChars > 1) return "I'm Sorry Hansoo";

    if (oddChar != '\0') ret = string(1, oddChar);

    sort(keys.begin(), keys.end(), greater<char>());

    for (int i = 0; i < keys.size(); i++) {
        int occurence = counter[keys[i]] / 2;
        ret = string(occurence, keys[i]) + ret + string(occurence, keys[i]);
    }

    return ret;
}

TEST_CASE("makePalindrome") {
    SECTION("given invalid palindrome source") {
        string name = "CCCA";
        REQUIRE(makePalindrome(name) == "I'm Sorry Hansoo");
    }
    SECTION("example 1") {
        string name = "AABB";
        REQUIRE(makePalindrome(name) == "ABBA");
    }
    SECTION("example 2") {
        string name = "XXXXAABB";
        REQUIRE(makePalindrome(name) == "ABXXXXBA");
    }
}

int main() {
    string name;
    cin >> name;

    cout << makePalindrome(name) << "\n";

    return 0;
}
