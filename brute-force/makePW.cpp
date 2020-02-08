// Problem: https://www.acmicpc.net/problem/1759

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

string source;

vector<string> getCombination(int n, int r) {
    vector<string> comb;
    vector<int> index;
    for (int i = 0; i < (n-r); i++) {
        index.push_back(0);
    }
    for (int i = 0; i < r; i++) {
        index.push_back(1);
    }

    do {
        string password;
        for (int i = 0; i < n; i++) {
            if (index[i] == 1) {
                password += source[i];
            }
        }
        sort(password.begin(), password.end());
        comb.push_back(password);
    } while (next_permutation(index.begin(), index.end()));

    return comb;
}

void filterViolation(vector<string> &unfilteredComb) {
    string vowels = "aeiou";
    vector<string>::iterator it;
    for (it = unfilteredComb.begin(); it != unfilteredComb.end(); ++it) {
        string password = *it;
        int vowels = 0, consonants = 0;
        for (int i = 0; i < password.length(); i++) {
            if (password[i] == 'a' || password[i] == 'e' || password[i] == 'i' || password[i] == 'o' || password[i] == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
        bool isViolated = (vowels < 1) || (consonants < 2);
        if (isViolated) {
            unfilteredComb.erase(it);
            --it;
        }
    }
    sort(unfilteredComb.begin(), unfilteredComb.end());
}


TEST_CASE("filterViolation") {
    SECTION("example 1") {
        int C = 6;
        int L = 4;
        ::source = "atcisw";
        vector<string> comb = getCombination(C, L);
        filterViolation(comb);
        for (auto i: comb) {
            cout << i << "\n";
        }

        REQUIRE(comb.size() == 14);
    }
}

TEST_CASE("getCombination") {
    SECTION("example 1") {
        int C = 6;
        int L = 4;
        ::source = "atcisw";
        vector<string> comb = getCombination(C, L);
        for (auto i: comb) {
            cout << i << "\n";
        }

        REQUIRE(comb.size() == 15);
    }
}

int main() {
    int L = 0, C = 0;
    cin >> L >> C;
    for(int i = 0; i < C; i++) {
        char ch;
        cin >> ch;
        ::source += ch;
    }

    vector<string> passwords = getCombination(C, L);
    filterViolation(passwords);
    for (auto password: passwords) {
        cout << password << "\n";
    }

    return 0;
}
