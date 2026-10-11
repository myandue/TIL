// 메뉴 리뉴얼

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, int> combs;

void pick(const string& order, int start, string cur, int k) {
    if (cur.size() == k) { // k개 다 골랐으면
        combs[cur]++;
        return;
    }
    
    for(int i = start ; i < order.size() ; i++) {
        pick(order, i+1, cur + order[i], k); 
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    // 메뉴 정렬
    for(string& order : orders) {
        sort(order.begin(), order.end());
    }
    
    for (int k : course) {
        combs.clear();
        
        for (string& order: orders) {
            pick(order, 0, "", k);
        }
        
        int max = 0;
        vector<string> answer_tmp;
        for (auto& comb: combs) {
            if (comb.second == 1) continue;
            if (comb.second >= max) {
                if (comb.second == max) {
                    answer_tmp.push_back(comb.first);
                } else {
                    max = comb.second;
                    answer_tmp.clear();
                    answer_tmp.push_back(comb.first);
                }
            }
        }
            
        for (string& comb : answer_tmp) {
            answer.push_back(comb);
        }
    }
    

    sort(answer.begin(), answer.end());
    
    return answer;
}
