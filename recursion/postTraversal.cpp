// Problem: https://www.acmicpc.net/problem/5639

#include <iostream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

std::vector<int> preOrder;

void reverseOrder(int start, int end) {
    if (start == end) {
        return;
    }
    int root = preOrder[start];
    
    int rightSubtreeRootIdx = end + 1;
    for (int i = start + 1; i <= end; i++) {
        if (preOrder[i] > root) {
            rightSubtreeRootIdx = i;
            break;
        }
    }
    int leftSubtreeEnd = (rightSubtreeRootIdx != end + 1)? (rightSubtreeRootIdx - 1) : end;
    if (leftSubtreeEnd - start > 1) {
        reverseOrder(start + 1, leftSubtreeEnd);
    }
    if (end - rightSubtreeRootIdx >= 0) {
        reverseOrder(rightSubtreeRootIdx, end);
    }
    preOrder.erase(preOrder.begin() + start);
    preOrder.insert(preOrder.begin() + end, root);
}

void printVector(std::vector<int> toPrint) {
    for (auto i: toPrint) {
        std::cout << i << "\n";
    }
}

TEST_CASE("reverseOrder") {
    SECTION("only root node") {
        std::vector<int> preTraversal = {30};
        preOrder.assign(preTraversal.begin(), preTraversal.end());
        reverseOrder(0, preTraversal.size()-1);
        // printVector(preOrder);
        REQUIRE(preOrder.front() == 30);
    }
    SECTION("tree with 3 nodes") {
        std::vector<int> preTraversal = {24, 5, 28};
        preOrder.assign(preTraversal.begin(), preTraversal.end());
        reverseOrder(0, preTraversal.size()-1);
        // printVector(preOrder);
        REQUIRE(preOrder.front() == 5);
    }
    SECTION("exapmle input") {
        std::vector<int> preTraversal = {50, 30, 24, 5, 28, 45, 98, 52, 60};
        preOrder.assign(preTraversal.begin(), preTraversal.end());
        reverseOrder(0, preTraversal.size()-1);
        printVector(preOrder);
        REQUIRE(preOrder.front() == 5);
        REQUIRE(preOrder.back() == 50);
    }
}

int main() {
    int node;
    
    while (std::cin >> node) {
        preOrder.push_back(node);
    }

    reverseOrder(0, preOrder.size() - 1);
    printVector(preOrder);

    return 0;
}
