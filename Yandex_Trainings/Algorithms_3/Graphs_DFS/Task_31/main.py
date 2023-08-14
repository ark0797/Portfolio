# Depth-First Search
# https://contest.yandex.ru/contest/45468/problems/31/

import sys
sys.setrecursionlimit(100001)

def dfs(graph, visited, now):
    visited[now] = True
    for neig in graph[now]:
        if not visited[neig]:
            dfs(graph, visited, neig)

# сначала сделаем список смежности
v, e = map(int, input().split())

graph = [{0} for i in range(v+1)]
for i in range(e):
    v1, v2 = map(int, input().split())
    if v1 != v2:
        graph[v1].add(v2)
        graph[v2].add(v1)
#print(graph)
visited = [False]*(v+1)
visited[0] = True
dfs(graph, visited, 1)
#print(visited)
k = 0
rez = []
for i in range(1, v+1):
    if visited[i] == True:
        k += 1
        rez.append(i)
print(k)
print(*rez)