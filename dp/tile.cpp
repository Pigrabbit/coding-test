// Problem: https://programmers.co.kr/learn/courses/30/lessons/43104

#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 80;
long long tile[MAX_N + 1];
long long len[MAX_N + 1];

long long getTileLen(int N) {
    if (N == 1 || N == 2) {
        return 1;
    }
    if (tile[N] != -1) {
        return tile[N];
    } 

    tile[N] = getTileLen(N-1) + getTileLen(N-2);
    return tile[N];
}


long long solution(int N) {
    long long answer = 0;
    memset(tile, -1, sizeof(tile));
    memset(len, -1, sizeof(len));

    if (N == 1) {
        len[N] = 4 * getTileLen(N);
        return len[N];
    }

    if (len[N] != -1) {
        return len[N];
    } 
    len[N] = solution(N-1) + 2 * getTileLen(N);
    answer = len[N];

    return answer;
}