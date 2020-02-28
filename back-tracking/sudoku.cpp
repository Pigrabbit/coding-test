// Problem: https://www.acmicpc.net/problem/2580

#include <iostream>
// #define CATCH_CONFIG_MAIN
// #include "../lib/catch.hpp"

int sudoku[9][9];

bool possible(int row, int col, int num) {
	for (int i = 0; i < 9; i++) {
		if (sudoku[i][col] == num) {return false;}
	}
	for (int j = 0; j < 9; j++) {
		if (sudoku[row][j] == num) {return false;}
	}
    int subSquareRow = (row / 3) * 3;
    int subSquareCol = (col / 3) * 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (sudoku[subSquareRow+i][subSquareCol+j] == num) {return false;}
		}
	}
    return true;
}

void solve(int count) {
    if (count == 81) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << sudoku[i][j] << " ";
            }
            std::cout << "\n";
        }
        exit(0);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (possible(i, j, num)) {
                        sudoku[i][j] = num;
                        solve(count + 1);
                        sudoku[i][j] = 0;
                    }
                }
                return;
            }
        }
    };
}

int main() {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = 0;
            std::cin >> num;
            sudoku[i][j] = num;
            if (num != 0) count++;
        }
    }

    solve(count);
    return 0;
}

// TEST_CASE("possible") {
//     int inputs[9][9] = {
//         {0, 3, 5, 4, 6, 9, 2, 7, 8},
//         {7, 8, 2, 1, 0, 5, 6, 0, 9},
//         {0, 6, 0, 2, 7, 8, 1, 3, 5},
//         {3, 2, 1, 0, 4, 6, 8, 9, 7},
//         {8, 0, 4, 9, 1, 3, 5, 0, 6},
//         {5, 9, 6, 8, 2, 0, 4, 1, 3},
//         {9, 1, 7, 6, 5, 2, 0 ,8, 0},
//         {6, 0, 3, 7, 0, 1, 9, 5, 2},
//         {2, 5, 8, 3, 9, 4, 7, 6, 0}
//     };
//     std::memcpy(sudoku, inputs, 9 * 9 * sizeof(int));    
//     SECTION("is possible to put 1 in (0, 0)") {
//         REQUIRE(possible(0, 0, 1) == true);
//     }
//     SECTION("is possible to put 3 in (1, 4)") {
//         REQUIRE(possible(1, 4, 3) == true);
//     }
//     SECTION("is possible to put 1 in (1, 4)") {
//         REQUIRE(possible(1, 4, 1) == false);
//     }
// }

// TEST_CASE("solve") {
//     int inputs[9][9] = {
//         {0, 3, 5, 4, 6, 9, 2, 7, 8},
//         {7, 8, 2, 1, 0, 5, 6, 0, 9},
//         {0, 6, 0, 2, 7, 8, 1, 3, 5},
//         {3, 2, 1, 0, 4, 6, 8, 9, 7},
//         {8, 0, 4, 9, 1, 3, 5, 0, 6},
//         {5, 9, 6, 8, 2, 0, 4, 1, 3},
//         {9, 1, 7, 6, 5, 2, 0 ,8, 0},
//         {6, 0, 3, 7, 0, 1, 9, 5, 2},
//         {2, 5, 8, 3, 9, 4, 7, 6, 0}
//     };
//     std::memcpy(sudoku, inputs, 9 * 9 * sizeof(int));    
//     SECTION("example 1") {
//         solve(67);
//     }
// }
