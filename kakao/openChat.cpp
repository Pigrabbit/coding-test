// Problem: https://programmers.co.kr/learn/courses/30/lessons/42888

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

void updateMessage(vector<int> &occurence, vector<string> &answer, string nickname) {
    for (size_t j = 0; j < occurence.size(); j++) {
        string msgToEdit = answer[occurence[j]];
        vector<string> innerTokens;
        stringstream check2(msgToEdit);
        string buf;
        while (getline(check2, buf, ' ')) {
            innerTokens.push_back(buf);
        }
        string msgEditted = nickname + "님이 " + innerTokens.back();
        answer[occurence[j]] = msgEditted;
    }
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    unordered_map<string, vector<int>> occurrenceIdx;
    unordered_map<string, string> idToNickname;
    int numRecords = record.size();

    for (int i = 0; i < numRecords; i++) {
        string curRecord = record[i];
        vector<string> tokens;
        stringstream check1(curRecord);
        string tmp;

        while (getline(check1, tmp, ' ')) {
            tokens.push_back(tmp);
        }
        string message, nickname;
        string uid = tokens[1];

        if (tokens.front() == "Enter") {
            nickname = tokens[2];
            message = nickname + "님이 들어왔습니다.";
            answer.push_back(message);

            idToNickname[uid] = nickname;

            vector<int> occurence = occurrenceIdx[uid];
            updateMessage(occurence, answer, nickname);

            int idx = distance(answer.begin(), answer.end()) - 1;
            if (occurrenceIdx.count(uid) == 0) occurrenceIdx[uid] = {idx};
            else occurrenceIdx[uid].push_back(idx);
        } 
        else if (tokens.front() == "Leave") {
            message = idToNickname[uid] + "님이 나갔습니다.";
            answer.push_back(message);

            int idx = distance(answer.begin(), answer.end()) - 1;
            if (occurrenceIdx.count(uid) == 0) occurrenceIdx[uid] = {idx};
            else occurrenceIdx[uid].push_back(idx);
        }
        else {
            // 지금까지 occurence의 값들을 전부 바꿔줘야 함.
            vector<int> occurence = occurrenceIdx[uid];
            nickname = tokens[2];
            idToNickname[uid] = nickname;
            updateMessage(occurence, answer, nickname);
        }
    }

    return answer;
}
