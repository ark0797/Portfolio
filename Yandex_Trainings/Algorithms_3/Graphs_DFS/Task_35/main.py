# The Cycle Search
# https://contest.yandex.ru/contest/45468/problems/35/

import sys
sys.setrecursionlimit(100001)

def dfs(graph, visited, now, ancestor, rez, f):
    visited[now] = True
    colors[now] = 1
    predok[now] = ancestor
    ancestor = now
    for neig in graph[now]:
        if not visited[neig]:
            dfs(graph, visited, neig, ancestor, rez, f)
    colors[now] = 2
    for neig in graph[now]:
        if colors[neig] == 1 and neig != predok[now]:
            # print('YES')
            f = True
            predok[neig] = now
            break
    if f:
        rez.append(now)
        elem = predok[now]
        while elem != now:
            rez.append(elem)
            elem = predok[elem]
        raise Exception


v = int(input())
graph = [{0} for i in range(v + 1)]
for i in range(1, v + 1):
    tmp = list(map(int, input().split()))
    for j in range(v):
        if tmp[j] == 1:
            graph[i].add(j + 1)
# print(graph)
rez = []
visited = [False] * (v + 1)
visited[0] = True
colors = [0] * (v + 1)
predok = [0] * (v + 1)
ancestor = 0
logic = True  # нет цикла
for i in range(1, v + 1):  # v - кол-во вершин
    if not visited[i]:
        f = False
        try:
            dfs(graph, visited, i, ancestor, rez, f)
        except Exception:
            logic = False  # есть цикл
            print('YES')
            print(len(rez))
            print(*rez)
            break
if logic:
    print('NO')