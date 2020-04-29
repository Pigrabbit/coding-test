// Problem: https://www.acmicpc.net/problem/1931

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> meetingSchedule;

int main() {
    int numMeeting = 0;
    cin >> numMeeting;

    for (int i = 0; i < numMeeting; i++) {
        vector<int> schedule(2);
        cin >> schedule[1] >> schedule[0];
        meetingSchedule.push_back(schedule);
    }

    sort(meetingSchedule.begin(), meetingSchedule.end());

    int curEnd = meetingSchedule[0][0], count = 1;
    
    for (int i = 1; i < numMeeting; i++) {
        if (meetingSchedule[i][1] >= curEnd) {
            curEnd = meetingSchedule[i][0];
            count++;
            continue;
        }
    }

    cout << count << "\n";

    return 0;
}
