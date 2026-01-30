# 쿼드압축 후 개수 세기
# 통과하기는 했는데 이렇게 복잡할 수 밖에 없나..?

zero_cnt = 0
one_cnt = 0

def solution(arrs):
    main(arrs)
    
    return [zero_cnt, one_cnt]

def main(arrs):
    global zero_cnt
    global one_cnt
    
    if len(arrs) == 1:
        if arrs[0][0] == 1:
            one_cnt += 1
            return
        else:
            zero_cnt += 1
            return
    
    same = True
    first_num = arrs[0][0]
    for arr in arrs:
        for num in arr:
            if num != first_num:
                same = False
                break
        if same == False:
            break
    
    if same:
        if first_num == 1:
            one_cnt += 1
        else:
            zero_cnt += 1
    else:
        length = int(len(arrs) / 2)
        arr_1 = []
        arr_2 = []
        arr_3 = []
        arr_4 = []
        for arr in arrs[0:length]:
            arr_1.append(arr[0:length])
            arr_2.append(arr[length:])
        for arr in arrs[length:]:
            arr_3.append(arr[0:length])
            arr_4.append(arr[length:])
        
        main(arr_1)
        main(arr_2)
        main(arr_3)
        main(arr_4)
        return
    
