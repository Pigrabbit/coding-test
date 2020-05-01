// Problem: https://programmers.co.kr/learn/courses/30/lessons/60062

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>

#define v vector

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = -1;
	int numWeakWall = weak.size(), numFriends = dist.size(), len = n;

	// sort dist array
	sort(dist.begin(), dist.end(), [](const int & lhs, const int & rhs) {
		return lhs > rhs; 
	});

	// 몇 명 보낼건지 결정
	for (int i = 1; i <= numFriends; i++) {
		// 누구 보낼건지 결정: greedy로 dist의 앞에서부터 i명 보낸다.
		v<int> perm(i, 0);
		copy(dist.begin(), dist.begin() + i, perm.begin());
		
        // 누구부터 보낼건지 permutation
		sort(perm.begin(), perm.end());
		do {
			// 출발할 위치 고르기
			for (auto it = weak.begin(); it != weak.end(); ++it) {
				auto leftSize = distance(weak.begin(), it);

                // 출발할 위치 기준 시계방향 점검할 위치: right
                // 출발할 위치 기준 반시계방향 점검할 위치: left
				deque<int> left(leftSize, 0), right(numWeakWall - leftSize, 0);
				copy(weak.begin(), it, left.begin());
				copy(it, weak.end(), right.begin());

                // circular 이므로 left에 n 만큼 더한뒤 right와 concat
				for (auto l : left) {
					right.push_back(l + n);
				}

                // 점검 simulation
				v<int> friends = perm;
				while (!right.empty() && !friends.empty()) {
					int curPos = right.front(), d = friends.front();
					right.pop_front();
                    friends.erase(friends.begin());
					int checkEnd = curPos + d;

					while (!right.empty() && right.front() <= checkEnd)
						right.pop_front();
				}

				if (right.empty()) return answer = i;
			}

		} while (next_permutation(perm.begin(), perm.end()));
        
	}

	return answer;
}
