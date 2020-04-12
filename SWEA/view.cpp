// Problem: 1206

#include <iostream>
#include <vector>
#define vec vector
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	for(test_case = 1; test_case <= 10; ++test_case)
	{
        int width = 0;
        cin >> width;
        vec<int> apartments(width);
        for (int i = 0; i < width; i++) {
            cin >> apartments[i];
        }

        // check availability
        int count = 0;
        for (int i = 2; i < width - 2; i++) {
            int leftAvailable = min(apartments[i] - apartments[i-1], apartments[i] - apartments[i-2]);
            int rightAvailable = min(apartments[i] - apartments[i+1], apartments[i] - apartments[i+2]);
            int available = min(leftAvailable, rightAvailable);
            if (available > 0) count += available;
        }

        cout << "#" << test_case << " " << count << "\n";
	}
	return 0;
}
