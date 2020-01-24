#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> N;

int findNum(int arrLength, int num) {
    int low = 0;
    int high = arrLength - 1;
    int mid = 0; 

    while (low <= high){
        mid = low + (high - low) / 2;
        if (N[mid] == num) {
            return 1;
        } else if (N[mid] < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m = 0;

    cin >> n;
    N.reserve(n);
    
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        N.push_back(num);
    }

    cin >> m;
    sort(N.begin(), N.end());

    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        int isInArray = 0;
        isInArray = findNum(n, num);
        cout << isInArray << "\n";
    }
    return 0;
}
