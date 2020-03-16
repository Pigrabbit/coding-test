// Problem: https://www.acmicpc.net/problem/1916

#include <iostream>
#include <map>
#include <limits.h>
#include <queue>
using namespace std;

const int MAX_VERTICE = 1000;
vector<pair<int, int>> graph[MAX_VERTICE + 1];

int dijkstra(int from, int to, int numVertice) {
	priority_queue<pair<int, int>> pqueue;
	vector<int> distances(numVertice + 1, INT_MAX);
	distances[from] = 0;
	pqueue.push(make_pair(0, from));

	while(!pqueue.empty()) {
		int cost = -pqueue.top().first, vertex = pqueue.top().second;
		pqueue.pop();
		
		for (auto neighbor: graph[vertex]) {
			int weight = neighbor.second;
			if (cost + weight < distances[neighbor.first]) {
				distances[neighbor.first] = cost + weight;
				pqueue.push(make_pair(-(cost + weight), neighbor.first));
			}
		}
	}
	return distances[to];
}

void printGraph(int numVertice) {
    for (int i = 1; i <= numVertice; i++) {
        cout << "\nVertex "  << i << "\n";
        for (auto neightbor: graph[i]) {
            cout << "\t(dest, weight): (" << neightbor.first << ", " << neightbor.second << ")\n";
        }
    }
}

int main() {
    int vertice = 0, edges = 0;
    cin >> vertice >> edges;

    for (int i = 0; i < edges; i++) {
        int src = 0, dest = 0, weight = 0;
        cin>> src >> dest >> weight;
        graph[src].push_back(make_pair(dest, weight));
    }

    int from = 0, to = 0;
    cin >> from >> to;

    // printGraph(vertice);
    cout << dijkstra(from, to, vertice) << "\n";

    return 0;
}
