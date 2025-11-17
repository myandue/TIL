# 올바른 괄호

def solution(s):
    answer = True
    
    cnt = 0
    
    for l in s:
        if l == "(":
            cnt += 1
        else:
            cnt -= 1
        
        if cnt < 0:
            answer = False
            break

    if cnt != 0:
        answer = False
        
    return answer