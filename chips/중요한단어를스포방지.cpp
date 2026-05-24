/*
핵심 아이디어:
1. 각 문자 위치가 어느 스포 구간에 속하는지 미리 표시 (-1이면 비스포 구간)
2. 메시지를 단어 단위로 분리하면서, 각 단어가 걸친 스포 구간의 최댓값(=그 단어가 완전히 공개되는 클릭 시점)을 구함
3. 스포 구간이 전혀 안 걸친 단어들은 따로 nonSpoilerWords 집합에 저장 (조건 2 검사용)
4. 클릭 순서대로 진행하면서, 그 클릭에서 공개되는 단어들을 왼쪽 -> 오른쪽으로 보고 조건 2,3 검사
*/

#include <string>
#include <vector>
#include <set>
using namespace std;

int solution(string message, vector<vector<int>> spoiler_ranges) {
    int n = message.size();
    int m = spoiler_ranges.size();

    // 각 위치가 속한 스포 구간의 인덱스 (-1: 비스포 구간)
    vector<int> spoilerIdx(n, -1);
    for (int i = 0; i < m; i++) {
        for (int j = spoiler_ranges[i][0]; j <= spoiler_ranges[i][1]; j++){
            spoilerIdx[j] = i;
        }
    }

    // 단어 추출: (시작, 끝, 문자열)
    vector<pair<int, int>> wordRange;
    vector<string> words;
    for (int i = 0; i < n;){
        if (message[i] == ' ') { i++; continue; }
        int s = i;
        while (i < n && message[i] != ' ') i++;
        wordRange.push_back({s, i - 1});
        words.push_back(message.substr(s, i - s));
    }
    int W = words.size();

    // 각 단어가 걸친 스포 구간의 최댓값, 비스포 단어 집합
    vector<int> maxIdx(W, -1);
    set<string> nonSpoilerWords;
    for (int w = 0; w < W; w++) {
        int mx = -1;
        for (int j = wordRange[w].first; j <= wordRange[w].second; j++){
            if (spoilerIdx[j] != -1) mx = max(mx, spoilerIdx[j]);
        }
        maxIdx[w] = mx;
        if (mx == -1) nonSpoilerWords.insert(words[w]);
    }

    vector<vector<int>> revealedAt(m);
    for (int w = 0; w < W; w++) {
        if (maxIdx[w] >= 0) revealedAt[maxIdx[w]].push_back(w);
    }

    set<string> revealed;
    int answer = 0;
    for (int click = 0; click < m; click++) {
        for (int w : revealedAt[click]){
            const string& s = words[w];
            bool dup = revealed.count(s) > 0;
            bool inPlain = nonSpoilerWords.count(s) > 0;
            revealed.insert(s);
            if (!dup && !inPlain) answer++;
        }
    }
    return answer;
}