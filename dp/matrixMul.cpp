// Problem: https://www.acmicpc.net/problem/11049

#include <iostream>
#include <limits.h>
#include <cstring>

const int MAX_MATRICES = 500;

int matrices[MAX_MATRICES][2];
int cache[MAX_MATRICES][MAX_MATRICES];

int getMinMul(int start, int end) {
    if (start == end) {
        return 0;
    }
    int & ret = cache[start][end];
    if (ret != -1) {
        return ret;
    }
    ret = INT_MAX;

    for (int i = start; i < end; i++) {
        int curRow = matrices[start][0], curCol = matrices[i][1], nextCol = matrices[end][1];
        int tmp = getMinMul(start, i) + getMinMul(i+1, end) + curRow * curCol * nextCol;
        ret = std::min(ret, tmp);
    }
    return ret;
}

int main() {
    int N = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            std::cin >> matrices[i][j];
        }
    }

    std::memset(cache, -1 , sizeof(cache));
    
    std::cout << getMinMul(0, N - 1) << "\n";

    return 0;
}
