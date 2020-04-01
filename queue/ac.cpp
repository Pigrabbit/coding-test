// Problem: https://www.acmicpc.net/problem/5430

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int numTestCase = 0;
    cin >> numTestCase;
    vector<string> answers;

    while (numTestCase--) {
        string direction, arrString, retString;
        int len = 0;
        deque<int> arr;

        cin >> direction >> len >> arrString;

        // check empty array
        if (arrString.size() <= 2 && arrString.find('D') != arrString.npos) {
            retString = "error";
            answers.push_back(retString);
            continue;
        }

        // parse input string
        arrString.erase(arrString.begin());
        arrString.erase(arrString.end() - 1);

        stringstream check1(arrString);
        string buffer;

        while(getline(check1, buffer, ',')) {
            arr.push_back(stoi(buffer));
        }

        // processing directions
        bool isReverse = false;
        for (int i = 0; i < direction.size(); i++) {
            if (direction[i] == 'R') {
                isReverse = isReverse ? false : true;
                continue;
            }
            if (arr.empty()) {
                retString = "error";
                break;
            }
            if (isReverse) {
                arr.pop_back();
                continue;
            }
            arr.pop_front();
        }

        if (retString == "error") {
            answers.push_back(retString);
            continue;
        }

        // compose return String
        retString = "[";
        if (!isReverse) {
            for (int i = 0; i < arr.size(); i++) {
                retString += to_string(arr[i]);
                retString += ",";
            }
        }
        else {
            for (int i = arr.size() - 1; i >= 0; i--) {
                retString += to_string(arr[i]);
                retString += ",";
            }
        }
        retString.erase(retString.end() - 1);
        retString += "]";

        answers.push_back(retString);
    }

    for (auto answer: answers) {
        cout << answer << "\n";
    }

    return 0;
}

