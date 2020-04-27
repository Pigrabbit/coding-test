// Problem: https://www.acmicpc.net/problem/17142

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define q queue
#define v vector

using namespace std;

const int EMPTY = 0;
const int WALL = 1;
const int VIRUS = 2; // cand of activation
const int ACTIVATED = 4; // activated virus
const int INF = 987654321;

const int MAX_SIZE = 50;
int board[MAX_SIZE + 1][MAX_SIZE + 1];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

v<v<int>> activatedPos;
v<v<int>> virusPos;

int N, M;
int answer = INF;
int numEmpty = 0;
int numVirusCand = 0;

bool isInRange(int y, int x);
int spreadVirus();

bool isInRange(int y, int x) {
	return (y >= 1) && (y <= N) && (x >= 1) && (x <= N);
}

int spreadVirus() {
	int ret = 0;
	int leftEmpty = numEmpty;
	int maxTime = 0;

	// arrival time, state
	v<int> state[MAX_SIZE + 1][MAX_SIZE + 1];
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			state[y][x] = { 0, board[y][x] };
		}
	}

	q<v<int>> bfsQ;
	for (auto p : activatedPos) {
		bfsQ.push(p);
		state[p[0]][p[1]] = { 0, ACTIVATED };
	}
	

	while (!bfsQ.empty()) {
		int cy = bfsQ.front()[0], cx = bfsQ.front()[1];
		bfsQ.pop();
		int cTime = state[cy][cx][0], cState = state[cy][cx][1];

		if (leftEmpty == 0) {
			ret = maxTime;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir], nx = cx + dx[dir];
			// 범위 벗어나는 것 체크
			if (!isInRange(ny, nx)) continue;
			// 벽인 경우
			if (board[ny][nx] == WALL) continue;
			// 이미 visit한 경우
			if (state[ny][nx][0] != 0) continue;
			// 범위 안, 벽 아니고, visit 아직 안 함
			// 빈 칸인 경우
			if (state[ny][nx][1] == EMPTY) {
				// 시간, 상태 update
				state[ny][nx] = { cTime + 1, ACTIVATED };
				bfsQ.push({ ny, nx });
				maxTime = max(maxTime, cTime + 1);
				leftEmpty--;
			}
			// 비활성 바이러스인 경우
			else if (state[ny][nx][1] == VIRUS) {
				state[ny][nx] = { cTime + 1, ACTIVATED };
				bfsQ.push({ ny, nx });
			}
		}
	}

	if (leftEmpty > 0) ret = -1;

	return ret;
}

int main() {
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			if (board[i][j] == EMPTY) numEmpty++;
			if (board[i][j] == VIRUS) {
				numVirusCand++;
				virusPos.push_back({ i, j });
			}
		}
	}
	// end of input

	// use next permutation
	v<int> perm(numVirusCand, 0);
	fill(perm.end() - M, perm.end(), 1);
	do {
		while (!activatedPos.empty()) {
			activatedPos.pop_back();
		}

		for (int j = 0; j < numVirusCand; j++) {
			if (perm[j] == 1) activatedPos.push_back(virusPos[j]);
		}

		int minTime = spreadVirus();
		if (minTime != -1) answer = min(answer, minTime);

	} while (next_permutation(perm.begin(), perm.end()));

	if (answer != INF) cout << answer << "\n";
	else cout << -1 << "\n";
	return 0;
}
