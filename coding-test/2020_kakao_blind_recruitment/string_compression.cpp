// 문자열 압축

#include <string>

using namespace std;

int solution(string s) {
    int size = s.size();
    
    int answer = size;
    int answer_tmp = size;
    
    int half = size / 2;
    
    int zip_cnt = 0;
    int start = 0;
    
    string now_word;
    string next_word;
    
    for (int i = 1 ; i <= half ; i++) {
        start = 0;
                
        while(start < size) {
            now_word = s.substr(start, i);
            
            start += i;
            if (start >= size) {
                if (zip_cnt > 0) {
                    answer_tmp -= zip_cnt * i;
                    answer_tmp += to_string(zip_cnt + 1).size(); 
                    //zip_cnt는 '몇 번 압축됐나'이기 때문에 '몇 번 반복됐다'를 보려면 '+ 1'이 필요하다.
                    //해당 반복횟수의 '자릿수'를 더해야하기 때문에 string으로 변경 후 size 값을 더한다.
                    
                    zip_cnt = 0;
                }
                break;
            }
            
            next_word = s.substr(start, i);
            
            if (next_word == now_word) {
                zip_cnt += 1;
            } else {
                if (zip_cnt > 0) {
                    answer_tmp -= zip_cnt * i;
                    answer_tmp += to_string(zip_cnt + 1).size();                     
                    zip_cnt = 0;
                }
            }
            
            now_word = next_word;
        }
        
        if (answer_tmp < answer) answer = answer_tmp;
        answer_tmp = size;
        zip_cnt = 0;
    }
    
    return answer;
}
