# 디스크 컨트롤러 

def solution(jobs):
    answer = 0
    
    que = []
    work = []
    
    time = 0
    end_time = 0
    total_time = 0
    job_cnt = len(jobs)
    
    while len(jobs) > 0 or len(que) > 0 or len(work) > 0:      
        if len(jobs) > 0:
            new_jobs = []
            for i, j in enumerate(jobs):
                if j[0] == time:
                    que.append(j)
                else:
                    new_jobs.append(j)
            jobs = new_jobs
                
            
        if len(work) == 0 and len(que) > 0:
            # 우선 순위 높은 작업 찾기
            min_time = 1000
            min_idx = 0
            for i, q in enumerate(que):
                if q[1] < min_time:
                    min_time = q[1]
                    min_idx = i
            work.append(que[min_idx])
            end_time = time + que[min_idx][1]
            del que[min_idx]
        
        if len(work) > 0:
            if time == end_time:
                total_time += (time - work[0][0])
                time -= 1
                del work[0]
        
        time += 1    
    
    answer = total_time // job_cnt
    
    return answer
    
    
