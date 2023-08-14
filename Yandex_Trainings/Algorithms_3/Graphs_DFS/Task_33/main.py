# The Cheating
# https://contest.yandex.ru/contest/45468/problems/33/

import sys
sys.setrecursionlimit(100001)

def dfs(graph, visited, now, color, colors):
    visited[now] = True
    color = 3 - color
    colors[now] = color
    # print(colors)
    for neig in graph[now]:
        if not visited[neig]:
            dfs(graph, visited, neig, color, colors)
    for neig in graph[now]:
        if colors[neig] == color:  # мы нашли вершину такого же цвета
            raise Exception


v, e = map(int, input().split())
graph = [{0} for i in range(v + 1)]
for i in range(e):
    v1, v2 = map(int, input().split())
    if v1 != v2:
        graph[v1].add(v2)
        graph[v2].add(v1)

visited = [False] * (v + 1)
visited[0] = True
# comp = 0
colors = [0] * (v + 1)
color = 2
f = True
for i in range(1, v + 1):  # v - кол-во вершин
    if not visited[i]:
        try:
            dfs(graph, visited, i, color, colors)
        except Exception:
            f = False
            print('NO')
            break
if f:  # если программа нигде не упала аварийно
    print('YES')
