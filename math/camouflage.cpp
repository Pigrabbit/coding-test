// Problem: https://programmers.co.kr/learn/courses/30/lessons/42578

#include <string>
#include <vector>
#include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    unordered_map<string, int> numClothes;

    for (int i = 0; i < clothes.size(); i++) {
        numClothes[clothes[i][1]]++;
    }

    vector<string> keys;
    keys.reserve(numClothes.size());
    vector<int> values;
    values.reserve(numClothes.size());
    
    for(auto kv : numClothes) {
        keys.push_back(kv.first);
        values.push_back(kv.second);  
    } 

    int tmp = 1;
    for (int i = 0; i < numClothes.size(); i++) {
        tmp = tmp * (values[i] + 1);
    }

    return answer = tmp - 1;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<vector<string>> clothes = {
            {"yellow_hat", "headgear"}, 
            {"blue_sunglasses", "eyewear"}, 
            {"green_turban", "headgear"}
        };

        REQUIRE(solution(clothes) == 5);
    }
    SECTION("example 2") {
        vector<vector<string>> clothes = {
            {"yellow_hat", "face"}, 
            {"blue_sunglasses", "face"}, 
            {"green_turban", "face"}
        };

        REQUIRE(solution(clothes) == 3);
    }
}
