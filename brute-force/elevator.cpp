// Problem: https://www.acmicpc.net/problem/3541

#include <iostream>
#include <limits.h>

int getLowestFloor(int ** elevators, int numElevators, int numPress) {
    int lowestFloor = INT_MAX;
    int lobby = 0;
    for (int i = 0; i < numElevators; i++) {
        int * elevator = elevators[i];
        int up = elevator[0], down = elevator[1];
        int current = 0;

        current = (up + down) + ((-numPress * down) % (up + down));

        if (current == lobby) {
            current += (up + down);
        }
        lowestFloor = std::min(lowestFloor, current);
    }
    return lowestFloor;
}


int main() {
    int numElevator = 0, numPress = 0;
    std::cin >> numPress >> numElevator;

    int **elevators = new int * [numElevator];
    for(int i = 0; i < numElevator; i++) {
        elevators[i] = new int[2];
        for (int j = 0; j < 2; j++) {
            std::cin >> elevators[i][j];
        }
    }

    int lowestFloor = getLowestFloor(elevators, numElevator, numPress);
    std::cout << lowestFloor << "\n";

    return 0;
}
