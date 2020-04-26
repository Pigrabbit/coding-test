#include <iostream>
#include <vector>

using namespace std;
const int MAX_LENGTH = 1000;
int len;
int arr[MAX_LENGTH + 1];

int lis() {
    vector<int> tmp;
    tmp.push_back(arr[0]);
    for (int i = 1; i < len; i++) {
        if (arr[i] > tmp.back()) {
            tmp.push_back(arr[i]);
        } 
        else {
            // find lower bound
            auto it = lower_bound(tmp.begin(), tmp.end(), arr[i]);
            *it = arr[i];
        }
    }
    return tmp.size();
}

int main () {
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    cout << lis() << "\n";
    return 0;
}
