// 구명보트

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    vector<int> desc = people;
    vector<int> asc = people;
    
    sort(desc.begin(), desc.end(), greater<int>());
    sort(asc.begin(), asc.end());
    
    int people_cnt = 0;
    int j = 0;
    
    for (int i : desc) {
        if (people_cnt >= people.size()) break;
        if (i + asc[j] <= limit) {
            answer ++;
            j ++;
            people_cnt += 2;
        } else {
            answer ++;
            people_cnt += 1;
        }
    }
    
    return answer;
}
