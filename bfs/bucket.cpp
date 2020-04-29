#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> getCases(int A, int B, int C) {
    vector<int> ret;
    ret.push_back(C);

    queue<vector<int>> bfsQueue;
    bool checked[A + 1][B + 1][C + 1];
    memset(checked, false, sizeof(checked));
    checked[0][0][C] = true;

    vector<int> status = {0, 0, C};
    bfsQueue.push(status);

    while(!bfsQueue.empty()) {
        int curA = bfsQueue.front()[0], curB = bfsQueue.front()[1], curC = bfsQueue.front()[2];
        // cout << "current status A: " << curA << ", B: " << curB << ", C: " << curC << "\n";
        bfsQueue.pop();
        if (curA == 0 && find(ret.begin(), ret.end(), curC) == ret.end()) ret.push_back(curC);

        int capA = 0, capB = 0, capC = 0;
        for (int i = 0; i < 6; i++) {
            bool isMoved = false;
            switch (i)
            {
            // 0: A -> B 
            case 0:
                if (curA == 0) break;
                capB = B - curB;
                if (curA >= capB && !checked[curA - capB][curB + capB][curC]) {
                    checked[curA - capB][curB + capB][curC] = true;
                    vector<int> newStatus = {curA - capB, curB + capB, curC};
                    bfsQueue.push(newStatus);
                }
                else if (curA < capB && !checked[0][curB + curA][curC]) {
                    checked[0][curB + curA][curC] = true;
                    vector<int> newStatus = {0, curB + curA, curC};
                    bfsQueue.push(newStatus);
                }
                break;
            // 1: A -> C
            case 1:
                if (curA == 0) break;
                capC = C - curC;
                if (curA >= capC && !checked[curA - capC][curB][curC + capC]) {
                    checked[curA - capC][curB][curC + capC] = true;
                    vector<int> newStatus = {curA - capC, curB, curC + capC};
                    bfsQueue.push(newStatus);
                }
                else if (curA < capC && !checked[0][curB][curC + curA]) {
                    checked[0][curB][curC + curA] = true;
                    vector<int> newStatus = {0, curB, curC + curA};
                    bfsQueue.push(newStatus);
                }
                break;
            // 2: B -> A
            case 2:
                if (curB == 0) break;
                capA = A - curA;
                if (curB >= capA && !checked[A][curB - capA][curC]) {
                    checked[A][curB - capA][curC] = true;
                    vector<int> newStatus = {A, curB - capA, curC};
                    bfsQueue.push(newStatus);
                }
                else if (curB < capA && !checked[curA + curB][0][curC]) {
                    checked[curA + curB][0][curC] = true;
                    vector<int> newStatus = {curA + curB, 0, curC};
                    bfsQueue.push(newStatus);
                }
                break;
            // 3: B -> C
            case 3:
                if (curB == 0) break;
                capC = C - curC;
                if (curB >= capC && !checked[curA][curB - capC][C]) {
                    checked[curA][curB - capC][C] = true;
                    vector<int> newStatus = {curA, curB - capC, C};
                    bfsQueue.push(newStatus);
                }
                else if (curB < capC && !checked[curA][0][curC + curB]) {
                    checked[curA][0][curC + curB] = true;
                    vector<int> newStatus = {curA, 0, curC + curB};
                    bfsQueue.push(newStatus);
                }
                break;
            // 4: C -> A
            case 4:
                if (curC == 0) break;
                capA = A - curA;
                if (curC >= capA && !checked[A][curB][curC - capA]) {
                    checked[A][curB][curC - capA] = true;
                    vector<int> newStatus = {A, curB, curC - capA};
                    bfsQueue.push(newStatus);
                }
                else if (curC < capA && !checked[curA + curC][curB][0]) {
                    checked[curA + curC][curB][0] = true;
                    vector<int> newStatus = {curA + curC, curB, 0};
                    bfsQueue.push(newStatus);
                }
                break;
            // 5: C -> B    
            case 5:
                if (curC == 0) break;
                capB = B - curB;
                if (curC >= capB && !checked[curA][B][curC - capB]) {
                    checked[curA][B][curC - capB] = true;
                    vector<int> newStatus = {curA, B, curC - capB};
                    bfsQueue.push(newStatus);
                }
                else if (curC < capB && !checked[curA][curB + curC][0]) {
                    checked[curA][curB + curC][0] = true;
                    vector<int> newStatus = {curA, curB + curC, 0};
                    bfsQueue.push(newStatus);
                }
                break;        
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

TEST_CASE("getCases") {
    SECTION("example 1") {
        int A = 8, B = 9, C = 10;
        vector<int> exp = {1, 2, 8, 9 ,10};
        REQUIRE(getCases(A, B, C) == exp);
    }
}

int main() {
    int A = 0, B = 0, C = 0;
    cin >> A >> B >> C;

    vector<int> answer = getCases(A, B, C);
    for(auto num: answer)
        cout << num << " ";
    cout << "\n";

    return 0;
}
