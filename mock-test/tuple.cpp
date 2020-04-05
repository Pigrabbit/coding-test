// 튜플은 다음과 같은 성질을 가지고 있습니다.

// 중복된 원소가 있을 수 있습니다. ex : (2, 3, 1, 2)
// 원소에 정해진 순서가 있으며, 원소의 순서가 다르면 서로 다른 튜플입니다. ex : (1, 2, 3) ≠ (1, 3, 2)
// 튜플의 원소 개수는 유한합니다.

// 원소의 개수가 n개이고, 
// 중복되는 원소가 없는 튜플 (a1, a2, a3, ..., an)이 주어질 때(단, a1, a2, ..., an은 자연수), 
// 이는 다음과 같이 집합 기호 '{', '}'를 이용해 표현할 수 있습니다.
// {{a1}, {a1, a2}, {a1, a2, a3}, {a1, a2, a3, a4}, ... {a1, a2, a3, a4, ..., an}}

// 예를 들어 튜플이 (2, 1, 3, 4)인 경우 이는

// {{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}} 와 같이 표현할 수 있습니다. 
// 이때, 집합은 원소의 순서가 바뀌어도 상관없으므로

// {{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}
// {{2, 1, 3, 4}, {2}, {2, 1, 3}, {2, 1}}
// {{1, 2, 3}, {2, 1}, {1, 2, 4, 3}, {2}}
// 는 모두 같은 튜플 (2, 1, 3, 4)를 나타냅니다.

// 특정 튜플을 표현하는 집합이 담긴 문자열 s가 매개변수로 주어질 때, 
// s가 표현하는 튜플을 배열에 담아 return 하도록 solution 함수를 완성해주세요.

// sol
// 문자열 처리 문제이다.
// 괄호를 stack으로 tracking해서 subarray들을 알아낸다.

// subarray를 짧은 것부터 순서대로 보면서
// tuple의 시퀀스를 알아낸다.
// 원소 1개인 subarray의 원소가 a1이다.
// 원소 2개인 subarray의 원소중에 a1이 아닌 놈이 a2다.
// 원소 3개인 subarray의 원소중에 a1, a2가 아닌 놈이 a3다.

// 이렇게 얻어낸 ai들을 순서대로 vector에 push back해서 return 하자.


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int>> subArrays;
    int openIdx = 0, len = s.size();
    bool isOpened = false;
    string subStr;

    for (int i = 1; i < len - 1; i++) {
        if (s[i] == '{') {
            isOpened = true;
            openIdx = i;
        }
        if (s[i] == '}' && isOpened) {
            isOpened = false;
            subStr = s.substr(openIdx + 1, i-openIdx-1);

            vector<int> subArray;
            for (int j = 0; j < i-openIdx-1; j++) {
                // 한 자리 수가 아닐 수 있음.
                string num = "";
                for (int k = j; k < i-openIdx-1; k++) {
                    if (subStr[k] == ',') break;
                    num += subStr[k];
                    j = k + 1;
                }

                subArray.push_back(stoi(num));
            }
            subArrays.push_back(subArray);
        }
    }

    // cout << "\nPrinting subarrays\n";
    // for (auto sub: subArrays) {
    //     for (auto el: sub) {
    //         cout << el << " ";
    //     }
    //     cout << "\n";
    // }

    // STEP 2
    sort(subArrays.begin(), subArrays.end(), [](const vector<int> &a, const vector<int> &b){ return a.size() < b.size();});
    int numSubArrays = subArrays.size();

    for (int i = 0; i < numSubArrays; i++) {
        if (answer.empty()) {
            answer.push_back(subArrays[i][0]);
            continue;
        }

        // int lastElement = answer.back();
        while (find(answer.begin(), answer.end(), subArrays[i].back()) != answer.end()) {
        // while (subArrays[i].back() == lastElement) {
            subArrays[i].pop_back();
        }

        int nextElement = subArrays[i].back();
        cout << "Pushing " << nextElement << " into answer\n";
        answer.push_back(nextElement);
    }

    return answer;
}

TEST_CASE("solution") {
    SECTION("example1") {
        string s = "{{2},{2,1},{2,1,3},{2,1,3,4}}";
        vector<int> exp = {2, 1, 3, 4};
        REQUIRE(solution(s) == exp);
    }
    SECTION("example2") {
        string s = "{{1,2,3},{2,1},{1,2,4,3},{2}}";
        vector<int> exp = {2, 1, 3, 4};
        REQUIRE(solution(s) == exp);
    }
}
