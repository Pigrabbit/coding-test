// Problem: https://www.acmicpc.net/problem/1966

#include <iostream>
#include <deque>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

bool checkHigherPriority(std::deque<std::vector<int>> & printerQueue, int priority) {
    for (int i = 1; i < printerQueue.size(); i++) {
        if (printerQueue[i][0] > priority) {
            return true;
        }
    }
    return false;
}

TEST_CASE("checkHigherPriority") {
    SECTION("example 1") {
        std::deque<std::vector<int>> dq = {{1, 0}, {2, 1}, {3, 2}, {4, 3}};
        std::vector<int> doc = dq.front();
        REQUIRE(checkHigherPriority(dq, doc[0]) == true);
    }
    SECTION("example 2") {
        std::deque<std::vector<int>> dq = {{2, 1}, {3, 2}, {4, 3}, {1, 0}};
        std::vector<int> doc = dq.front();
        REQUIRE(checkHigherPriority(dq, doc[0]) == true);
    }
    SECTION("example 3") {
        std::deque<std::vector<int>> dq = {{4, 3}, {1, 0}, {2, 1}, {3, 2}};
        std::vector<int> doc = dq.front();
        REQUIRE(checkHigherPriority(dq, doc[0]) == false);
    }
}

int getOrder(std::deque<std::vector<int>> & printerQueue, int targetIdx) {
    int order = 0;
    while (!printerQueue.empty()) {
        std::vector<int> doc = printerQueue.front();
        int priority = doc[0], idx = doc[1];
        if (checkHigherPriority(printerQueue, priority)) {
            // 나머지 문서들 중 현재 문서보다 중요도가 높은 문서가 있는 경우
            printerQueue.pop_front();
            printerQueue.push_back(doc);
        } else {
            // 없는 경우
            order++;
            printerQueue.pop_front();
            if (idx == targetIdx) {
                return order;
            }
        }
    }
    return order;
}

TEST_CASE("getOrder") {
    SECTION("example 1") {
        std::deque<std::vector<int>> dq = {{1, 0}, {2, 1}, {3, 2}, {4, 3}};
        int order = getOrder(dq, 2);        
        REQUIRE(order == 2);
    }
    SECTION("example 2") {
        std::deque<std::vector<int>> dq = {{5, 0}};
        int order = getOrder(dq, 0);        
        REQUIRE(order == 1);
    }
    SECTION("example 1") {
        std::deque<std::vector<int>> dq = {{1, 0}, {1, 1}, {9, 2}, {1, 3}, {1, 4}, {1, 5}};
        int order = getOrder(dq, 0);        
        REQUIRE(order == 5);
    }
}

int main() {
    int numTestCase = 0;
    std::cin >> numTestCase;
    std::vector<int> answers;

    for (int i = 0; i < numTestCase; i++) {
        std::deque<std::vector<int>> printerQueue;
        int n = 0, m = 0;
        std::cin >> n >> m;
        for (int j = 0; j < n; j++) {
            int priority = 0;
            std::cin >> priority;
            printerQueue.push_back({priority, j});
        }
        int order = getOrder(printerQueue, m);
        answers.push_back(order);
    }

    for (auto answer: answers) {
        std::cout << answer << "\n";
    }

    return 0;
}