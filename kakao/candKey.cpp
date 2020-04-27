// Problem: https://programmers.co.kr/learn/courses/30/lessons/42890

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

#define um unordered_map

using namespace std;

bool isUnique(vector<vector<string>> &relation, vector<int> columnIdx, int numRows) {
	bool ret = true;
	int numKeys = columnIdx.size();
	um<string, int> occuerence;

	for (int i = 0; i < numRows; i++) {
		string curTuple;

		for (int j = 0; j < numKeys; j++) {
			curTuple += relation[i][columnIdx[j]];
		}

		if (occuerence.count(curTuple) > 0) {
			ret = false;
			break;
		}
		else occuerence[curTuple] = 1;
	}
	
	return ret;
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	int numRows = relation.size(), numCols = relation[0].size();
	vector<vector<int>> candKeys;

	for (int k = 1; k <= numCols; k++) {
		// k개 만큼 고르기 => perm
		vector<int> perm(numCols, 0);
		fill(perm.end() - k, perm.end(), 1);

		do {
			vector<int> candKeyIdx;
			for (int j = 0; j < numCols; j++) {
				if (perm[j] == 1) candKeyIdx.push_back(j);
			}

			if (isUnique(relation, candKeyIdx, numRows)) {
				// 최소성 검사
				bool hasMinimality = true;

				for (auto key: candKeys) {
					vector<int> v(key.size(), -1);
					set_intersection(key.begin(), key.end(), candKeyIdx.begin(), candKeyIdx.end(), v.begin());

					if (v == key) {
						hasMinimality = false;
						break;
					}
				}

				if (hasMinimality) candKeys.push_back(candKeyIdx);
			}
		} while (next_permutation(perm.begin(), perm.end()));

	}

	answer = candKeys.size();
	return answer;
}

