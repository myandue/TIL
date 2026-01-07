# 삼각 달팽이 

def solution(n):
    arr = []
    
    for i in range(n):
        arr.append([])
        for j in range(i+1):
            arr[i].append(0)
    
    cnt = 0
    num = 1
    insert_amt = n 
    
    while True:
        a = cnt // 3 
        if cnt%3 == 0:
            y = a 
            x = y * 2 
            for i in range(insert_amt): 
                arr[x][y] = num 
                x += 1 
                num += 1
        elif cnt%3 == 1:
            y = a + 1 
            x = n - y 
            for i in range(insert_amt): 
                arr[x][y] = num 
                y += 1
                num += 1
        elif cnt%3 == 2:
            x = n - 2 - a
            y = x - a
            for i in range(insert_amt, 0, -1): 
                arr[x][y] = num 
                x -= 1
                y -= 1
                num+=1

        cnt += 1 
        insert_amt -= 1 
        
        if cnt == n: 
            break

    answer = []
    for i in arr:
        for j in i:
            answer.append(j)
    
    return answer
