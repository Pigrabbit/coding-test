// Problem: https://www.acmicpc.net/problem/10942

#include <iostream>
#include <cstring>

const int MAX_LENGTH = 2000;
const int MAX_QUERY = 1000000;
int sequence[MAX_LENGTH+1];
int cache[MAX_LENGTH+1][MAX_LENGTH+1];
int query[MAX_QUERY][2];

int isPalindrome(int start, int end) {
    if (start < 1 || end > MAX_LENGTH) {
        return 0;
    }

    if (start >= end) {
        return 1;
    }

    int & ret = cache[start][end];
    if (ret != -1) {
        return ret;
    }

    if (sequence[start] == sequence[end]) {
        return ret = isPalindrome(start + 1, end - 1);
    } else {
        return ret = 0;
    }
}

int main() {
    std::ios_base :: sync_with_stdio(false); 
    std::cin.tie(NULL); 
    std::cout.tie(NULL);
    
    int sequenceLen = 0, queryLen = 0;
    std::cin >> sequenceLen;
    for (int i = 1; i <= sequenceLen; i++) {
        std::cin >> sequence[i];
    }
    std::memset(cache, -1, sizeof(cache));

    std::cin >> queryLen;
    int start, end;
    for (int i = 0; i < queryLen; i++) {
        std::cin >> start >> end;
        std::cout << isPalindrome(start, end) << "\n";
    }

    return 0;
}

