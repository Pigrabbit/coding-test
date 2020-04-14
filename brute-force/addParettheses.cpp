// Problem: https://www.acmicpc.net/problem/16637

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <limits.h>

#define vec vector

using namespace std;

int answer = INT_MIN;
vec<int> invalidPos = {-1, -1};

// 다음 괄호 넣을 수 있는 위치 찾기 {여는 위치, 닫는 위치}
vec<int> findPos(string s, int idx) {
    int numOperand = 0;
    int numOperator = 0;
    int numOpened = 0;
    for (int i = idx; i < s.size(); i++) {
        // 숫자이면
        if (s[i] == '(') numOpened++;
        else if (s[i] == ')') numOpened--;
        else if (s[i] >= 48 && s[i] <= 57) numOperand++;
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*') numOperator++;

        if (numOpened == 0 && numOperand == 2 && numOperator == 1) {
            return {i-2, i + 1};
        }
    }

    return invalidPos;
}


// 수식을 받아 결과 계산
int calculate(string s) {
    stack<char> operators;
    stack<int> operands;
    int numOpened = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') numOpened++;
        else if (s[i] == ')') numOpened--;
        else if (s[i] >= 48 && s[i] <= 57) operands.push(s[i] - '0');
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*') operators.push(s[i]);

        while (true) {
            if (numOpened != 0 || operators.size() <= 0 || operands.size() <= 1) break;
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            char oper = operators.top();
            operators.pop();
            if (oper == '*') {
                operands.push(operand1 * operand2);
            }
            else if (oper == '+') {
                operands.push(operand1 + operand2);
            }
            else if (oper == '-') {
                operands.push(operand1 - operand2);
            }
        }
    }

    return operands.top();
}

// 수식을 받아 괄호 추가.
// dfs, back-tracking으로 구현.
void putParentheses(string s, int idx) {
    // base case
    // idx가 끝인 경우
    if (idx < 0 || idx >= s.size() - 1 ) {
        int result = calculate(s);
        answer = max(result, answer);
        return;
    }
    // 더 이상 괄호를 추가할 수 없는 경우
    vec<int> nextPos = findPos(s, idx);
    int openPos = nextPos[0], closedPos = nextPos[1];
    if (nextPos == invalidPos) {
        int result = calculate(s);
        answer = max(result, answer);
        return;
    }

    // 괄호 추가하기
    string updatedEqn = s.substr(0, openPos) + "(" + s.substr(openPos, 3) + ")" + s.substr(closedPos);
    // 추가한 경우
    putParentheses(updatedEqn, closedPos + 3);
    // 안 한 경우
    putParentheses(s, idx + 2);
}

int main() {
    int len = 0;
    cin >> len;
    string inputStr;
    cin >> inputStr;

    putParentheses(inputStr, 0);

    cout << answer << "\n";

    return 0;
}
