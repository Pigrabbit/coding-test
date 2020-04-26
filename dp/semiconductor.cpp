// Problem: https://www.acmicpc.net/problem/2352
// Reference: https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

#include <iostream> 
#include <vector> 
using namespace std;

// Binary search (note boundaries in the caller) 
int CeilIndex(vector<int>& v, int left, int right, int key)
{
	while (right - left > 1) {
		int mid = left + (right - left) / 2;
		if (v[mid] >= key)
			right = mid;
		else
			left = mid;
	}

	return right;
}

int getLISLength(vector<int>& v)
{
	if (v.size() == 0) return 0;

	vector<int> tail(v.size(), 0);
	int length = 1; // always points empty slot in tail 

	tail[0] = v[0]; // start
	for (size_t i = 1; i < v.size(); i++) {

		// new smallest value => smallest among all end
		if (v[i] < tail[0]) {
			tail[0] = v[i];
		}
		// v[i] extends largest subsequence => v[i] is the largest among all end
		else if (v[i] > tail[length - 1]) {
			tail[length++] = v[i];
		}
		// v[i] will become end candidate of an existing 
		// subsequence or Throw away larger elements in all 
		// LIS, to make room for upcoming grater elements 
		// than v[i] (and also, v[i] would have already 
		// appeared in one of LIS, identify the location 
		// and replace it) 
		else {
			int left = -1, right = length - 1;
			tail[CeilIndex(tail, left, right, v[i])] = v[i];
		}
	}

	return length;
}

int main()
{
	int arrLength = 0;
	cin >> arrLength;
	vector<int> arr(arrLength);

	for (int i = 0; i < arrLength; i++) {
		cin >> arr[i];
	}

	cout << getLISLength(arr) << '\n';
	return 0;
}
