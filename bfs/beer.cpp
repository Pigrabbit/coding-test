// Problem: https://www.acmicpc.net/problem/9205

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define v vector
#define q queue

using namespace std;
const int MAX_CU = 100;

v<v<int>> cuPos(MAX_CU + 1);
v<int> home(2, 0);
v<int> festival(2, 0);

int numCU;
int numTC;

int getDist(int fromY, int fromX, int toY, int toX) {
	return abs(fromY - toY) + abs(fromX - toX);
}

int main() {
	cin >> numTC;
	while (numTC--) {
		cin >> numCU;
		cin >> home[0] >> home[1];
		for (int i = 0; i < numCU; i++) {
			v<int> pos(2, 0);
			cin >> pos[0] >> pos[1];
			cuPos[i] = pos;
		}
		cin >> festival[0] >> festival[1];
		// end of input

		// BFS
		bool isHappy = false;
		bool visited[MAX_CU + 1];
		memset(visited, false, sizeof(visited));

		q<v<int>> bfsQ;
		bfsQ.push({home[0], home[1], -1});

		while (!bfsQ.empty()) {
			int cy = bfsQ.front()[0], cx = bfsQ.front()[1], cIdx = bfsQ.front()[2];
			bfsQ.pop();
			if (cIdx != -1) visited[cIdx] = true;
			if (getDist(cy, cx, festival[0], festival[1]) <= 1000) {
				isHappy = true;
				break;
			}

			for (int i = 0; i < numCU; i++) {
				if (visited[i]) continue;
				if (getDist(cy, cx, cuPos[i][0], cuPos[i][1]) <= 1000) {
					// 가지고 있는 맥주로 도달 할 수 있는 편의점
					bfsQ.push({ cuPos[i][0], cuPos[i][1], i });
				}
			}
		}
		if (isHappy) cout << "happy\n";
		else cout << "sad\n";
	}
    
	return 0;
}
