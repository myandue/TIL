// 오픈채팅방

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

vector<string> solution(vector<string> record) {
    
    unordered_map<string, string> um;
    string cmd, id, nick;
    
    for (const string& s : record) {
        istringstream iss(s);
        iss >> cmd >> id >> nick;
        if (cmd != "Leave") {
            um[id] = nick;
        }
    }
    
    vector<string> answer;
    string result;
    
    for (const string& s: record) {
        istringstream iss(s);
        iss >> cmd >> id >> nick;
        
        result = um[id] + "님이 ";
        
        if (cmd == "Enter") {
            result += "들어왔습니다.";
        } else if (cmd == "Leave") {
            result += "나갔습니다.";
        } else {
            continue;
        }
        
        answer.push_back(result);
    }
    
    return answer;
}
