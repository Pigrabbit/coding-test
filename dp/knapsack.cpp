// Problem: https://www.acmicpc.net/problem/12865

#include <iostream>
#include <limits.h>

const int MAX_ITEM = 100, MAX_WEIGHT = 100000;
int weights[MAX_ITEM + 1];
int values[MAX_ITEM + 1];
int dp[MAX_ITEM + 1][MAX_WEIGHT + 1];

int KS(int numItemLeft, int capacity){
    if (::dp[numItemLeft][capacity] != -1) {
        return ::dp[numItemLeft][capacity];
    }
    int result = 0;
    if (numItemLeft == 0 || capacity == 0) {
        result = 0;
    } else if (weights[numItemLeft] > capacity) {
        result = KS(numItemLeft - 1, capacity);
    } else {
        int tmp1 = KS(numItemLeft-1, capacity);
        int tmp2 = values[numItemLeft] + KS(numItemLeft-1, capacity - weights[numItemLeft]);
        result = std::max(tmp1, tmp2);
    }
    ::dp[numItemLeft][capacity] = result;
    return result;
}

int main() {
    int N = 0, K = 0;
    std::cin >> N >> K;
    
    for (int i = 1; i <= N; i++) {
        std::cin >> weights[i] >> values[i];
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            ::dp[i][j] = -1;
        }
    }

    int result = KS(N, K);
    std::cout << "printing dp array\n";
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            std::cout << ::dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << result << "\n";

    return 0;
}
