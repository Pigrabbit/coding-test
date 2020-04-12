// Problem: https://programmers.co.kr/learn/courses/30/lessons/17686

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#define vec vector
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

struct file {
    string head;
    int number;
    string tail;
    string orgin;
};

file parseStr(string fileStr) {
    file retFile;
    int len = fileStr.size();
    int headEnd = 0, numberEnd = 0;
    for (int i = 0; i < len; i++) {
        if (fileStr[i] <= 57 && fileStr[i] >= 48) {
            if (headEnd == 0) headEnd = i - 1;
            if ((numberEnd - headEnd >= 5) || (numberEnd != 0 && numberEnd < i - 1)) break;
            numberEnd = i;
        }
        else {
            if (numberEnd > 0) break;
        }
    }
    retFile.head = fileStr.substr(0, headEnd + 1);
    transform(retFile.head.begin(), retFile.head.end(), retFile.head.begin(), ::toupper);
    retFile.number = stoi(fileStr.substr(headEnd + 1, numberEnd - headEnd));
    retFile.tail = (numberEnd + 1 >= len)? "\0" : fileStr.substr(numberEnd + 1, len - numberEnd);
    retFile.orgin = fileStr;

    return retFile;
}

bool compareTwoFile(file a, file b) {
    if (a.head != b.head) 
        return a.head < b.head;
    if (a.number != b.number)
        return a.number < b.number;
    return false;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    int numFiles = files.size();
    vector<file> parsedFile;
    for (int i = 0; i < numFiles; i++) {
        parsedFile.push_back(parseStr(files[i]));
    }

    stable_sort(parsedFile.begin(), parsedFile.end(), compareTwoFile);
    for (auto f: parsedFile) {
        answer.push_back(f.orgin);
    }
    return answer;
}

TEST_CASE("solution") {
    SECTION("example1") {
        vec<string> files = {
            "img12.png", "img10.png", "img02.png", "img1.png", "IMG01.GIF", "img2.JPG"
        };
        vec<string> exp = {
            "img1.png", "IMG01.GIF", "img02.png", "img2.JPG", "img10.png", "img12.png"
        };
        REQUIRE(solution(files) == exp);
    }
    SECTION("example2") {
        vec<string> files = {
            "F-15", "foo010bar020.zip", "ff123456IO.txt"
        };
        REQUIRE(solution(files).size() == 3);
    }
    SECTION("example3") {
        vec<string> files = {"MUZI01", "muzi10", "muzi1", "muzi2.png", "muzi001.txt"};
        vec<string> exp = {"MUZI01", "muzi1", "muzi001.txt", "muzi2.png" , "muzi10"};
        REQUIRE(solution(files) == exp);
    }
    SECTION("example4") {
        vec<string> files = {"muzi1.txt", "MUZI1.txt", "muzi001.txt", "muzi1.TXT"};
        vec<string> exp = files;
        REQUIRE(solution(files) == exp);
    }
    SECTION("example5") {
        vec<string> files = {"muzi01.txt", "MUZI0001.txt", "muzi00000.txt", "muzi1"};
        vec<string> exp = {"muzi00000.txt", "muzi01.txt", "MUZI0001.txt", "muzi1"};
        REQUIRE(solution(files) == exp);
    }
}

