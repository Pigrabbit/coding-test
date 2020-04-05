// 게임 화면은 1 x 1 크기의 칸들로 이루어진 N x N 크기의 정사각 격자이며
//  위쪽에는 크레인이 있고 오른쪽에는 바구니가 있습니다. (위 그림은 5 x 5 크기의 예시입니다). 
// 각 격자 칸에는 다양한 인형이 들어 있으며 인형이 없는 칸은 빈칸입니다. 
// 모든 인형은 1 x 1 크기의 격자 한 칸을 차지하며 격자의 가장 아래 칸부터 차곡차곡 쌓여 있습니다. 
// 게임 사용자는 크레인을 좌우로 움직여서 멈춘 위치에서 가장 위에 있는 인형을 집어 올릴 수 있습니다. 
// 집어 올린 인형은 바구니에 쌓이게 되는 데, 이때 바구니의 가장 아래 칸부터 인형이 순서대로 쌓이게 됩니다. 
// 다음 그림은 [1번, 5번, 3번] 위치에서 순서대로 인형을 집어 올려 바구니에 담은 모습입니다.

// 만약 같은 모양의 인형 두 개가 바구니에 연속해서 쌓이게 되면 두 인형은 터뜨려지면서 바구니에서 사라지게 됩니다. 
// 위 상태에서 이어서 [5번] 위치에서 인형을 집어 바구니에 쌓으면 같은 모양 인형 두 개가 없어집니다.

// 크레인 작동 시 인형이 집어지지 않는 경우는 없으나 만약 인형이 없는 곳에서 크레인을 작동시키는 경우에는 아무런 일도 일어나지 않습니다. 
// 또한 바구니는 모든 인형이 들어갈 수 있을 만큼 충분히 크다고 가정합니다. (그림에서는 화면표시 제약으로 5칸만으로 표현하였음)

// 게임 화면의 격자의 상태가 담긴 2차원 배열 board와
//  인형을 집기 위해 크레인을 작동시킨 위치가 담긴 배열 moves가 매개변수로 주어질 때, 
// 크레인을 모두 작동시킨 후 터트려져 사라진 인형의 개수를 return 하도록 solution 함수를 완성해주세요.

// sol
// 2D array인 board 배열을 받는다.
// 여기서 주의할 점은 board는 indexing이 0부터 n-1까지 되어있다.

// moves 배열을 순회하며 각 칸에서 인형을 집는다.
// 인형의 모양은 1-100까지 int로 표현
// board의 y좌표에 대해 순회하면서 빈 칸이 아닐 경우 그 칸에서 뽑는다.
// board[i][x] 에서 뽑았다면 그 좌표의 board값은 빈칸으로 update한다.

// 뽑은 인형은 stack에 다가 push하자.
// push하기전에 top을 확인하자.
// 다른 번호면 그냥 push
// 같은 번호의 인형이면 top을 pop해주고 count를 2 증가시킨다.

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int EMPTY = 0;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int numMoves = moves.size(), boardSize = board.size();
    int character = -1;
    stack<int> basket;

    for (int i = 0; i < numMoves; i++) {
        int col = moves[i] - 1;
        // 인형뽑기
        for (int y = 0; y < boardSize; y++) {
            if (board[y][col] == EMPTY) {
                if(y != boardSize - 1) {
                    continue;
                }
            }
            character = board[y][col];
            board[y][col] = EMPTY;
            break;
        }

        // 뽑아서 바구니에 넣기
        if (character == 0) continue;

        if (basket.empty() || character != basket.top()) {
            basket.push(character);
            continue;
        }
        cout << "current col: " << col+1 << ", current char: " << character << ", current top: " << basket.top() << "\n";
        basket.pop();
        answer += 2;
    }
    

    return answer;
}


TEST_CASE("solution") {
    SECTION("no characters at all") {
        vector<vector<int>> board = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };
        vector<int> moves = {1, 5, 3};
        REQUIRE(solution(board, moves) == 0);
    }
}
