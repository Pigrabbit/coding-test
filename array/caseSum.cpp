// Problem: https://www.acmicpc.net/problem/2003

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

int getSatisfiedCase(int * arr, int size, int M) {
    int satisfiedCase = 0;
    for (int i = 0; i < size; i++) {
        int sum = arr[i];
        if (sum == M) {
            satisfiedCase++;
        } else {
            for (int j = i + 1; j < size; j++) {
                sum += arr[j];
                if (sum == M) {
                    satisfiedCase++;
                }
            }
        }
    }
    return satisfiedCase;
}

int twoPointer(int * arr, int size, int target) {
    int *pFront = arr, *pBack = arr;
    int sum = arr[0];
    int cases = 0;
    while (pBack - arr < size) {
        if (sum == target) {
            cases++;
            pBack++;
            if (pBack - arr < size) {
                sum += *pBack - *pFront;
            }
            pFront++;
        } else if (sum < target) {
            pBack++;
            if (pBack - arr < size) {
                sum += *pBack;
            }
        } else {
            if (pFront < pBack) {
                sum -= *pFront;
                pFront++;
            } else {
                pBack++;
                if (pBack - arr < size) {
                    sum += *pBack;
                }
            }
        }
    }

    return cases;
}

TEST_CASE("getSatisfiedCase") {
    SECTION("example1") {
        int n = 4;
        int m = 6;
        int* arr = new int[n];
        *arr = 1;
        *(arr + 1) = 4;
        *(arr + 2) = 2;
        *(arr + 3) = 1;

        int satisfiedCase = getSatisfiedCase(arr, n, m);

        REQUIRE(satisfiedCase == 1);
    }
    SECTION("example2") {
        int n = 4;
        int m = 2;
        int* arr = new int[n];
        *arr = 1;
        *(arr + 1) = 1;
        *(arr + 2) = 1;
        *(arr + 3) = 1;

        int satisfiedCase = getSatisfiedCase(arr, n, m);

        REQUIRE(satisfiedCase == 3);
    }
    SECTION("example3") {
        int n = 10;
        int m = 5;
        int* arr = new int[n];
        *arr = 1;
        *(arr + 1) = 2;
        *(arr + 2) = 3;
        *(arr + 3) = 4;
        *(arr + 4) = 2;
        *(arr + 5) = 5;
        *(arr + 6) = 3;
        *(arr + 7) = 1;
        *(arr + 8) = 1;
        *(arr + 9) = 2;

        int satisfiedCase = getSatisfiedCase(arr, n, m);

        REQUIRE(satisfiedCase == 3);
    }
}

TEST_CASE("twoPointer") {
    SECTION("example1") {
        int n = 10;
        int m = 5;
        int* arr = new int[n];
        *arr = 1;
        *(arr + 1) = 2;
        *(arr + 2) = 3;
        *(arr + 3) = 4;
        *(arr + 4) = 2;
        *(arr + 5) = 5;
        *(arr + 6) = 3;
        *(arr + 7) = 1;
        *(arr + 8) = 1;
        *(arr + 9) = 2;

        int satisfiedCase = twoPointer(arr, n, m);

        REQUIRE(satisfiedCase == 3);
    }
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    int * array = new int [n];
    for (int i = 0; i< n; i++) {
        std::cin >> array[i];
    }

    std::cout << getSatisfiedCase(array, n, m) << "\n";
    std::cout << twoPointer(array, n, m) << "\n";

    return 0;
}
