# 정수 삼각형

def solution(triangle):
    path_sum = []
    for num in triangle[-1]:
        path_sum.append([num]) #[[4][5][2][6][5]]

    for tri in triangle[-2::-1]: # [2,7,4,4]
        new_path_sum = []
        for idx, num in enumerate(tri): #1,7
            now_path_sum = []
            
            path_arr = path_sum[idx] # [5]
            for path_num in path_arr: #5
                now_path_sum.append(num + path_num) #[7+5]
                
            path_arr = path_sum[idx+1] # [2]
            for path_num in path_arr: # 
                now_path_sum.append(num + path_num) #[12, 7+2]
            new_path_sum.append(now_path_sum) #[[6,7] [12,9]]

        path_sum = new_path_sum
                
    return max(path_sum[0])
  
# 너무 복잡하게 생각하는듯..
