// 조이스틱

#include <string>
#include <vector>

using namespace std;

int solution(string name) {
    int answer = 0;
    int cnt;
    
    // 상하 움직임 계산
    for (char c : name) {
        cnt = c - 'A' > 'Z' - c + 1 ? 'Z' - c + 1 : c - 'A';
        answer += cnt;
    }
    
    // 좌우 움직임 계산 
    // 오른쪽으로 쭉 가는 경우
    cnt = name.size() - 1;
    
    int l;
    int r;
    int cnt_tmp;
    
    for (int i = 0 ; i < name.size() ; i++) {
        if (name[i] == 'A') {
            l = i;
            while (i < name.size() && name[i] == 'A') i++; 
            r = name.size() - i; 
            
            // 현재 A 구간에 대한 계산 
            cnt_tmp = l == 0 ? r : (
                // 왼쪽 왕복 vs 오른쪽 왕복
                ((l-1)*2 + r) < ((r*2-1) + l) ?
                ((l-1)*2 + r) : ((r*2-1) + l)
            );
            
            if (cnt_tmp < cnt) {
                cnt = cnt_tmp;
            }
        }
    }
    
    answer += cnt;
    return answer;
}
