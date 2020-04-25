// Problem: https://www.acmicpc.net/problem/17472

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

#define v vector

using namespace std;

const int LAND = 1;
const int WATER = 0;

const int MAX_GROUPS = 6;
const int MAX_SIZE = 10;

pair<int, int> board[MAX_SIZE + 1][MAX_SIZE + 1];
bool visited[MAX_GROUPS + 1];
v<v<int>> adjList(MAX_GROUPS + 1);

struct bridge {
    int fromIsland;
    int toIsland;
    int len;
};

v<bridge> candBridge;

int height, width;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int answer = 987654321;

v<int> findEndPoint(int y, int x, int curIsland, int dir) {
    int nY = y + dy[dir], nX = x + dx[dir];
    int len = 0;
    int destIsland = 0;
    while (nY >= 1 && nY <= height && nX >= 1 && nX <= width) {
        if (board[nY][nX].first != WATER) {
            destIsland = board[nY][nX].second;
            break;
        }
        nY += dy[dir], nX += dx[dir];
        len++;
    }

    if (len < 2 || destIsland == 0 || destIsland == curIsland) return {-1, -1, -1, -1};
    return {nY, nX, destIsland, len};
}

void buildBridges(int numIsland) {
    // step 1. choose island => 시작할 island는 어떻게 정할까 이중 for loop?
    // step 2. search possible bridge
       // 2-1. 다른 섬까지 연결되는지 확인(가로, 세로 only)
       // 2-2. 길이 2이상인지 확인.
    // step 3. candBridge에 저장
       // 3-1. 시작 island, 도착 island, 길이
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (board[y][x] == make_pair(WATER, 0)) continue;
            int curIsland = board[y][x].second;
            for (int dir = 0; dir < 4; dir++) {
                v<int> endPoint = findEndPoint(y, x, curIsland, dir);
                if (endPoint[0] == -1) continue;
                bridge newBridge = {curIsland, endPoint[2], endPoint[3]};

                // search duplicate
                bool hasDulplicate = false;
                for (int i = 0; i < candBridge.size(); i++) {
                    if (candBridge[i].fromIsland == newBridge.toIsland &&\
                    candBridge[i].toIsland == newBridge.fromIsland &&\
                    candBridge[i].len == newBridge.len) {
                        hasDulplicate = true;
                        break;
                    }
                }
                if (hasDulplicate) continue;

                candBridge.push_back(newBridge);
            }
        }
    }
}

void dfs(int here) {
    visited[here] = true;
    for (int i = 0; i < adjList[here].size(); i++) {
        int there = adjList[here][i];
        if (!visited[there]) dfs(there);
    }
}

void dfsAll(int numIsland) {
    memset(visited, false, sizeof(visited));
    dfs(1);
}


int main() {
    cin >> height >> width;

    v<pair<int, int>> landPos;
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            cin >> board[y][x].first;
            board[y][x].second = 0;
            if (board[y][x].first == LAND) landPos.push_back(make_pair(y, x));
        }
    }

    // TODO: grouping
    int groupIdx = 1;
    bool checked[MAX_SIZE + 1][MAX_SIZE + 1];
    memset(checked, false, sizeof(checked));
    
    while (groupIdx <= MAX_GROUPS && !landPos.empty()) {
        queue<pair<int, int>> bfsQueue;
        int startY = landPos.front().first, startX = landPos.front().second;
        landPos.erase(landPos.begin());
        bfsQueue.push(make_pair(startY, startX));
        board[startY][startX].second = groupIdx;

        while (!bfsQueue.empty()) {
            int curY = bfsQueue.front().first, curX = bfsQueue.front().second;
            bfsQueue.pop();
            checked[curY][curX] = true;

            for (int i = 0; i < 4; i++) {
                int nY = curY + dy[i], nX = curX + dx[i];

                if (nY < 1 | nY > height | nX < 1 | nX > width) continue;
                if (checked[nY][nX]) continue;

                if (board[nY][nX] == make_pair(LAND, 0)) {    
                    auto it = find(landPos.begin(), landPos.end(), make_pair(nY, nX));
                    if (it == landPos.end()) continue; 
                    landPos.erase(it);

                    board[nY][nX].second = groupIdx;
                    bfsQueue.push(make_pair(nY, nX));
                } 
            }
            // end of bfs
        }
        groupIdx++;
    }

    // TODO: brute force to build 
    int numIsland = groupIdx - 1;
    buildBridges(numIsland);

    // TODO: find min
    // use permutation
    int numBridges = candBridge.size();
    
    v<int> perm(numBridges);
    for (int i = 1; i <= numBridges; i++) {
        fill(perm.end() - i, perm.end(), 1);
        do {
            // clear adjList
            for (int j = 1; j <= numIsland; j++) {
                while(!adjList[j].empty()) {
                    adjList[j].pop_back();
                }
            }

            // choose bridges to build
            v<bridge> chosenBridge;
            int curLen = 0;
            for (int j = 0; j < numBridges; j++) {
                if (perm[j] == 1) chosenBridge.push_back(candBridge[j]);
            }

            // record connected status
            for (auto b: chosenBridge) {
                adjList[b.fromIsland].push_back(b.toIsland);
                adjList[b.toIsland].push_back(b.fromIsland);
                curLen += b.len;
            }

            // check connectivity
            dfsAll(numIsland);

            bool isConnected = true;
            for (int j = 1; j <= numIsland; j++) {
                if (visited[j] == false) {
                    isConnected = false;
                    break;
                } 
            }

            if (!isConnected) continue;
            answer = min(answer, curLen);

        } while (next_permutation(perm.begin(), perm.end()));
    }

    if (answer != 987654321) cout << answer << "\n";
    else cout << -1 << "\n";

    return 0;
}
