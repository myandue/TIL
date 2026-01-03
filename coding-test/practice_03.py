# 하노이의 탑 

answer = []

def solution(n):
    hanoi(1,2,3,n)
    return answer

def hanoi(start, mid, end, n):    
    if(n==1):
        answer.append([start, end])
        return 
    elif(n==2):
        answer.append([start, mid])
        answer.append([start, end])
        answer.append([mid, end])
        return 
    else:
        hanoi(start, end, mid, n-1)
        answer.append([start, end])
        hanoi(mid, start, end, n-1)
