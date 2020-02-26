// Problem: https://www.acmicpc.net/problem/9251

#include <iostream>
#include <string>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int MAX_LENGTH = 1000;
std::string A, B;
int dp[1+MAX_LENGTH][1+MAX_LENGTH];

int LCS(int posA, int posB) {
    if (posA >= A.size() || posB >= B.size()) {
        return 0;
    }
    int & ret = dp[posA][posB];
    if (ret != -1) {
        return ret;
    }
    
    if (A[posA] == B[posB]) {
        ret = 1 + LCS(posA + 1, posB + 1);
    } else {
        ret = std::max(LCS(posA + 1, posB), LCS(posA, posB + 1));
    }
    return ret;
}

TEST_CASE("LCS") {
    SECTION("identical single character strings") {
        std::memset(dp, -1, sizeof dp);
        A = std::string(1, 'A');
        B = std::string(1, 'A');
        REQUIRE(LCS(0, 0) == 1);
    }
    SECTION("different single character strings") {
        std::memset(dp, -1, sizeof dp);
        A = std::string(1, 'A');
        B = std::string(1, 'B');
        REQUIRE(LCS(0, 0) == 0);
    }
    SECTION("no common subsequence strings") {
        std::memset(dp, -1, sizeof dp);
        A = "ABCDEF";
        B = "PQRSTUV";
        REQUIRE(LCS(0, 0) == 0);
    }
    SECTION("Simple case") {
        std::memset(dp, -1, sizeof dp);
        A = "DAB";
        B = "CEA";
        REQUIRE(LCS(0, 0) == 1);
    }
    SECTION("has common subsequence strings") {
        std::memset(dp, -1, sizeof dp);
        A = "ACAYKP";
        B = "CAPCAK";
        REQUIRE(LCS(0, 0) == 4);
    }
    SECTION("single letter with long length") {
        std::memset(dp, -1, sizeof dp);
        A = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        B = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        REQUIRE(LCS(0, 0) == 257);
    }
    SECTION("different length") {
        std::memset(dp, -1, sizeof dp);
        A = "AAA";
        B = "AA";
        REQUIRE(LCS(0, 0) == 2);
    }
    SECTION("wrong case") {
        std::memset(dp, -1, sizeof dp);
        A = "bcdefgha";
        B = "acdefghb";
        REQUIRE(LCS(0, 0) == 6);
    }
}

int main() {
    std::memset(dp, -1, sizeof dp);
    std::cin >> A;
    std::cin >> B;
    
    std::cout << LCS(0, 0) << "\n";

    return 0;
}
