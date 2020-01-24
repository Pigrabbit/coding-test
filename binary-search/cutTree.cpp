#include <iostream>
#include <vector>
#include <algorithm>
// #define CATCH_CONFIG_MAIN
// #include "../lib/catch.hpp"

using namespace std;

vector<int> trees;

int getMaxCutHeight(int treeNeeded) {
    long long maxHeight = 0;
    long long low = 0;
    long long high = trees.back();
    long long mid = 0;

    while (low <= high) {
        mid = low + (high - low) / 2;
        long long sum = 0;
        for (int tree: trees) {
            if (tree >= mid) {
                sum += tree - mid;
            }
        }

        if (sum < treeNeeded) {
            high = mid - 1;
        } else {
            if (mid >= maxHeight) {
                maxHeight = mid;
            }
            low = mid + 1;
        }
    } 

    return maxHeight;
}

// TEST_CASE("getMaxCutHeight") {
//     SECTION("example 1") {
//         int treeNeeded = 6;
//         trees = {10, 15, 17, 20};
//         REQUIRE(getMaxCutHeight(treeNeeded) == 15);
//     }
// }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int numTree, treeNeeded = 0;
    cin >> numTree >> treeNeeded;

    trees.reserve(numTree);
    for (int i = 0; i < numTree; i++) {
        int height = 0;
        cin >> height;
        trees.push_back(height);
    }

    sort(trees.begin(), trees.end());
    cout << getMaxCutHeight(treeNeeded) << "\n";

    return 0;
}
