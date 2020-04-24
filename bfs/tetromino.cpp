// Problem: https://www.acmicpc.net/problem/14500

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define v vector

using namespace std;

const int MAX_SIZE = 500;
const int CHECKED = 2;
const int INCLUDED = 1;
const int NOT_INCLUDED = 0;

int N, M;
int grid[MAX_SIZE+1][MAX_SIZE+1];
int state[MAX_SIZE+1][MAX_SIZE+1];
int answer = 0;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

v<pair<int, int>> tetroPos;

bool isInRange(int y, int x) {
    return (y >= 1) && (y <= N) && (x >= 1) && (x <= M);
}

int sumUp() {
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        ret += grid[tetroPos[i].first][tetroPos[i].second];
    }
    return ret;
}

void checkTpiece(int y, int x) {
    // ㅗ, ㅜ, ㅓ, ㅏ 순으로 check
    // ㅗ shape
    if (isInRange(y - 1, x) && isInRange(y, x -1) && isInRange(y, x+1)) {
        answer = max(answer, grid[y][x] + grid[y-1][x] + grid[y][x-1] + grid[y][x+1]);
    }
    // ㅜ shape
    if (isInRange(y + 1, x) && isInRange(y, x -1) && isInRange(y, x+1)) {
        answer = max(answer, grid[y][x] + grid[y+1][x] + grid[y][x-1] + grid[y][x+1]);
    }
    // ㅓ shape
    if (isInRange(y , x-1) && isInRange(y-1, x) && isInRange(y+1, x)) {
        answer = max(answer, grid[y][x] + grid[y][x-1] + grid[y-1][x] + grid[y+1][x]);
    }
    // ㅏ shape
    if (isInRange(y, x + 1) && isInRange(y-1, x) && isInRange(y+1, x)) {
        answer = max(answer, grid[y][x] + grid[y][x+1] + grid[y-1][x] + grid[y+1][x]);
    }
}

// back tracking
void dfs(int y, int x, int count) {
    if (count == 4) {
        answer = max(answer, sumUp());
        return;
    }

    if (count == 0) {
        // select start pos
        for (int i = 1; i <= N; i++) {
            for (int j =1; j <= M; j++) {
                state[i][j] = INCLUDED;
                tetroPos.push_back(make_pair(i, j));
                dfs(i, j, count + 1);
                checkTpiece(i, j);
                state[i][j] = NOT_INCLUDED;
                tetroPos.pop_back();
            }
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            int nY = y + dy[i], nX = x + dx[i];

            if (!isInRange(nY, nX)) continue;

            if (state[nY][nX] == INCLUDED || state[nY][nX] == CHECKED) continue;

            state[nY][nX] = INCLUDED;
            tetroPos.push_back(make_pair(nY, nX));
            dfs(nY, nX, count + 1);
            state[nY][nX] = NOT_INCLUDED;
            tetroPos.pop_back();
        }
    }
}

int main() {
    cin >> N >> M;

    for (int y = 1 ; y <= N; y++ ) {
        for (int x = 1; x <= M; x++) {
            cin >> grid[y][x];
        }
    }

    memset(state, NOT_INCLUDED, sizeof(state));
    dfs(0, 0, 0);

    // find anawer
    cout << answer << "\n";
    return 0;
}
