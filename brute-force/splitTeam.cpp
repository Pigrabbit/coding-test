// Problem: https://www.acmicpc.net/problem/14889

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_PLAYER = 20;

vector<vector<int>> stats(MAX_PLAYER, vector<int>(MAX_PLAYER, 0));

vector<vector<int>> getCombination(int n, int r) {
    vector<vector<int>> combination;
    vector<int> num;
    for (int i= 0; i < n; i++) {
        num.push_back(i+1);
    }

    vector<int> indexes;
    for (int i = 0; i < r; i++) {
        indexes.push_back(1);
    }

    for (int i=0; i < n-r; i++) {
        indexes.push_back(0);
    }

    sort(indexes.begin(), indexes.end());

    do {
        vector<int> team;
        for (int i = 0; i < n; i++) {
            if (indexes[i] == 1) {
                team.push_back(num[i]);
            }
        }
        combination.push_back(team);
    } while (next_permutation(indexes.begin(), indexes.end()));

    return combination;
}

int getTeamStat(vector<int> &playerNum, int n) {
    vector<int>::iterator it;
    int sum = 0;
    for (it = playerNum.begin(); it != playerNum.end(); ++it) {
        for (int j = 0; j < n; j++) {
            bool isInTeam = find(playerNum.begin(), playerNum.end(), j+1) != playerNum.end();
            bool isNotSelf = *it != (j+1);
            if  (isNotSelf && isInTeam) {
                // cout << "stat added: " << ::stats[*it-1][j] << "\n";
                sum += ::stats[*it-1][j];
            }
        }
    }
    return sum;
}

int getMinGap (int n) {
    int minGap;
    vector<int> gap;
    vector<int> playerPool;
    for (int i = 0; i < n; i++) {
        playerPool.push_back(i+1);
    }

    vector<vector<int>> comb = getCombination(n, n/2);
    vector<vector<int>>::iterator combIt;

    for (combIt = comb.begin(); combIt != comb.end(); ++ combIt) {
        vector<int> teamStart = *combIt;
        int statStart = getTeamStat(teamStart, n);

        vector<int> teamLink(n/2);
        sort(teamStart.begin(), teamStart.end());
        set_difference(playerPool.begin(), playerPool.end(), teamStart.begin(), teamStart.end(), teamLink.begin());
        int statLink = getTeamStat(teamLink, n);

        int differnece = abs(statStart - statLink);
        gap.push_back(differnece);
    }

    sort(gap.begin(), gap.end());
    minGap = gap.front();

    return minGap;
}

TEST_CASE("getCombination") {
    SECTION("example 1") {
        int n = 4;
        vector<vector<int>> comb = getCombination(n, n/2);
        REQUIRE(comb.size() == 6);
        REQUIRE(comb[0].size() == 2);
    }
}

TEST_CASE("getTeamStat") {
    SECTION("example1") {
        ::stats = {
            {0, 1, 2, 3},
            {4, 0, 5, 6},
            {7, 1, 0, 2},
            {3, 4, 5, 0}
        };
        vector<int> players = {1, 4};
        int n = 4;
        REQUIRE(6 == getTeamStat(players, n));
    }
    SECTION("example2") {
        ::stats = {
            {0, 1, 2, 3, 4, 5},
            {1, 0 ,2, 3, 4, 5},
            {1, 2, 0, 3, 4, 5},
            {1, 2, 3, 0, 4, 5},
            {1, 2, 3, 4, 0, 5},
            {1, 2, 3, 4, 5, 0}
        };
        vector<int> players = {1, 3, 6};
        int n = 6;
        REQUIRE(getTeamStat(players, n) == 17);
    }
}

TEST_CASE("getMinGap") {
    SECTION("example 1") {
        ::stats = {
            {0, 1, 2, 3},
            {4, 0, 5, 6},
            {7, 1, 0, 2},
            {3, 4, 5, 0}
        };
        int n = 4;
        REQUIRE(getMinGap(n) == 0);
    }
    SECTION("example2") {
        ::stats = {
            {0, 1, 2, 3, 4, 5},
            {1, 0 ,2, 3, 4, 5},
            {1, 2, 0, 3, 4, 5},
            {1, 2, 3, 0, 4, 5},
            {1, 2, 3, 4, 0, 5},
            {1, 2, 3, 4, 5, 0}
        };
        int n = 6;
        REQUIRE(getMinGap(n) == 2);
    }
}

int main() {
    int n = 0;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ::stats[i][j];
        }
    }

    cout << getMinGap(n) << "\n";

    return 0;
}