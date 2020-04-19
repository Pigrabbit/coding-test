// Problem: https://www.acmicpc.net/problem/2573

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define vec vector
using namespace std;
const int MAX_HEIGHT = 300, MAX_WIDTH = 300;
const int WATER = 0;
const int LATELY_WATER = -1;

int grid[MAX_HEIGHT][MAX_WIDTH];
bool check[MAX_HEIGHT][MAX_WIDTH];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

bool isInRange(int y, int x, int height, int width) {
	return (y >= 0) && (y < height) && (x >= 0) && (x < width);
}

vec<int> getStartPos(int height, int width) {
    vec<int> startPos;
    bool foundStartPos = false;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (grid[y][x] != WATER) {
				startPos = {y, x};
				foundStartPos = true;
				break;
			}
		}
		if (foundStartPos) break;
	}

    return startPos;
}

// BFS
void meltDownBFS(int height, int width) {
	bool visited[MAX_HEIGHT][MAX_WIDTH];
	memset(visited, false, sizeof(visited));

	// initialize
	queue<vec<int>> bfsQueue;
    vec<int> startPos = getStartPos(height, width);
    bfsQueue.push(startPos);

	while (!bfsQueue.empty()) {
		int curY = bfsQueue.front()[0], curX = bfsQueue.front()[1];
		bfsQueue.pop();
		int &curHeight = grid[curY][curX];

		if (visited[curY][curX]) continue;
		visited[curY][curX] = true;

		for (int i = 0; i < 4; i++) {
			int newY = curY + dy[i], newX = curX + dx[i];
			if (!isInRange(newY, newX, height, width)) continue;
			if (grid[newY][newX] == WATER) {
				if (curHeight > 1) curHeight--;
				else if (curHeight == 1) curHeight = LATELY_WATER;
			}
			else if (grid[newY][newX] != 0 && !visited[newY][newX]) {
				bfsQueue.push({newY, newX});
			}
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (grid[y][x] == LATELY_WATER) {
				grid[y][x] = WATER;
			}
		}
	}
}

// DFS
void checkConnection(vec<int> pos, int height, int width) {
	int y = pos[0], x = pos[1];
	check[y][x] = true;

	for (int i = 0; i < 4; i++) {
		int newY = y + dy[i], newX = x + dx[i];
		if (!isInRange(y, x, height, width)) continue;
		if (!check[newY][newX] && grid[newY][newX] != WATER) {
			vec<int> nextPos = { newY, newX };
			checkConnection(nextPos, height, width);
		}
	}
}

int main() {
	int height, width;
	cin >> height >> width;

	for (int y = 0; y < height; y++) {
		for (int x= 0; x < width; x++) {
			cin >> grid[y][x];
		}
	}

	int count = 0;
	bool isSeparated = false;
	while (true) {
		count++;
		meltDownBFS(height, width);
		// find start pos
		vec<int> startPos = getStartPos(height, width);
		if (startPos.empty()) break;
		memset(check, false, sizeof(check));
		checkConnection(startPos, height, width);

		// check whether it is disconnected
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (grid[y][x] != WATER && check[y][x] == false) {
					isSeparated = true;
					break;
				}
			}
		}
		if (isSeparated) break;
	}
	
	if (isSeparated) cout << count << "\n";
	else cout << 0 << "\n";

	return 0;
}
