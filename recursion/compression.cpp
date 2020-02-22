// Problem: https://www.acmicpc.net/problem/1662

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

std::stack<int> openIndex;
std::unordered_map <int, int> parenthesesPair; // open index => closed index

int unzip(std::string & str, int start, int end) {
    int length = 0;
    for (int i = start; i < end; i++) {
        if (str[i] == '(') {
            length--;
            int K = int(str[i-1]) - 48;
            int Q = unzip(str, i + 1, parenthesesPair[i]);
            length += K * Q;
            i = parenthesesPair[i];
        } else {
            length++;
        }
    }

    return length;
}

int getLength(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '('){
            ::openIndex.push(i);
        } else if (str[i] == ')'){
            ::parenthesesPair[::openIndex.top()] = i;
            ::openIndex.pop();
        }
    }

    int length = unzip(str, 0, str.length());
    return length;
}

int main() {
    std::string str;
    std::cin >> str;
    
    int length = getLength(str);
    std::cout << length << "\n";

    return 0;
}
