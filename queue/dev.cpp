// Problem: https://programmers.co.kr/learn/courses/30/lessons/42586

#include <string>
#include <vector>
#include <deque>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int features = progresses.size();
    deque<int> schedule(features, -1);
    
    for (int i = 0; i < features; i++) {
        int curProgress = progresses[i], curSpeed = speeds[i], days = 0;
        while (curProgress < 100) {
            curProgress += curSpeed;
            days++;
        }
        schedule[i] = days;
    }

    while(!schedule.empty()) {
        int due = schedule.front();
        schedule.pop_front();

        int leftFeature = schedule.size();
        int count = 1;

        while(!schedule.empty() && schedule.front() <= due) {
            schedule.pop_front();
            count++;
        }

        answer.push_back(count);
    }

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<int> prog = {93, 30, 55};
        vector<int> speeds = {1, 30, 5};
        vector<int> answer = solution(prog, speeds);
        REQUIRE(answer[0] == 2);
        REQUIRE(answer[1] == 1);   
    }
}