// Problem: https://www.acmicpc.net/problem/5015

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int MAX_LENGTH = 100;
int memo[MAX_LENGTH + 1][MAX_LENGTH + 1][MAX_LENGTH + 1];

std::string pattern;
std::vector<std::string> filenames;

int match(int p, int f, int fileNum) {
    int & ret = memo[fileNum][p][f];
    if (ret != -1) {
        return ret;
    }
    std::string filename = filenames[fileNum];
	while (p < pattern.size() && f < filename.size() && (pattern[p] == filename[f])) {
		++p;
		++f;
	}
    if (p == pattern.size()) {
        ret = f == filename.size();
		return ret;
	}
	if (pattern[p] == '*') {
		for (int skip = 0; skip + f <= filename.size(); ++skip){
			if (match(p + 1, f + skip, fileNum)) {
				return ret = 1;
			}
		}
	}
	return ret = 0;
}

TEST_CASE("match") {
    memset(memo, -1, sizeof memo);
    SECTION("identical filename and pattern") {
        pattern = "fcn.py";
        filename = "fcn.py";
        REQUIRE(match(0, 0, 0) == true);
    }
    SECTION("different filename and pattern without wildcard") {
        pattern = "fcn.pyc";
        filename = "fcn.py";
        REQUIRE(match(0, 0, 1) == false);
    }
    SECTION("pattern with wildcard at the end") {
        pattern = "fcn.*";
        filename = "fcn.py";
        REQUIRE(match(0, 0, 2) == true);
    }
    SECTION("pattern with wildcard at the front") {
        pattern = "*.py";
        filename = "fcn.py";
        REQUIRE(match(0, 0,3) == true);
    }
    SECTION("pattern only has wildcard") {
        pattern = "*";
        filename = "fcn.py";
        REQUIRE(match(0, 0, 4) == true);
    }
}

int main() {
    std::cin >> pattern;
    int n = 0;
    std::cin >> n;

    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) {
        std::string file;
        std::cin >> file;
        filenames.push_back(file);
    }

    for (int fileNum = 0; fileNum < n; fileNum++) {
        int isMatch = match(0, 0, fileNum);
        if (isMatch) {
            std::cout << filenames[fileNum] << "\n";
        }
    }

    return 0;
}
