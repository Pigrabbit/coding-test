// Problem: https://www.acmicpc.net/problem/2178

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
// #define CATCH_CONFIG_MAIN
// #include "../lib/catch.hpp"

using namespace std;

const int MAX_LENGTH = 100;

int bfs(vector<list<pair<int, int>>> graph, int startX, int startY, int targetX, int targetY) {
    pair<int, int> startVertex = make_pair(startX, startY);
    pair<int, int> targetVertex = make_pair(targetX, targetY);
    vector<pair<int, int>> visited = {startVertex};

    queue<pair<int, int>> bfsQueue;
    bfsQueue.push(startVertex);
    
    int distance[targetX][targetY];
    distance[0][0] = 1;

    while (!bfsQueue.empty()) {
        pair<int, int> currentVertex = bfsQueue.front();
        bfsQueue.pop();
        cout << "current vertex: (" << currentVertex.first << ", " << currentVertex.second << ") \n";
        visited.push_back(currentVertex);
        cout << "\tcurrent distance: " << distance[currentVertex.first-1][currentVertex.second-1] << "\n";

        for (vector<list<pair<int, int>>>::iterator it = graph.begin(); it != graph.end(); ++it) {
            list<pair<int, int>> verticeList = *it;
            for (list<pair<int, int>>::iterator listIt = verticeList.begin(); listIt != verticeList.end(); ++listIt) {
                pair<int, int> vertex = *listIt;
                if (listIt == verticeList.begin() && vertex != currentVertex) {
                    break;
                } else if (listIt != verticeList.begin() && find(visited.begin(), visited.end(), vertex) == visited.end()) {
                    if (vertex == targetVertex) {
                        // check base case
                        cout << "found the target!";
                        return distance[currentVertex.first-1][currentVertex.second-1] + 1;
                    } else {
                        cout << "\tadding the neighbor vertex to bfs queue... (" << vertex.first << ", " << vertex.second << ")\n";
                        distance[vertex.first-1][vertex.second-1] = distance[currentVertex.first-1][currentVertex.second-1] + 1; 
                        bfsQueue.push(vertex);
                    }
                }
            }
        }
    }
    
    return 0;
}

bool isValidCoordinate(int curX, int curY, int borderX, int borderY) {
    return curX >= 1 && curX <= borderX && curY >= 1 && curY <= borderY;
}

vector<list<pair<int, int>>> buildGraph(string strInput [], int rows, int cols) {
    // current vertex coordiante at index 0
    // adjacent vertices from index 1
    // {{curX, curY}, {adj1X, adj1Y}, {adj2X, adj2Y}, ...}
    vector<list<pair<int, int>>> adjacencyList;

    // left, right, up, down
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            list<pair<int, int>> coordinates;

            pair<int, int> currentVertex = make_pair(i, j);
            coordinates.push_back(currentVertex);

            char currentVal = strInput[i-1].at(j-1);

            if (currentVal == '1') {
                // look around
                for (int k = 0; k < 4; k++) {
                    int neighborX = i + dx[k];
                    int neighborY = j + dy[k];
                    // check the coordinate is in valid range
                    if (isValidCoordinate(neighborX, neighborY, rows, cols)) {
                        pair<int, int> neighborVertex = make_pair(neighborX, neighborY);
                        char neighborVal = strInput[neighborX-1].at(neighborY-1);
                        if (neighborVal == '1') {
                            // add an edge
                            coordinates.push_back(neighborVertex);
                        }
                    }
                }
            }
            adjacencyList.push_back(coordinates);
        }
    }

    return adjacencyList;
}

void printAdjList(vector<list<pair<int, int>>> adjList) {
    for (vector<list<pair<int, int>>>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
        list<pair<int, int>> verticeList = *it;
        for (list<pair<int, int>>::iterator listIt = verticeList.begin(); listIt != verticeList.end(); ++listIt) {
            pair<int, int> coordinate = *listIt;
            if (listIt == verticeList.begin()) {
                cout << "Current vertex coordinate: (" << coordinate.first << ", " << coordinate.second <<") \n";
            } else {
                cout << "\tNeighbor vertex coordinate: (" << coordinate.first << ", " << coordinate.second <<") \n";
            }
        }
    }   
}

int main() {
    int rows = 0, cols = 0;
    cin >> rows >> cols;

    string maze[MAX_LENGTH + 2];

    for (int i = 0; i < rows; i++) {
        cin >> maze[i];
    }

    vector<list<pair<int, int>>> graph = buildGraph(maze, rows, cols);
    printAdjList(graph);

    cout << bfs(graph, 1, 1, rows, cols) << "\n";
}
