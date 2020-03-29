// 징검다리는 일렬로 놓여 있고 각 징검다리의 디딤돌에는 모두 숫자가 적혀 있으며
//  디딤돌의 숫자는 한 번 밟을 때마다 1씩 줄어듭니다.
// 디딤돌의 숫자가 0이 되면 더 이상 밟을 수 없으며 
// 이때는 그 다음 디딤돌로 한번에 여러 칸을 건너 뛸 수 있습니다.
// 단, 다음으로 밟을 수 있는 디딤돌이 여러 개인 경우
// 무조건 가장 가까운 디딤돌로만 건너뛸 수 있습니다.

// i번째 디딤돌에 도달하는 경우의 수
//     i-1번째를 디디고 한 칸 이동하는 경우
//     i-2번째를 디디고 i-1번째가 0일 때 두 칸 이동하는 경우
//     i-3번째를 디디고 i-2, i-1번째가 0일 때 세 칸 이동하는 경우
//     ...
//     i-k번째를 디디고 i-k+1, ..., i-1번째가 0일 때 k 칸 이동하는 경우

// Brute-force로 풀기
// while(true) 로 반복문 돌리기
// 더 이상 못건너는 상태면 count 반환하고 loop 탈출
// 징검다리 앞에서부터 simulation
// i번째 돌위에 있다면 i+1 부터 i+range까지 건널 수 있는 돌이 있는지 확인
// 있으면 건너고 위치 update
// 끝에 도달하면 count++;
// 끝에 도달하지 못하면 loop 탈출


#include <string>
#include <vector>
#include <limits.h>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;


int solution(vector<int> stones, int k) {
    int answer = 0;
    int numStones = stones.size();
    while (true)
    {
        int pos = 0;
        while (pos <= numStones) {
            bool canMove = false;
            for (int i = pos + 1; i <= min(pos + k, numStones - 1 - k); i++) {
                if (stones[i] == 0) continue;
                stones[i]--;
                pos = i;
                cout << "current pos: " << pos << "\n";
                canMove = true;
                break;
            }
            if(!canMove) break;
        }
        
        if (pos < numStones - 1 - k) break;
    
        answer++;
        continue;
    }
    

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<int> stones = {2, 4, 5, 3, 2, 1, 4, 2, 5, 1};
        int k = 3;
        REQUIRE(solution(stones, k) == 3);
    }
}
