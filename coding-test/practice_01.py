# 혼자 놀기의 달인
def solution(cards):
    cards_len = len(cards)
    answer_list = []
    for i in range(cards_len):
        check = [-1] * len(cards)
        
        a = 0
        num = i + 1
        while True:
            if check[num - 1] == 1:
                break
            else:
                a += 1
                check[num - 1] = 1
                num = cards[num - 1]
                
        b_max = 0
        for j in range(cards_len):
            if check[j] == -1:
                b = 0
                num = j + 1
                while True:
                    if check[num - 1] == 1:
                        if b > b_max:
                            b_max = b
                        break
                    else:
                        b += 1
                        check[num - 1] = 1
                        num = cards[num - 1]
                        
        answer_list.append(a*b_max)
        
    return max(answer_list)