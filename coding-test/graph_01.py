# 가장 먼 노드
# BFS

from collections import deque

def solution(n, edge):
    answer = 0
    
    connect = [[] for _ in range(n+1)]
    for a,b in edge:
        connect[a].append(b)
        connect[b].append(a)
    
    dist = [-1] * (n+1)
    q = deque([1])
    dist[1] = 0
    
    while q:
        node = q.popleft()
        for next in connect[node]:
            if dist[next] == -1:
                dist[next] = dist[node] + 1
                q.append(next)
    
    max_dist = max(dist)
    answer = dist.count(max_dist)
    
    return answer
