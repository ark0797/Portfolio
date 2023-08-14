# The path in the graph
# https://contest.yandex.ru/contest/45468/problems/37/

v = int(input())
# превратим матрицу смежности в список смежности
graph = [{0} for i in range(v + 1)]
for i in range(1, v + 1):
    tmp = list(map(int, input().split()))
    for j in range(v):
        if tmp[j] == 1:
            graph[i].add(j + 1)

from_vert, to_vert = map(int, input().split())
# надо хранить предков вершин
pred = [-1] * (v + 1)
visited = [-1] * (v + 1)
visited[0] = -2  # у нас нет такой вершины, это заглушка
visited[from_vert] = 0
pred[from_vert] = 0
queue = []
queue.append(from_vert)
add_vert = 1
while len(queue) != 0:
    k = 0
    for i in range(add_vert):
        tmp_vert = queue[i]
        for neig in graph[tmp_vert]:
            if visited[neig] == -1:
                pred[neig] = tmp_vert
                visited[neig] = visited[tmp_vert] + 1
                k += 1
                queue.append(neig)
    # удалять надо ровно add_vert Элементов из начала
    queue = queue[add_vert:]
    add_vert = k

answ = visited[to_vert]
print(answ)
if answ != -1 and answ != 0:
    rez = []
    rez.append(to_vert)
    rez.append(pred[to_vert])
    tmp_vert = pred[to_vert]
    while pred[tmp_vert] != 0:
        rez.append(pred[tmp_vert])
        tmp_vert = pred[tmp_vert]
    rez.reverse()
    print(*rez)
