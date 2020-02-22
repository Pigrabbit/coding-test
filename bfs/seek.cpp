// Problem: https://www.acmicpc.net/problem/1697

#include <iostream>
#include <queue>
#include <vector>

const int MAX_POS = 100000;
int dx[3] = {-1, 1};
bool visited[MAX_POS + 1];

std::vector<int> timeConsumed(MAX_POS+1, -1);
std::queue<int> bfsQueue;

void bfs(int pos, int target) {
    if (pos == target) {
        ::timeConsumed[target] = 0;
    } else {
        ::timeConsumed[pos] = 0;
        ::visited[pos] = true;
        ::bfsQueue.push(pos);
        while (!::bfsQueue.empty()){
            int currentPos = bfsQueue.front();
            bfsQueue.pop();
            dx[2] = currentPos;
            for (int i = 0; i < 3; i ++) {
                int newPos = currentPos + dx[i];
                if (newPos >= 0 && newPos <= MAX_POS) {
                    if (visited[newPos] == false && ::timeConsumed[newPos] == -1) {
                        ::bfsQueue.push(newPos);
                        ::timeConsumed[newPos] = ::timeConsumed[currentPos] + 1;
                    }
                }
            }
        }
    }
}

int main() {
    int N = 0, K = 0;
    std::cin >> N >> K;

    bfs(N, K);
    std::cout << timeConsumed[K]  << "\n";
    return 0;
}
