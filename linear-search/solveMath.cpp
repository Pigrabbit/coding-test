#include <string>
#include <vector>
#include <map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> highestScorers;
    int countA = 0;
    int countB = 0;
    int countC = 0;

    // count score of each person
    for (int i = 0; i < answers.size(); i++) {
        int answerA = i % 5 + 1;
        int answerB;
        int answerC;
        switch (i % 8)
            {
            case 1:
                answerB = 1;
                break;
            case 3:
                answerB = 3;
                break;
            case 5:
                answerB = 4;
                break;
            case 7:
                answerB = 5;
                break;    
            default:
                answerB = 2;
            }
        
        switch (i % 10)
            {
            case 0:
                answerC = 3;
                break;
            case 1:
                answerC = 3;
                break;
            case 2:
                answerC = 1;
                break;
            case 3:
                answerC = 1;
                break;
            case 4:
                answerC = 2;
                break;
            case 5:
                answerC = 2;
                break;
            case 6:
                answerC = 4;
                break;
            case 7:
                answerC = 4;
                break;
            case 8:
                answerC = 5;
                break;
            case 9:
                answerC = 5;
                break;                     
            }
    
        if (answers[i] == answerA) {
            countA++;
        }
        if (answers[i] == answerB) {
            countB++;
        }
        if (answers[i] == answerC) {
            countC++;
        }
    }
    
    map <int, int> personalScore;
    personalScore[1] = countA;
    personalScore[2] = countB;
    personalScore[3] = countC;

    // get the max score
    pair<int, int> _ = minmax({countA, countB, countC});
    int max = _.second;

    // get the highest scorer
    for (int i = 0; i < personalScore.size(); i ++) {
        if (personalScore[i+1] == max) {
            highestScorers.push_back(i+1);
        }
    }

    return highestScorers;
}

TEST_CASE("find the highest scorer") {

    SECTION("Example 1") {
        vector<int> answers = {1, 2, 3, 4, 5};
        vector<int> highestScorer = {1};
        REQUIRE(solution(answers) == highestScorer);
    }
    
    SECTION("Example 2") {
        vector<int> answers = {1, 3, 2, 4, 2};
        vector<int> highestScorer = {1, 2, 3};
        REQUIRE(solution(answers) == highestScorer);
    }
}
