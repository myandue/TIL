// 큰 수 만들기

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    vector<char> v;
    
    for (char c : number) {
        while (!v.empty() && c > v.back() && k > 0) {
                v.pop_back();
                k--;
        }
        
        v.push_back(c);
    }
    
    string answer;
    for (char c : v) {
        answer += c;
    }
    
    return answer.substr(0, answer.size() - k);
}
