// 호텔에 투숙하려는 고객들에게 방을 배정하려 합니다. 
// 호텔에는 방이 총 k개 있으며, 각각의 방은 1번부터 k번까지 번호로 구분하고 있습니다. 
// 처음에는 모든 방이 비어 있으며 스카피는 다음과 같은 규칙에 따라 고객에게 방을 배정하려고 합니다.

// 한 번에 한 명씩 신청한 순서대로 방을 배정합니다.
// 고객은 투숙하기 원하는 방 번호를 제출합니다.
// 고객이 원하는 방이 비어 있다면 즉시 배정합니다.
// 고객이 원하는 방이 이미 배정되어 있으면 원하는 방보다 번호가 크면서 비어있는 방 중 가장 번호가 작은 방을 배정합니다.

// 전체 방 개수 k와 
// 고객들이 원하는 방 번호가 순서대로 들어있는 배열 room_number가 매개변수로 주어질 때, 
// 각 고객에게 배정되는 방 번호를 순서대로 배열에 담아 return 하도록 solution 함수를 완성해주세요.

// sol
// brute-force로 풀 수 있나?
// 간단, room number 배열을 순회하며 원하는 방이 available한자 확인한다.
// 이 때 방 상태(가능/불가능)를 담은 길이 (k+1)의 room 1차원 배열을 돌면서 확인한다.
// time complextiy는 O(k) * O(request) 가 되어 시간내에 solve가 불가능하다.

// DP를 이용해야 할 거 같음
// room_number에 따른 점화식을 세울 수 있나?
// 어떻게 subproblem으로 쪼개지?
// available(i) : i번쨰 방 이후로 가능한 방 번호 중 최솟값을 저장하게 하자.
// 초기화는 모두 자기 방 번호로 한다. (모든 방이 비어있으므로)
// j 번째(j > i) 방에 손님이 투숙하면
// avaiable(j)를 availalbe(j+1) 로 업데이트한다.
// 맨 끝방의 경우 -1로 업데이트 한다.

#include <string>
#include <vector>
#include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

#define ll long long
#define vec vector

using namespace std;

unordered_map<ll, ll> roomAndParent;

void printRoomAndParent() {
    for (auto & room: roomAndParent) {
        cout << "room: " << room.first << ", parent: " << room.second << "\n";
    }
    cout << "\n";
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (int i = 0; i < room_number.size(); i++) {
        ll curRoom = room_number[i];
        vec<ll> toUpdate = {curRoom};

        while (roomAndParent.count(curRoom) != 0) {
            curRoom = roomAndParent[curRoom];
            toUpdate.push_back(curRoom);
        }
        toUpdate.pop_back();

        // empty room found!
        answer.push_back(curRoom);
        roomAndParent[curRoom] = curRoom + 1;

        for (auto room: toUpdate) {
            roomAndParent[room] = curRoom + 1;
        }   
        printRoomAndParent();
    }

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        ll k = 6;
        vec<ll> room_number = {1, 3, 4, 1, 3, 1};
        vec<ll> exp = {1, 3, 4, 2, 5, 6};
        REQUIRE(solution(k, room_number) == exp);
    }
}
