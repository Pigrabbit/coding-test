// Problem: https://www.acmicpc.net/problem/1978

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    int numInputs = 0;
    cin >> numInputs;
    
    vector<int> inputs(numInputs, 0);
    int maxInput = 0;

    for (int i = 0; i < numInputs;  i++) {
        cin >> inputs[i];
        maxInput = max(inputs[i], maxInput);
    }

    // eratos
    bool isPrimeNum[maxInput + 1];
    memset(isPrimeNum, true, sizeof(isPrimeNum));
    isPrimeNum[0] = false, isPrimeNum[1] = false;

    for (int i = 2; i * i <= maxInput; i++) {
        if (!isPrimeNum[i]) continue;
        for (int j = i * i; j <= maxInput; j += i) {
            isPrimeNum[j] = false;
        }
    }

    int cnt = 0;
    for (int i = 0; i < numInputs; i++)
        if (isPrimeNum[inputs[i]]) cnt++;

    cout << cnt << "\n";

    return 0;
}

