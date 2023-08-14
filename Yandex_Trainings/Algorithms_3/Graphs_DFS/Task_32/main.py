# Сounting the connectivity components of a graph
# https://contest.yandex.ru/contest/45468/problems/32/

import sys
sys.setrecursionlimit(100001)

def dfs(graph, visited, now, comp):
    visited[now] = True
    for neig in graph[now]:
        if not visited[neig]:
            dfs(graph, visited, neig, comp)


def dfs_adv(graph, visited, now, comp, links):
    visited[now] = True
    links.append(now)
    for neig in graph[now]:
        if not visited[neig]:
            dfs_adv(graph, visited, neig, comp, links)


v, e = map(int, input().split())
graph = [{0} for i in range(v + 1)]
for i in range(e):
    v1, v2 = map(int, input().split())
    if v1 != v2:
        graph[v1].add(v2)
        graph[v2].add(v1)

visited = [False] * (v + 1)
visited[0] = True
comp = 0
for i in range(1, v + 1):  # v - кол-во вершин
    if not visited[i]:
        dfs(graph, visited, i, comp)
        comp += 1
print(comp)

visited = [False] * (v + 1)
visited[0] = True
for i in range(1, v + 1):  # v - кол-во вершин
    if not visited[i]:
        links = []
        dfs_adv(graph, visited, i, comp, links)
        print(len(links))
        print(*links)