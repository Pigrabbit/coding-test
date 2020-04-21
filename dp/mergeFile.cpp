// Problem: https://www.acmicpc.net/problem/11066

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_FILES = 500;
const int INF = 987654321;
int cache[MAX_FILES+1][MAX_FILES+1];
int pages[MAX_FILES+1];
int accumulate[MAX_FILES+1];

int getMergeCost(int start, int end)
{
	if (start == end) return 0; // base case
    int & ret = cache[start][end];
	if (ret != -1) return cache[start][end]; // memoization

	int localMin = INF;
	for (int mid = start; mid < end; mid++) {
		int tmp1 = getMergeCost(start, mid);
		int tmp2 = getMergeCost(mid + 1, end);
		localMin = min(localMin, tmp1 + tmp2);
	}

	int localSum = accumulate[end] - accumulate[start - 1];

	return ret = localMin + localSum;
}

int main()
{
	int numTestCase;
	cin >> numTestCase;
	for (int i = 0; i < numTestCase; i++) {
        memset(cache, -1, sizeof(cache));
		int n;
		cin >> n;
		for (int j = 1; j <= n; j++) {
			cin>> pages[j];
		}
		
		accumulate[0] = 0;
		for (int j = 1; j <= n; j++) {
			accumulate[j] = accumulate[j - 1] + pages[j];
		}

		getMergeCost(1, n);
        cout << cache[1][n] << "\n";
	}

	return 0;
}


