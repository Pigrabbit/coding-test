// Problem: https://www.acmicpc.net/problem/1024

#include <iostream>
#include <vector>

using namespace std;

vector<int> getArrayWithSumN(int N, int L) {
    vector<int> ret;

    for (int len = L; len <= 100; len++) {
        int tmpSum = 0, count = 0;
        for (int i = 1; i < len; i++) {
            tmpSum += i;
        }
        while (tmpSum < N) {
            tmpSum += len;
            count++;
        }

        if (tmpSum == N) {
            // target found
            // int startNum = 1 + count;
            ret.push_back(count);
            for (int i = 1; i < len; i++) {
                ret.push_back(count + i);                
            }
            break;
        }
    }

    if (ret.empty()) return {-1};

    return ret;
}

int main() {
    int N = 0, L = 0;
    cin >> N >> L;

    vector<int> answer = getArrayWithSumN(N, L);

    if (answer[0] == -1) cout << answer[0] << "\n";
    else {
        for (auto num: answer) {
            cout << num << " ";
        }
        cout << "\n";
    }

    return 0;
}
