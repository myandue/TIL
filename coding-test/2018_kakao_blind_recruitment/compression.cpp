// [3차] 압축

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    
    // 사전 초기화
    unordered_map<string, int> dic;
    char a = 'A';
    for (int i = 1 ; i <= 26 ; i ++) {
        dic[string(1, a)] = i;
        a += 1;
    }
    
    int last_num = 26;
    for (int i = 0 ; i < msg.size() ; i++) {
        string search_msg;
        string max_msg;
        int len = 1;
        while (i + len <= msg.size()) {
            search_msg = msg.substr(i, len);
            if (dic.count(search_msg)) {
                max_msg = search_msg;
                len++;
            } else {
                break;
            }
        }
        answer.push_back(dic[max_msg]);
        i = i + max_msg.size() - 1;
        if (i+1 < msg.size()) {
            last_num += 1;
            dic[search_msg] = last_num;
        }
    }
    
    return answer;
}
