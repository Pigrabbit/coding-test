// Problem: https://www.acmicpc.net/problem/2631

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int MAX_STUDENT = 200;

int order[MAX_STUDENT + 1];
int N;
int cache[MAX_STUDENT + 1];

int main() {
	cin >> N;
	for (int i = 0; i < N ; i++) {
		cin >> order[i];
	}
	// end of input

	// LIS: O(n^2)
	cache[0] = 1;
	for (int i = 1; i <= N; i++) {
		cache[i] = 1;
	}
	
	int longest = 0;
	
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			if (order[j] < order[i]) {
				// 이 element를 LIS에 포함할까 말까
				int tmp = cache[j] + 1;
				cache[i] = max(cache[i], tmp);
			}
			longest = max(longest, cache[i]);
		}
	}
	
	cout << N - longest << "\n";

	// LIS: O(nlogn)
	vector<int> v = { order[0] };
	for (int i = 1; i < N; i++) {
		if (order[i] > v.back()) v.push_back(order[i]);
		else {
			auto it = lower_bound(v.begin(), v.end(), order[i]);
			*it = order[i];
		}
	}

	cout << N - v.size() << "\n";

	return 0;
}

