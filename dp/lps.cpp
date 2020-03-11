// Problem: https://www.acmicpc.net/problem/13275

#include <iostream>
#include <string>

int getPalindromeLen(std::string & s, int left, int right) {
	if (left > right) {
        return 0;
    }

	int palindromeLen = 0;
	while(left >= 0 && right < s.length() && s[left] == s[right]) {
		left--;
		right++;
	}

	palindromeLen = right - left - 1;
	return palindromeLen;
}

int getLPS(std::string & s) {
    if (s.length() == 0) {return 0;}
	int lenLPS = 0;
	int start = 0, end = 0, currentMax = 0, tmp = 0;

	for (int i = 0; i < s.length(); i++) {
		int lenOdd = getPalindromeLen(s, i, i);
		int lenEven = getPalindromeLen(s, i, i + 1);
		tmp = std::max(lenOdd, lenEven);
		currentMax = end - start;
		if (tmp > currentMax) {
			start = i - ((tmp - 1) / 2);
			end = i + (tmp / 2);
		}
	}
    lenLPS = end - start + 1;

	return lenLPS;
}

int main() {
    std::string s;
    std::cin >> s;

    std::cout << getLPS(s) << "\n";

    return 0;
}
