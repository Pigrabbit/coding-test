// Problem: https://programmers.co.kr/learn/courses/30/lessons/42862

#include <string>
#include <vector>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    vector<int> toCheck(n+1, 1);
    for (int i = 0; i < lost.size(); i++) {
        for (int j = 0; j < reserve.size(); j++) {
            if (lost[i] == reserve[j]) {
                answer++;
                toCheck[lost[i]] = 0;
                lost.erase(lost.begin() + i);
                reserve.erase(reserve.begin() + j);
                i--, j--;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        vector<int>::iterator hasLost = find(lost.begin(), lost.end(), i);
        if (hasLost == lost.end()) {
            // 안 잃어버린 경우
            if (toCheck[i] == 0) {
                continue;
            }
            answer++;
            continue;
        }
        // i + 1 또는 i - 1이 reserve에 있는지 확인
        int resreveSize = reserve.size();
        
        for (int j = 0; j < resreveSize; j++) {
            if (reserve[j] == i - 1 || reserve[j] == i + 1) {
                answer++;
                reserve.erase(reserve.begin() + j);
                break;
            }
        }
    }
    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        int n = 5;
        vector<int> lost = {2, 4};
        vector<int> reserve = {1, 3, 5};
        REQUIRE(solution(n, lost, reserve) == 5);
    }
    SECTION("example 2") {
        int n = 5;
        vector<int> lost = {2, 4};
        vector<int> reserve = {1, 2};
        REQUIRE(solution(n, lost, reserve) == 4);
    }
}
