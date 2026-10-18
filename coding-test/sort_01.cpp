// 가장 큰 수

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers) {
    vector<string> v;
    for (int n : numbers) v.push_back(to_string(n));
    
    sort(v.begin(), v.end(), [](const string& a, const string& b){
        return a + b > b +  a;
    });
    
    if (v[0] == "0") return "0";
    
    string answer;
    for (const string& s : v) answer += s;
    
    return answer;
}

