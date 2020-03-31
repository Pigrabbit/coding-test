// LZW 압축은 다음 과정을 거친다.

// 1. 길이가 1인 모든 단어를 포함하도록 사전을 초기화한다.
// 2. 사전에서 현재 입력과 일치하는 가장 긴 문자열 w를 찾는다.
// 3. w에 해당하는 사전의 색인 번호를 출력하고, 입력에서 w를 제거한다.
// 4. 입력에서 처리되지 않은 다음 글자가 남아있다면(c), w+c에 해당하는 단어를 사전에 등록한다.
// 5. 단계 2로 돌아간다.

// 처음 사전은 다음과 같은 색인을 갖는다.
// 1  2  3 ...  26
// a  b  c       z

// 예를 들어 입력으로 KAKAO가 들어온다고 하자.

// 현재 사전에는 KAKAO의 첫 글자 K는 등록되어 있으나, 
// 두 번째 글자까지인 KA는 없으므로, 
// 첫 글자 K에 해당하는 색인 번호 11을 출력하고, 다음 글자인 A를 포함한 KA를 사전에 27 번째로 등록한다.
// 두 번째 글자 A는 사전에 있으나, 세 번째 글자까지인 AK는 사전에 없으므로, 
// A의 색인 번호 1을 출력하고, AK를 사전에 28 번째로 등록한다.
// 세 번째 글자에서 시작하는 KA가 사전에 있으므로, 
// KA에 해당하는 색인 번호 27을 출력하고, 다음 글자 O를 포함한 KAO를 29 번째로 등록한다.
// 마지막으로 처리되지 않은 글자 O에 해당하는 색인 번호 15를 출력한다.

// 이 과정을 거쳐 다섯 글자의 문장 KAKAO가 4개의 색인 번호 [11, 1, 27, 15]로 압축된다.

// sol
// 주어진 문자열 msg를 앞에서부터 char 단위로 iterate하자.
// 먼저 그 글자가 사전에 있는지 확인한다.
// 있는 경우 그 다음 글자까지 포함해서 사전을 검색한다.
// 사전에 나오지 않을 때 까지 글자를 concatenate해서 검색한다.
// 더 이상 없는 경우, 사전에 있는 마지막 Concat전의 string의 Index를 출력하고
// 사전 가장 마지막에 현재까지 concat한 string을 추가한다.

// 사전 검색에 실패한 char부터 다시 탐색을 시작한다.

#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    vector<string> dictionary(27);
    // Inintialize dictionary
    // cout << "\nInitailize dictionary\n";
    for (int i = 1; i <= 26; i++) {
        dictionary[i] = char(64 + i);
        // cout << dictionary[i] << " ";
    }

    int len = msg.size();
    for (int i = 0; i < len; i++) {
        string w;
        w += msg[i];
        cout << "\n start char: " << w;
        
        int dictIdx = distance(dictionary.begin(), find(dictionary.begin(), dictionary.end(), w));
        cout << "\nstart char Idx: " << dictIdx << "\n";
        int cIdx = i + 1;
        vector<string>::iterator it;

        while (true) {
            w += msg[cIdx];
            it = find(dictionary.begin(), dictionary.end(), w);

            if (it == dictionary.end()) {
                break;
            }
            dictIdx = distance(dictionary.begin(), it);
            cIdx++;
        }
        // dictIdx = distance(dictionary.begin(), it);
        answer.push_back(dictIdx);

        dictionary.push_back(w);
        i = cIdx - 1;
    }

    cout << "Printing Dictionary\n";
    for (auto word: dictionary) {
        cout << word << "\n";
    }

    return answer;
}

TEST_CASE("solution") {
    SECTION("example 1") {
        string msg = "KAKAO";
        vector<int> answer = solution(msg);
        cout << "\nAnswer\n";
        for (auto i: answer) {
            cout << i << " ";
        }
        REQUIRE(answer[0] == 11);
        REQUIRE(answer[1] == 1);
        REQUIRE(answer[2] == 27);
        REQUIRE(answer[3] == 15);
    }
    SECTION("example 2") {
        string msg = "TOBEORNOTTOBEORTOBEORNOT";
        vector<int> answer = solution(msg);
        cout << "\nAnswer\n";
        for (auto i: answer) {
            cout << i << " ";
        }
        REQUIRE(answer[0] == 20);
    }
}
