// Problem: https://www.acmicpc.net/problem/11656

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> getSuffixArray(string & s) {
    vector<string> ret(s.length());
    for (int i = 0; i < s.length(); i++) {
        ret[i] = s.substr(i);
    }

    sort(ret.begin(), ret.end());

    return ret;
}

int main() {
    string s;
    cin >> s;
    vector<string> suffixArray = getSuffixArray(s);
    
    for (auto suffix: suffixArray) {
        cout << suffix << "\n";
    }

    return 0;
}
