// Problem: https://www.acmicpc.net/problem/17136

#include <iostream>
#include <vector>
#include <cstring>

#define vec vector

using namespace std;

const int HEIGHT = 10, WIDTH = 10;
int board[HEIGHT][WIDTH];

const int EMPTY = 0;
const int TO_PASTE = 1;
const int PASTED = 2;

vec<int> invalidPos = {-1, -1};
int answer = 987654321;

vec<int> getNextPosToPaste() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x] == TO_PASTE) return {y, x};
        }
    }
    return invalidPos;
}

void dfs(vec<int> & usedPaper) {
    // Base Case 1: 종이를 다 소진한 경우
    for (auto paper: usedPaper) {
        if (paper > 5) {
            return;
        }
    }
    // Base Case 2: 다 덮인 경우
    vec<int> nextPos = getNextPosToPaste();
    if (nextPos == invalidPos) {
        int count = 0;
        for (auto paper: usedPaper) {
            count += paper;
        }
        answer = min(answer, count);
        return;
    }

    // simulation here
    // 붙인 다음 다시 띄기
    int nextY = nextPos[0], nextX = nextPos[1];

    for (int size = 5; size >= 1; size--) {
        // 경계넘어가는지 확인
        if (nextY + size > HEIGHT || nextX + size > WIDTH) continue;
        // 덮을 공간에 1말고 다른게있는지 확인
        bool canPaste = true;
        for (int y = nextY; y < nextY + size; y++) {
            for (int x = nextX; x < nextX + size; x++) {
                if (board[y][x] != TO_PASTE) {
                    canPaste = false;
                    break;
                }
            }
        }

        if (canPaste) {
            // paste
            for (int y = nextY; y < nextY + size; y++) {
                for (int x = nextX; x < nextX + size; x++) {
                    board[y][x] = PASTED;
                }
            }
            usedPaper[size-1]++;
            dfs(usedPaper);
            // undo
            usedPaper[size-1]--;
            for (int y = nextY; y < nextY + size; y++) {
                for (int x = nextX; x < nextX + size; x++) {
                    board[y][x] = TO_PASTE;
                }
            }
        }
    }
}

int main() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0 ; x < WIDTH; x++) {
            cin >> board[y][x];
        }
    }

    vec<int> usedPaper = {0, 0, 0, 0, 0};
    dfs(usedPaper);
    if (answer != 987654321)
        cout << answer << "\n";
    else
        cout << -1 << "\n";

    return 0;
}
