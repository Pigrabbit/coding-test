// Problem: https://www.acmicpc.net/problem/10942

#include <iostream>
// #include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

bool isPalindrome(int *arr, int start, int end) {
    bool isPalindrome = true;
    int* pStart = arr + (start - 1);
    int* pEnd = arr + (end - 1);

    while (pStart < pEnd) {
        if (*pStart != *pEnd) {
            isPalindrome = false;
            break;
        } else {
            pStart++;
            pEnd--;
        }
    }

    return isPalindrome;

}

TEST_CASE("isPalindrome") {
    int length = 7;
    int arr[length] = {1, 2, 1, 3, 1, 2, 1};
    SECTION("example 1") {
        int start = 1, end = 3;
        bool isPal = isPalindrome(arr, start, end);
        REQUIRE(isPal == true);
    }
    SECTION("example 2") {
        int start = 2, end = 5;
        bool isPal = isPalindrome(arr, start, end);
        REQUIRE(isPal == false);
    }
    SECTION("example 3") {
        int start = 3, end = 3;
        bool isPal = isPalindrome(arr, start, end);
        REQUIRE(isPal == true);
    }
    SECTION("example 4") {
        int start = 5, end = 7;
        bool isPal = isPalindrome(arr, start, end);
        REQUIRE(isPal == true);
    }
}
