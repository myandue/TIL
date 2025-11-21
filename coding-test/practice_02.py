# 점 찍기 
import math

def solution(k, d):
    cnt = 0
    for i in range(0, d+1, k):
        a = math.sqrt(d**2 - i**2)
        cnt += (a//k + 1)
        
    return cnt
