// 순위 검색

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    
    unordered_map<string, vector<int>> um;
    for (const string& s : info) {
        stringstream ss(s);
        string lang, job, career, food, score;
        ss >> lang >> job >> career >> food >> score;
        
        string a[2] = {lang, "-"};
        string b[2] = {job, "-"};
        string c[2] = {career, "-"};
        string d[2] = {food, "-"};
        
        for (int i = 0 ; i < 2 ; i++) {
            for (int j = 0 ; j < 2 ; j++) {
                for (int x = 0 ; x < 2 ; x++) {
                    for (int y = 0 ; y < 2 ; y++) {
                        um[a[i] + b[j] + c[x] + d[y]].push_back(stoi(score));
                    }
                }
            }
        }
    }
    
    for(auto& v : um) {
        sort(v.second.begin(), v.second.end());
    }
    
    for (const string& q : query) {
        stringstream ss(q);
        string lang, job, career, food, score, dummy;
        ss >> lang >> dummy >> job >> dummy >> career >> dummy >> food >> score;
        
        vector<int> v = um[lang+job+career+food];
        auto it = lower_bound(v.begin(), v.end(), stoi(score));
        int idx = it - v.begin();
        answer.push_back(v.size() - idx);
        
    }
    return answer;
}
