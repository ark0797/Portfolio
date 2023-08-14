# The Topological Sorting
# https://contest.yandex.ru/contest/45468/problems/34/

import sys
sys.setrecursionlimit(100001)

def dfs(graph, visited, now, colors, rez):
    visited[now] = True
    colors[now] = 1
    # print('vertex', now)
    # print('colors', colors)
    for neig in graph[now]:
        if not visited[neig]:
            dfs(graph, visited, neig, colors, rez)
    # обошли всех соседей тек вершины
    # print('after color', colors)
    f = True
    for neig in graph[now]:
        # print('neig grey', neig)
        if colors[neig] == 1:
            f = False
            raise Exception  # у нас цикл в ор графе
            # значит нет ТС
    if f:
        rez.append(now)
    colors[now] = 2


v, e = map(int, input().split())
graph = [{0} for i in range(v + 1)]
for i in range(e):
    v1, v2 = map(int, input().split())
    graph[v1].add(v2)
    # здесь у нас будут пути из каждой вершины в другие
# print(graph)
visited = [False] * (v + 1)
visited[0] = True
colors = [0] * (v + 1)
rez = []
fl = True
for i in range(1, v + 1):  # v - кол-во вершин
    if not visited[i]:
        try:
            dfs(graph, visited, i, colors, rez)
        except:
            fl = False
            print(-1)
            break
if fl:
    rez.reverse()
    print(*rez)
