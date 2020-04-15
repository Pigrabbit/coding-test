// Problem: https://www.acmicpc.net/problem/17471

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define vec vector
using namespace std;

const int MAX_N = 10;
int population[MAX_N + 1];
int answer = 987654321;

bool visited[MAX_N + 1];

vec<vec<int>> adjList(MAX_N + 1);

void dfs(vec<int> & district, int cur) {
	visited[cur] = true;

	for (int i = 0; i < district.size(); i++) {
		vec<int> neighbor = adjList[cur];

		for (int j = 0; j < neighbor.size(); j++) {
			if (visited[neighbor[j]] == false && \
            (find(district.begin(), district.end(), neighbor[j]) != district.end())) {
				dfs(district, neighbor[j]);
			}
		}
	}
}

bool isValid(vec<int> & district) {
	bool ret = true;
	int numArea = district.size();
	// visited 초기화
	memset(visited, false, sizeof(visited));

	// 선거구 안에 있는 모든 구역들이 방문 가능한지 여부를 확인해야 함.
	// dfs를 돌리고 visited에 false가 있는지 확인하자.
	int start = district[0];
	dfs(district, start);
	for (auto d : district) {
        if (visited[d] == false) {
            ret = false;
        }
    }	
	return ret;
}

int getDifference(vec<int> & districtA, vec<int> & districtB) {
	int popA = 0, popB = 0;
	for (auto area : districtA) 
		popA += population[area];
	
	for (auto area : districtB) 
		popB += population[area];
	
	return abs(popA - popB);
}

int main() {
	int numArea = 0;
	cin >> numArea;
	for (int i = 1; i <= numArea; i++) 
		cin >> population[i];
	

	for (int j = 1; j <= numArea; j++) {
		int numNeighbors = 0;
		cin >> numNeighbors;
		vec<int> neighbors(numNeighbors);

		for (int i = 0; i < numNeighbors; i++) {
			cin >> neighbors[i];
		}
		adjList[j] = neighbors;
	}

	// brute force
	for (int i = 1; i < numArea; i++) {
		vec<int> perm(numArea, 0);
		fill(perm.end() - i, perm.end(), 1);
		do {
			vec<int> districtA, districtB;
			// A, B 선거구에 포함시킬 구역들 결정하기.
			for (int j = 0; j < perm.size(); j++) {
				if (perm[j] == 1) districtA.push_back(j + 1);
				else districtB.push_back(j + 1);
			}
			// 각각이 valid 한지 확인
			// 둘 다 valid하다면 인구 차이 계산
			if (isValid(districtA) && isValid(districtB)) {
				int diff = getDifference(districtA, districtB);
				answer = min(answer, diff);
			}
		} while (next_permutation(perm.begin(), perm.end()));
	}

	if (answer != 987654321) cout << answer << "\n";
	else cout << -1 << "\n";

	return 0;
}
