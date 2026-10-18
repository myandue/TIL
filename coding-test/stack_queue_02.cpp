// 주식가격

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    vector<int> stack;
    
    stack.push_back(0);
    answer.push_back(prices.size() - 1);
    
    for(int i = 1 ; i < prices.size() ; i++) {
        answer.push_back(prices.size() - i - 1);
        while (!stack.empty() && prices[i] < prices[stack.back()]) { 
            answer[stack.back()] = i - stack.back();
            stack.pop_back();
        }
        stack.push_back(i);
    }
    
    return answer;
}
