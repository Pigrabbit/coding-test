// Problem: https://www.acmicpc.net/problem/17281

#include <iostream>
#include <vector>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

const int RUNNER_NONE  = 0;
const int RUNNER_1     = 1;
const int RUNNER_2     = 2;
const int RUNNER_3     = 3;
const int RUNNER_1_2   = 4;
const int RUNNER_2_3   = 5;
const int RUNNER_1_3   = 6;
const int RUNNER_1_2_3 = 7;

const int OUT          = 0;
const int SINGLE       = 1;
const int DOUBLE       = 2;
const int TRIPLE       = 3;
const int HOMERUN      = 4;

int currentState = RUNNER_NONE;
int outCount = 0;
int score = 0;
int maxScore = 0;
bool endOfInning = false;

int results[51][10];

// STATE_MACHINE
void fsm(int result) {
	if (result == OUT) {
		if (outCount == 2) {
			// end of inning
			endOfInning = true;
            currentState = RUNNER_NONE;
			outCount = 0;
		} else {
            outCount++;
        }
		return;
	}
	
	switch(currentState) {
		case RUNNER_NONE:
            if (result == HOMERUN) {
                score++;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                currentState = RUNNER_2; 
            } else if (result == SINGLE) {
                currentState = RUNNER_1; 
            }
			break;
            
		case RUNNER_1:
            if (result == HOMERUN) {
                score += 2;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score++;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                currentState = RUNNER_2_3;
            } else if (result == SINGLE) {
                currentState = RUNNER_1_2;
            }
			break;

		case RUNNER_2:	
            if (result == HOMERUN) {
                score += 2;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score++;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
				score++;
				currentState = RUNNER_2;
			} else if (result == SINGLE) {
				currentState = RUNNER_1_3; 
			}
			break;

        case RUNNER_3:
            if (result == HOMERUN) {
                score += 2;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score++;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                score++;
                currentState = RUNNER_2;
            } else if (result == SINGLE) {
                score++;
                currentState = RUNNER_1;
            }
            break;
		
        case RUNNER_1_2:
            if (result == HOMERUN) {
                score += 3;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score += 2;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                score++;
                currentState = RUNNER_2_3;
            } else if (result == SINGLE) {
                currentState = RUNNER_1_2_3;
            }
            break;
        
        case RUNNER_2_3:
            if (result == HOMERUN) {
                score += 3;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score += 2;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                score += 2;
                currentState = RUNNER_2;
            } else if (result == SINGLE) {
                score++;
                currentState = RUNNER_1_3;
            }
            break;
        
        case RUNNER_1_3:
            if (result == HOMERUN) {
                score += 3;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score += 2;
                currentState = RUNNER_3;
            } else if (result == DOUBLE) {
                score++;
                currentState = RUNNER_2_3;
            } else if (result == SINGLE) {
                score++;
                currentState = RUNNER_1_2;
            }
            break;

		case RUNNER_1_2_3:
            if (result == HOMERUN) {
                score += 4;
                currentState = RUNNER_NONE;
            } else if (result == TRIPLE) {
                score += 3;
                currentState = RUNNER_3;
            } else if (result == 2) {
				score += 2;
				currentState = RUNNER_2_3; 
			}
			else if (result == 1) {
				score++;
				currentState = RUNNER_1_2_3; 
			}
			break;
	}
}

int inningScore(std::vector<int> & battingOrder, int currentInning, int startBatterIdx) {
    // return next inning start batter index
    int batter;
    int i = startBatterIdx;
    while(!endOfInning) {
        batter = battingOrder[i-1];
        fsm(results[currentInning][batter]);
        i = (i == 9)? 1 : (i + 1);
    }
    endOfInning = false;

    return i;
}

std::vector<std::vector<int>> getBattingOrders() {
    std::vector<std::vector<int>> battingOrders;
    std::vector<int> order;
    for (int player = 2; player <= 9; player++) {
        order.push_back(player);
    }

    do {
        std::vector<int> orderWith4 = order;
        orderWith4.insert(orderWith4.begin() + 3, 1);
        battingOrders.push_back(orderWith4);
    } while (std::next_permutation(order.begin(), order.end()));

    return battingOrders;
}

TEST_CASE("fsm") {
    SECTION("grouond(fly) out on no out, no base runners") {
        outCount = 0;
        score = 0;
        fsm(OUT);
        REQUIRE(currentState == RUNNER_NONE);
        REQUIRE(outCount == 1);
    }
    SECTION("grouond(fly) out on 2 outs, no base runners") {
        outCount = 2;
        score = 0;
        fsm(OUT);
        REQUIRE(currentState == RUNNER_NONE);
        REQUIRE(outCount == 0);
        REQUIRE(endOfInning == true);
    }
    SECTION("single on no out, no base runners") {
        outCount = 0;
        score = 0;
        fsm(SINGLE);
        REQUIRE(currentState == RUNNER_1);
        REQUIRE(outCount == 0);
    }
    SECTION("single on no out, bases loaded") {
        outCount = 0;
        score = 0;
        currentState = RUNNER_1_2_3;
        fsm(SINGLE);
        REQUIRE(currentState == RUNNER_1_2_3);
        REQUIRE(outCount == 0);
        REQUIRE(score == 1);
    }
    SECTION("homerun on no out, runner on 1 and 2") {
        outCount = 0;
        score = 0;
        currentState = RUNNER_1_2;
        fsm(HOMERUN);
        REQUIRE(currentState == RUNNER_NONE);
        REQUIRE(outCount == 0);
        REQUIRE(score == 3);
    }
}

TEST_CASE("inningScore") {
    SECTION("example1") {
        score = 0;
        outCount = 0;
        currentState = 0;
        endOfInning = false;
        int results[10] = {0, 0, 0, 0, 4, 0, 0, 0, 0, 0};
        int nextBatter = inningScore(results, 1);
        REQUIRE(nextBatter == 4);
        REQUIRE(score == 0);
    }
    SECTION("example2") {
        score = 0;
        outCount = 0;
        currentState = 0;
        endOfInning = false;
        int results[10] = {0, 0, 0, 0, 4, 0, 0, 0, 0, 0};
        int nextBatter = inningScore(results, 4);
        REQUIRE(nextBatter == 8);
        REQUIRE(score == 1);
    }
    SECTION("example3") {
        score = 0;
        outCount = 0;
        currentState = 0;
        endOfInning = false;
        int results[10] = {0, 1, 1, 1, 4, 0, 0, 0, 0, 0};
        int nextBatter = inningScore(results, 1);
        REQUIRE(nextBatter == 8);
        REQUIRE(score == 4);
    }
    SECTION("example4") {
        score = 4;
        outCount = 0;
        currentState = 0;
        endOfInning = false;
        int results[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int nextBatter = inningScore(results, 8);
        REQUIRE(nextBatter == 2);
        REQUIRE(score == 4);
    }
}

int main() {
    int N = 0;
    std::cin >> N;
    for (int inning = 1; inning <= N; inning++) {
        for (int player = 1; player <= 9; player++) {
            std::cin >> results[inning][player];
        }
    }

    std::vector<std::vector<int>> battingOrders = getBattingOrders();
    for (auto order: battingOrders) {
        score = 0;
        int startBatterIdx = 1;
        for (int inning = 1; inning <= N; inning++) {
            startBatterIdx = inningScore(order, inning, startBatterIdx);
        }

        maxScore = std::max(maxScore, score);
    }

    std::cout << maxScore << "\n";
    
    return 0;
}
