// sol
// banned_id 1개는 응모자 id 1개의 대응되기 때문에
// banned_id를 iterate하면서 matching되는 user_id목록을 찾아 map에 저장하자.
// map: [banned_id] => [user_id]
// map의 key로 banned id, value로 user_id를 사용하자

// eg 1
// fr*d* => frodo, fradi
// abc1** => abc123
// return 2;

// eg 2
// "*rodo" => frodo, crodo
// "*rodo" => crodo
// "******" => abc123, frodoc
// return 2

// sol 2
// 일단 user_id N개 중에 banned_id R개를 뽑는 조합을 모두 만들자.
// 각 조합에 대해 element들이 banned_id에 주어진 문자열들과 mapping되는지 확인하고
// mapping 될 경우 count를 늘리자.

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    int numUserId = user_id.size(), numBannedId = banned_id.size();
    vector<int> perm(numUserId, 0);
    fill(perm.begin(), perm.begin() + numBannedId, 1);
    sort(perm.begin(), perm.end());

    do {
        vector<string> comb;
        for (int i = 0; i < numUserId; i++) {
            if (perm[i] == 1) {
                comb.push_back(user_id[i]);
                cout << user_id[i] << " ";
            }
        }
        cout << "\n";
        // check mapping
        // itreate through banned_id
        sort(comb.begin(), comb.end());
        do {
            int count = 0;
            bool isUsed[comb.size()];
            memset(isUsed, false, sizeof(isUsed));
            unordered_map<string, vector<string>> bannedIdToUserId;

            for (int i = 0; i < numBannedId; i++) {
                bool isMatched = true;
                string bannedIdToCheck = banned_id[i];

                for (int j = 0; j < comb.size(); j++) {
                    if (isUsed[j]) continue;
                    string userIdToCheck = comb[j];
                    if (bannedIdToUserId.count(bannedIdToCheck) > 0 && \
                     find(bannedIdToUserId[bannedIdToCheck].begin(), bannedIdToUserId[bannedIdToCheck].end(), userIdToCheck) != bannedIdToUserId[bannedIdToCheck].end()) 
                    continue;


                    if (bannedIdToCheck.size() != userIdToCheck.size()) {
                        isMatched = false;
                        continue;
                    }                
                    for (int pos = 0; pos < bannedIdToCheck.size(); pos++) {
                        if (bannedIdToCheck[pos] != userIdToCheck[pos]) {
                            if (bannedIdToCheck[pos] != '*') {
                                isMatched = false;
                                break;
                            }
                            continue;
                        }
                    }

                    if (isMatched) {
                        bannedIdToUserId[bannedIdToCheck].push_back(userIdToCheck);
                        count++;
                        isUsed[j] = true;
                        break;
                    }
                }
            }

            if (count == numBannedId) {
                answer++; 
                cout << "Got answer!\t";
                for (auto el: comb) {
                    cout << el << " ";
                }
                cout << "\n";
                break;
            }
        } while (next_permutation(comb.begin(), comb.end()));
    } while (next_permutation(perm.begin(), perm.end()));


    return answer;
}

TEST_CASE("solution") {
    SECTION("example1") {
        cout << "example 1\n";
        vector<string> user_id = {
            "frodo", "fradi", "crodo", "abc123", "frodoc"
        };
        vector<string> banned_id = {
            "fr*d*", "abc1**"
        };
        REQUIRE(solution(user_id, banned_id) == 2);
    }
    SECTION("example 2") {
        cout << "example 2\n";
        vector<string> user_id = {
            "frodo", "fradi", "crodo", "abc123", "frodoc"
        };
        vector<string> banned_id = {
           "*rodo", "*rodo", "******"
        };
        REQUIRE(solution(user_id, banned_id) == 2);
    }
    SECTION("example 3") {
        cout << "example 3\n";
        vector<string> user_id = {
            "frodo", "fradi", "crodo", "abc123", "frodoc"
        };
        vector<string> banned_id = {
           "fr*d*", "*rodo", "******", "******"
        };
        REQUIRE(solution(user_id, banned_id) == 3);
    }
}

