#include <string>
#include <vector>
#include <numeric>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

int solution(vector<int> requests, int M) {
    int answer = 0;
    int sum = accumulate(requests.begin(), requests.end(), 0);
    int low = 0;
    int high = *max_element(requests.begin(), requests.end());

    if (sum <= M) {
        return high;
    }

    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> payable;
        int payableSum = 0;
        for (int request: requests) {
            if (request > mid) {
                payable.push_back(mid);
                payableSum += mid;
            } else {
                payable.push_back(request);
                payableSum += request;
            }
        }
        
        if (payableSum > M) {
            high = mid - 1;
        } else {
            if (mid >= answer) {
                answer = mid;
            }
            low = mid + 1;
        }
    }
    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<int> budgets = {120, 110, 140, 150};
        int M = 485;
        int answer = 127;
        REQUIRE(solution(budgets, M) == answer);
    }
}