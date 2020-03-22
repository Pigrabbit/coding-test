// Problem: https://www.acmicpc.net/problem/9935

#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

std::string str;
std::string explodeStr;

int totalLen;
int explodeLen;

int hashCode(std::string s) {
    int g = 31;
    int hash = 0;
    for (int i = 0; i < s.length(); i++) {
        hash = g * hash + s[i];
    }
    return hash;
}

int explode(int explodeHash, int start) {
    int hasExploded = 0;
    std::string toCheck = str.substr(start, explodeLen);
    if (hashCode(toCheck) == explodeHash) {
        str.erase(start, explodeLen);
        std::cout << "explode from " << start << ", to " << start+explodeLen << "\n";
        hasExploded = 1;
    }
    return hasExploded;
}

TEST_CASE("hashCode") {
    SECTION("with identical string") {
        std::string s1 = "hello";
        std::string s2 = "hello";
        REQUIRE(hashCode(s1) == hashCode(s2));
    }
    SECTION("with different string") {
        std::string s1 = "hello";
        std::string s2 = "ola";
        REQUIRE(hashCode(s1) != hashCode(s2));
    }
}

int main() {
    std::cin >> str >> explodeStr;
    totalLen = str.size();
    explodeLen = explodeStr.size();

    int explodeHash = hashCode(explodeStr);

    for (int i = 0; i <= totalLen - explodeLen; i++) {
        int hasExploded = explode(explodeHash, i);
        if (hasExploded) {
            totalLen -= explodeLen;

            if (i >= explodeLen) {
                i -= explodeLen;
            } else if (i > 0){
                i = -1;
            }
        }
    }

    if (str.size() == 0) std::cout << "FRULA" << "\n";
    else std::cout << str << "\n";

    return 0;
}

