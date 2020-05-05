// Problem: https://www.acmicpc.net/problem/2225

#include <iostream>

using namespace std;

const long long MOD = 1000000000;
const int MAX = 200;
int N, K;
int cache[MAX + 1];

// K\N| 1  2  3  4 .... 200
// ------------------------
// 1 |  1  1  1  1 ...   1
// 2 |  2  3  4  5 ...  201
// 3 |  3  6  10 15 ... 

int main() {
    cin >> N >> K;
    for (int i = 1; i <= K; i++) 
        cache[i] = i;

    for (int i = 1; i < N; i++) 
        for (int j = 1; j <= K; j++)
            cache[j] = (cache[j] + cache[j-1]) % MOD;

    cout << cache[K] << "\n";
}
