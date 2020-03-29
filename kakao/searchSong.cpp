// Problem: https://programmers.co.kr/learn/courses/30/lessons/60060

#include <string>
#include <vector>
#include <unordered_map>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_WORDS_LEN = 100000;

bool isMatch(string query, string word);
int hashCode(string s);

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    int numQueries = queries.size(), numWords = words.size();
    unordered_map<string, int> patternCount;
    vector<string> wordByLength[MAX_WORDS_LEN + 1];

    // sort(words.begin(), words.end(), 
    //     [](const std::string& lhs, const std::string& rhs) {
    //         return lhs.size() == rhs.size() ? lhs < rhs : lhs.size() < rhs.size(); 
    // });
    
    for (auto word:words) {
        int len = word.size();
        wordByLength[len].push_back(word);
    }


    for (int i = 0; i < numQueries; i++) {
        string query = queries[i];
        if(patternCount.count(query) > 0) continue;

        vector<string> wordsCand = wordByLength[query.size()];
        for (int j = 0; j < wordsCand.size(); j++) {
            string word = wordsCand[j];
            if (isMatch(query, word)) {
                patternCount[query]++;
            }
        }
    }

    for (int i = 0; i < numQueries; i++) {
        string query = queries[i];
        answer.push_back(patternCount[query]);
    }


    return answer;
}

int hashCode(string s) {
    int g = 31;
    int hash = 0;
    for (int i = 0; i < s.length(); i++) {
        hash = g * hash + s[i];
    }
    return hash;
}

bool isMatch(string query, string word) {
    if (query.size() != word.size()) {
        return false;
    }
    int qIdx = query.find("?");
    if (qIdx == 0) {
        // prefix
        int lastIdx = query.rfind("?");
        return hashCode(word.substr(lastIdx + 1)) == hashCode(query.substr(lastIdx + 1));
    }
    else {
        // suffix
        return hashCode(word.substr(0, qIdx)) == hashCode(query.substr(0, qIdx));
    }
}

TEST_CASE("hashCode") {
    SECTION("with identical string") {
        string s1 = "hello", s2 = "hello";
        REQUIRE(hashCode(s1) == hashCode(s2));
    }
    SECTION("with different string") {
        string s1 = "hello", s2 = "hi";
        REQUIRE(hashCode(s1) != hashCode(s2));
    }
}

TEST_CASE("isMatch") {
    SECTION("with different length") {
        string query = "fro?", word = "frodo";
        REQUIRE(isMatch(query, word) == false);
    }
    SECTION("with prefix matched pattern") {
        string query = "frod?", word = "frodo";
        REQUIRE(isMatch(query, word) == true);
    }
    SECTION("with suffix matched pattern") {
        string query = "????o", word = "frodo";
        REQUIRE(isMatch(query, word) == true);
    }
}

TEST_CASE("solution") {
    SECTION("example 1") {
        vector<string> words = {"frodo", "front", "frost", "frozen", "frame", "kakao"};
        vector<string> queries = {"fro??", "????o", "fr???", "fro???", "pro?"};
        vector<int> exp = {3, 2, 4, 1, 0};
        REQUIRE(solution(words, queries) == exp);
    }
}
