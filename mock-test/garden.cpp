#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int EMPTY = 0;
const int GREEN = 1;
const int RED = 2;
const int FLOWER = 3;

const int MAX_HEIGHT = 50, MAX_WIDTH = 50, MAX_SEED = 10;
int ground[MAX_HEIGHT + 1][MAX_WIDTH + 1];

int height, width, green, red;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

vector<vector<int>> candidates;
int candidateSize;
int brute[10];

bool isInRange(int y, int x) {
    return (y > 0) && (y <= height) && (x > 0) && (x <= width);
}

int spreadBFS() {
    queue<vector<int>> bfsQueue;
    vector<int> state[52][52]; // arrival time, color
    for (int i = 0; i < 52; i++) {
        for (int j = 0; j< 52; j++) {
            state[i][j] = {0, 0};
        }
    }
    int flowers = 0;

    for (int i = 0; i < candidateSize; i++) {
        if (brute[i] == GREEN || brute[i] == RED) {
            int candY = candidates[i][0], candX = candidates[i][1];
            state[candY][candX] = {0, brute[i]};
            bfsQueue.push(candidates[i]);
        }
    }

    while(!bfsQueue.empty()) {
        int curY = bfsQueue.front()[0], curX = bfsQueue.front()[1];
        bfsQueue.pop();

        int currentTime = state[curY][curX][0], curStatus = state[curY][curX][1];
        if (curStatus == FLOWER) continue;

        for (int dir = 0; dir < 4; dir++) {
            int newX = curX + dx[dir], newY = curY + dy[dir];

            if (!isInRange(newY, newX)) continue;

            if (ground[newY][newX] == 0) continue;

            if (state[newY][newX][1] == EMPTY) {
                state[newY][newX] = {currentTime + 1, curStatus};
                bfsQueue.push({newY, newX});
            } 
            else if (state[newY][newX][1] == RED) {
                if (curStatus == GREEN  && state[newY][newX][0] == currentTime + 1) {
                    flowers++;
                    state[newY][newX][1] = FLOWER;
                }
            } 
            else if (state[newY][newX][1] == GREEN) {
                if (curStatus == RED && state[newY][newX][0] == currentTime + 1) {
                    flowers++;
                    state[newY][newX][1] = FLOWER;
                }
            }
        }
    }

    return flowers;
}


int main() {
    cin >> height >> width >> green >> red;
    
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            cin >> ground[y][x];
            if (ground[y][x] == 2) {
                candidates.push_back({y, x});
            }
        }
    }
    candidateSize = candidates.size();
    fill(brute + candidateSize - green - red, brute + candidateSize - red, GREEN);
    fill(brute + candidateSize - red, brute + candidateSize, RED);

    int maxFlower = 0;
    // permutation
    do {
        maxFlower = max(maxFlower, spreadBFS());
    } while (next_permutation(brute, brute + candidateSize));

    cout << maxFlower << "\n";

    return 0;
}
