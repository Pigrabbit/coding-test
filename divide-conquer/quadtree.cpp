// Problem: https://www.acmicpc.net/problem/1992

#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int MAX_HEIGHT = 64, MAX_WIDTH = 64;
char image[MAX_HEIGHT+1][MAX_WIDTH+1];

std::string zip(int y, int x, int size) {
	std::string res;
	if (size == 1) {
        return std::string(1, image[y][x]);
    }
	std::string leftUp = zip(y, x, size/2);
	std::string rightUp = zip(y, x + size/2, size/2);
	std::string leftDown = zip(y + size/2, x, size/2);
	std::string rightDown = zip(y +size/2, x + size/2, size/2);
	if (leftUp == rightUp && rightUp == leftDown && leftDown == rightDown && rightDown == leftUp) {
		res = leftUp;
	} else {
		res = '(' + leftUp + rightUp + leftDown + rightDown + ')';
	}
	return res;
}

TEST_CASE("zip") {
    image[0][0] = '0';
    image[0][1] = '1';
    image[1][0] = '1';
    image[1][1] = '0';
    SECTION("base case") {
        std::string res = zip(0, 1, 1);
        REQUIRE(res == "1");
    }
    SECTION("2x2 2d array with various values") {
        std::string res = zip(0, 0, 2);
        REQUIRE(res == "(0110)");
    }
    SECTION("2x2 2d array with single values") {
        image[0][0] = '1';
        image[0][1] = '1';
        image[1][0] = '1';
        image[1][1] = '1';
        std::string res = zip(0, 0, 2);
        REQUIRE(res == "1");
    }
}

int main() {
    int N = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> image[i][j];
        }
    }

    std::string res = zip(0, 0, N);
    std::cout << res << "\n";

    return 0;
}
