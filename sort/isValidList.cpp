#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

bool isValidList(vector<string>& numList) {
    int listLength = numList.size();
    for (int i = 1; i < listLength; i++) {
        string &compareNum = numList[i];
        string &prefixNum = numList[i-1];

        int prefixLength = 0;
        if (prefixNum.length() <= compareNum.length()) {
            prefixLength = prefixNum.length();
        } else {
            prefixLength = compareNum.length();
        }

        int count = 0;
        for (int j = 0; j <= prefixLength; j++) {
            // iterate over prefixLength to check 
            // that compareNum starts with the prefixNum
            if (j == count) {
                if (compareNum[j] == prefixNum[j]) {
                    // increase count when there are same number on same pos
                    count++;
                } else if (compareNum[j] == '\0' && prefixNum[j] != '\0') {
                    // check if one of the Number is at the end
                    return false;
                } else if (compareNum[j] != '\0' && prefixNum[j] == '\0') {
                    return false;
                }
            } else {
                break;
            }
        }
    }

    return true;
}

TEST_CASE("isValidList") {
    SECTION("example1") {
        vector<string> numList = {
            "911", "97625999", "91125426"
        };
        sort(numList.begin(), numList.end());
        REQUIRE(isValidList(numList) == false);
    }
    SECTION("example2") {
        vector<string> numList = {
            "113", "12340", "123440", "12345", "98346"
        };
        sort(numList.begin(), numList.end());
        REQUIRE(isValidList(numList) == true);
    }
}

int main() {
    int numTestCase = 0;
    cin >> numTestCase;
    string result;

    for (int i = 0; i < numTestCase; i++) {
        int listLength = 0;
        cin >> listLength;

        vector<string> numList;
        numList.reserve(listLength);

        for (int j = 0; j < listLength; j++) {
            string number;
            cin >> number;
            numList.push_back(number);
        }
        sort(numList.begin(), numList.end());

        if (isValidList(numList)) {
            result.append("YES\n");
        } else {
            result.append("NO\n");
        }
    }
    cout << result;
    return 0;
}
