// Problem: https://www.acmicpc.net/problem/15683

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const int MAX_SIZE = 8;

const int EMPTY = 0;
const int TYPE1 = 1;
const int TYPE2 = 2;
const int TYPE3 = 3;
const int TYPE4 = 4;
const int TYPE5 = 5;
const int WALL = 6;

int height, width;
int board[MAX_SIZE + 1][MAX_SIZE + 1];

struct cctv {
	int y;
	int x;
	int type;
};

vector<cctv> cctvPos;
int numCCTV;

int minArea = INF;
int dx[4] = { 0, 0, -1 ,1 };
int dy[4] = { -1, 1, 0, 0 };

vector<vector<int>> type2dir = { { 0, 1 }, { 2, 3 } };
vector<vector<int>> type3dir = { { 0, 3 }, { 1, 3 }, { 1, 2 }, { 0, 2 } };
vector<vector<int>> type4dir = { { 0, 1, 2 }, { 1, 2, 3 }, { 0, 2, 3 }, { 0, 1, 3 } };

bool isInRange(int y, int x) {
	return (y >= 0) && (y < height) && (x >= 0) && (x < width);
}

int getBlindArea() {
	int ret = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (board[y][x] == EMPTY) ret++;
		}
	}
	return ret;
}

void check(int y, int x, int dir, int val) {
	int ny = y, nx = x;
	while (true) {
		ny += dy[dir], nx += dx[dir];
		if (!isInRange(ny, nx)) break;
		if (board[ny][nx] == WALL) break;
		if (board[ny][nx] <= 0) board[ny][nx] += val;
	}
}

void dfs(int idx) {
	if (idx == numCCTV) {
		int blindArea = getBlindArea();
		minArea = min(minArea, blindArea);
		return;
	}

	cctv curCCTV = cctvPos[idx];
	int y = curCCTV.y, x = curCCTV.x;

	if (curCCTV.type == TYPE1) {
		for (int i = 0; i < 4; i++) {
			check(y, x, i, -1);
			dfs(idx + 1);
			check(y, x, i, 1);
		}
	}
	else if (curCCTV.type == TYPE2) {
		for (auto dirSet : type2dir) {
			for (auto i : dirSet) {
				check(y, x, i, -1);
			}
			dfs(idx + 1);
			for (auto i : dirSet) {
				check(y, x, i, 1);
			}
		}
	}
	else if (curCCTV.type == TYPE3) {
		for (auto dirSet : type3dir) {
			for (auto i : dirSet) {
				check(y, x, i, -1);
			}
			dfs(idx + 1);
			for (auto i : dirSet) {
				check(y, x, i, 1);
			}
		}
	}
	else if (curCCTV.type == TYPE4) {
		for (auto dirSet : type4dir) {
			for (auto i : dirSet) {
				check(y, x, i, -1);
			}
			dfs(idx + 1);
			for (auto i : dirSet) {
				check(y, x, i, 1);
			}
		}
	}
	else if (curCCTV.type == TYPE5) {	
		for (int i = 0; i < 4; i++) {
			check(y, x, i, -1);
		}
		dfs(idx + 1);
		for (int i = 0; i < 4; i++) {
			check(y, x, i, 1);
		}
	}
}

int main() {
	cin >> height >> width;
	numCCTV = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cin >> board[y][x];
			if (board[y][x] != EMPTY && board[y][x] != WALL) {
				numCCTV++;
				cctvPos.push_back({ y, x, board[y][x] });
			}
		}
	}

	dfs(0);
	cout << minArea << "\n";

	return 0;
}
