#include <iostream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

const int MAX_HEIGHT = 40, MAX_WIDTH = 40;
const int MAX_STICKERS = 100;
int laptop[MAX_HEIGHT + 1][MAX_WIDTH + 1];

vector<vector<int>> rotateStickerCW(vector<vector<int>> & sticker, int rows, int cols) {
    vector<vector<int>> rotatedSticker(cols, vector<int> (rows));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (i == j) {
                rotatedSticker[i][j] = sticker[i][j];
            } else {
                rotatedSticker[i][j] = sticker[j][i];
            }
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int front = 0, back = rows-1; front < back; front++, back--) {
            int tmp = rotatedSticker[i][back];
            rotatedSticker[i][back] = rotatedSticker[i][front];
            rotatedSticker[i][front] = tmp;
        }
    }

    return rotatedSticker;
}

bool pasteCheck(vector<vector<int>> & sticker, int sHeight, int sWidth, int height, int width) {
    // 왼쪽 위 부터 확인하자
    // 스티커 영역에 스티커가 차지할 부분이 빈 칸이 아니면 붙일 수 없다.
    for (int y = 1; y <= height - sHeight + 1; y++) {
        for (int x = 1; x <= width - sWidth + 1; x++) {
            // 왼쪽 위 스티커 붙일 시작점 정함.
            // check availability
            bool isValid = true;
            for (int stickerY = 0; stickerY < sHeight && isValid; stickerY++) {
                for (int stickerX = 0; stickerX < sWidth && isValid; stickerX++) {
                    if (sticker[stickerY][stickerX] == 1 && laptop[y + stickerY][x + stickerX] == 1) {
                        isValid = false;
                    }
                }
            }

            // paste
            if (isValid) {
                for (int stickerY = 0; stickerY < sHeight && isValid; stickerY++) {
                    for (int stickerX = 0; stickerX < sWidth && isValid; stickerX++) {
                        if (sticker[stickerY][stickerX] == 1 && laptop[y + stickerY][x + stickerX] == 0) {
                            laptop[y + stickerY][x + stickerX] = 1;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

int main() {
    int height = 0, width = 0, numStickers = 0;
    cin >> height >> width >> numStickers;

    for (int y = 1; y <= height; y++) 
        for (int x = 1; x <= width; x++)
            laptop[y][x] = 0;
    
    while(numStickers--) {
        int sHeight = 0, sWidth = 0;
        cin >> sHeight >> sWidth;
        vector<vector<int>> sticker(sHeight, vector<int> (sWidth));
        for (int y = 0; y < sHeight; y++) 
            for (int x = 0; x < sWidth; x++)
                cin >> sticker[y][x];

        // 0
        if(pasteCheck(sticker, sHeight, sWidth, height, width)) {
            continue;
        }
        // 90
        vector<vector<int>> rotated90 = rotateStickerCW(sticker, sHeight, sWidth);
        if(pasteCheck(rotated90, sWidth, sHeight, height, width)) {
            continue;
        }
        // 180
        vector<vector<int>> rotated180 = rotateStickerCW(rotated90, sWidth, sHeight);
        if(pasteCheck(rotated180, sHeight, sWidth, height, width)) {
            continue;
        }
        // 270
        vector<vector<int>> rotated270 = rotateStickerCW(rotated180, sHeight, sWidth);
        pasteCheck(rotated270, sWidth, sHeight, height, width);
    }

    int count = 0;
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            if (laptop[y][x] == 1)
                count++;
        }
    }

    cout << count << "\n";

    return 0;
}


// TEST_CASE("rotateStickerCW") {
//     SECTION("example 1") {
//         vector<vector<int>> sticker = {
//             {1, 2},
//             {3, 4}
//         };
//         int rows = 2, cols = 2;
//         vector<vector<int>> rotatedSticker = rotateStickerCW(sticker, rows, cols);
//         // for (auto row: rotatedSticker) {
//         //     for (auto col: row) {
//         //         cout << col << " ";
//         //     }
//         //     cout << "\n";
//         // }
//         REQUIRE(rotatedSticker[0][0] == 3);
//     }
//     SECTION("example 2") {
//         vector<vector<int>> sticker = {
//             {1, 1, 1},
//             {1, 0, 1}
//         };
//         int rows = 2, cols = 3;
//         vector<vector<int>> rotatedSticker = rotateStickerCW(sticker, rows, cols);
//         // for (auto row: sticker) {
//         //     for (auto col: row) {
//         //         cout << col << " ";
//         //     }
//         //     cout << "\n";
//         // }
//         REQUIRE(rotatedSticker[0][0] == 1);
//     }
//     SECTION("example 2") {
//         vector<vector<int>> sticker = {
//             {1, 1, 1, 1, 1},
//             {0, 0, 0, 1, 0}
//         };
//         int rows = 2, cols = 5;
//         vector<vector<int>> rotatedSticker = rotateStickerCW(sticker, rows, cols);
//         // for (auto row: sticker) {
//         //     for (auto col: row) {
//         //         cout << col << " ";
//         //     }
//         //     cout << "\n";
//         // }
//         REQUIRE(rotatedSticker[0][0] == 0);
//     }
// }

// TEST_CASE("pasteCheck") {
//     SECTION("example 1") {
//         int height = 5, width = 4;
//         int laptopIn[height][width] = {
//             {0, 0, 0, 0},
//             {0, 0, 0, 0},
//             {0, 0, 0, 0},
//             {0, 0, 0, 0},
//             {0, 0, 0, 0}
//         };
//         for (int y = 0; y < height; y++) {
//             for (int x = 0; x < width; x++) {
//                 laptop[y+1][x+1] = laptopIn[y][x];
//             }
//         }
//         vector<vector<int>> sticker = {
//             {1, 0, 1},
//             {1, 1, 1},
//             {1, 0, 1}
//         };
//         pasteCheck(sticker, 3, 3, height, width);
//         cout << "=============\n";
//         for (int y = 1; y <= height; y++) {
//             for (int x = 1; x <= width; x++) {
//                 cout << laptop[y][x] << " ";
//             }
//             cout << "\n";
//         }

//         vector<vector<int>> sticker2 = {
//             {1, 1, 1, 1, 1},
//             {0, 0, 0, 1, 0}
//         };
//         pasteCheck(sticker2, 2, 5, height, width);
//         cout << "=============\n";
//         for (int y = 1; y <= height; y++) {
//             for (int x = 1; x <= width; x++) {
//                 cout << laptop[y][x] << " ";
//             }
//             cout << "\n";
//         }

//         vector<vector<int>> rotated = rotateStickerCW(sticker2, 2, 5);
//         pasteCheck(rotated, 5, 2, height, width);
//         cout << "=============\n";
//         for (int y = 1; y <= height; y++) {
//             for (int x = 1; x <= width; x++) {
//                 cout << laptop[y][x] << " ";
//             }
//             cout << "\n";
//         }
//         REQUIRE(laptop[1][1] == 1);
//     }
// }