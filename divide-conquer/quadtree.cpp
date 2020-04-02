// Problem: https://www.acmicpc.net/problem/1992

#include <iostream>
#include <string>

using namespace std;

const int MAX_HEIGHT = 64, MAX_WIDTH = 64;
char image[MAX_HEIGHT+1][MAX_WIDTH+1];

string zip(int y, int x, int size) {
	string res;
	if (size == 1) {
        return string(1, image[y][x]);
    }
	string leftUp = zip(y, x, size/2);
	string rightUp = zip(y, x + size/2, size/2);
	string leftDown = zip(y + size/2, x, size/2);
	string rightDown = zip(y + size/2, x + size/2, size/2);

	if (leftUp == rightUp && rightUp == leftDown && leftDown == rightDown && rightDown == leftUp) {
        bool isIdentical = true;
        if (leftUp.size() > 1) {
            char front = leftUp[0];
            for (int i = 1; i < leftUp.size(); i++) {
                if (leftUp[i] != front) {
                    isIdentical = false;
                    break;
                }
            }
        }
        if (isIdentical) return res = leftUp;
	} 
	
    res = '(' + leftUp + rightUp + leftDown + rightDown + ')';
	return res;
}

int main() {
    int N = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> image[i][j];
        }
    }

    string res = zip(0, 0, N);
    cout << res << "\n";

    return 0;
}
