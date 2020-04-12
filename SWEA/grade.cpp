// Problem: 1983

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <cstdio>

#define vec vector
#define um unordered_map

using namespace std;

um<int, string> gradeToStr = {
    {0, "A+"},
    {1, "A0"},
    {2, "A-"},
    {3, "B+"},
    {4, "B0"},
    {5, "B-"},
    {6, "C+"},
    {7, "C0"},
    {8, "C-"},
    {9, "D0"}
};

double getTotal(int mid, int final, int assignment) {
    return 0.35 * mid + 0.45 * final + 0.2 * assignment;
}
int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int numStudents = 0, studentToQuery = 0;
        cin >> numStudents >> studentToQuery;

        // vec<vec<double>> scores(numStudents);
        vec<pair<double,int>> scores(numStudents);
        int mid = 0, final = 0, assignment = 0;
        
        for (int i = 0; i < numStudents; i++) {
            cin >> mid >> final >> assignment;
            scores[i] = make_pair(getTotal(mid, final, assignment), i + 1);
        }

        sort(scores.begin(), scores.end());

        int rank = 0;
        for (auto it = scores.begin(); it != scores.end(); it++) {
            if((*it).second == studentToQuery) {
                rank = numStudents - distance(scores.begin(), it);
                break;
            }
        }
        
        int range = numStudents / 10;
        int grade = 0;
        while (rank > range) {
            grade++;
            rank -= range;
        }

        cout << "#" << test_case << " " << ::gradeToStr[grade] << "\n";
	}
	return 0;
}
