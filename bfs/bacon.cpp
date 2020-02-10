// Problem: https://www.acmicpc.net/problem/1389

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

unordered_map<int, vector<int>> adjList;

vector<int> bfs(int startNode, int targetNode) {
    vector<int> visited = {startNode};
    // 1st element - Node
    // left elements - path
    queue<vector<int>> bfsQueue;
    bfsQueue.push({startNode, startNode});
    while (bfsQueue.size() > 0) {
        int currentNode = bfsQueue.front()[0];
        vector<int> currentPath = vector<int>(bfsQueue.front().begin()+1, bfsQueue.front().end());
        bfsQueue.pop();
        visited.push_back(currentNode);
        for(auto node: ::adjList[currentNode]) {
            bool hasVisited = find(visited.begin(), visited.end(), node) != visited.end();
            if (!hasVisited) {
                if (node == targetNode) {
                    currentPath.push_back(node);
                    return currentPath;
                } else {
                    vector<int> nodeAndPath = {node};
                    nodeAndPath.insert(nodeAndPath.end(), currentPath.begin(), currentPath.end());
                    nodeAndPath.push_back(node);
                    bfsQueue.push(nodeAndPath);
                }
            }
        }
    }
}

int getBacon(int startNode) {
    int bacon = 0;
    for (int i = 1; i <= ::adjList.size(); i++) {
        if (i != startNode) {
            vector<int> path = bfs(startNode, i);
            bacon += path.size() - 1;
        }
    }
    return bacon;
}

int minBaconPerson() {
    int minBacon = 987654321;
    int minPerson = 0;
    for (int i = 1; i <= ::adjList.size(); i++) {
        if (getBacon(i) < minBacon) {
            minBacon = getBacon(i);
            minPerson = i;
        }
    }
    return minPerson;
}

TEST_CASE("bfs") {
    SECTION("example 1") {
        ::adjList[1] = {3, 4};
        ::adjList[2] = {3};
        ::adjList[3] = {1, 2, 4};
        ::adjList[4] = {1, 3, 5};
        ::adjList[5] = {4};

        // vector<int> path_2_5 = bfs(2, 5);
        // for (auto i: path_2_5) {
        //     cout << i << "\n";
        // }

        REQUIRE(path_2_5.size() == 4);
    }
}

TEST_CASE("getBacon") {
    SECTION("example 1") {
        ::adjList[1] = {3, 4};
        ::adjList[2] = {3};
        ::adjList[3] = {1, 2, 4};
        ::adjList[4] = {1, 3, 5};
        ::adjList[5] = {4};

        REQUIRE(getBacon(1) == 6);
    }
}

TEST_CASE("minBaconPerson") {
    SECTION("example 1") {
        ::adjList[1] = {3, 4};
        ::adjList[2] = {3};
        ::adjList[3] = {1, 2, 4};
        ::adjList[4] = {1, 3, 5};
        ::adjList[5] = {4};

        REQUIRE(minBaconPerson() == 3);
    }
}

int main() {
    int users = 0, relations = 0;
    cin >> users >> relations;

    for (int i = 0; i < relations; i ++) {
        int node1, node2;
        cin >> node1 >> node2;
        ::adjList[node1].push_back(node2);
        ::adjList[node2].push_back(node1);
    }

    cout << minBaconPerson() << "\n";

    return 0;
}
