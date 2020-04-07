// Problem: https://www.acmicpc.net/problem/1182

#include <iostream>

using namespace std;

const int MAX_N = 20;
int arr[MAX_N];

int getSatisfyingCases(int idx, int curSum, int len, int target) {
    if (idx >= len) return 0;

    int ret = 0;
    if (curSum + arr[idx] == target) ret++;

    return ret + getSatisfyingCases(idx + 1, curSum, len, target) + getSatisfyingCases(idx + 1, curSum + arr[idx], len, target);
}

int main() {
    int len = 0, target = 0;
    cin >> len >> target;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    cout << getSatisfyingCases(0, 0, len, target) << "\n";

    return 0;
}
