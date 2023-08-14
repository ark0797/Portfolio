# The Speleologist's Way
# https://contest.yandex.ru/contest/45468/problems/39/

n = int(input()) # размерность задачи
# смещения
dp_x = [-1,1,0,0,0,0]
dp_y = [0,0,-1,1,0,0]
dp_z = [0,0,0,0,-1,1]
graph = [[['#']*(n+2) for i in range(n+2)] for i in range(n+2)]
#print(graph)
for i in range(1, n+1): # это z
    s = input() # пустая строка
    for j in range(1, n+1): # это x
        elem = list(input())
        if 'S' in elem:
            from_x, from_y, from_z = j, elem.index('S') + 1, i # положение старта
        graph[i][j][1:n+1] = elem

visited = [[[-1]*(n+2) for i in range(n+2)] for i in range(n+2)]
visited[from_z][from_x][from_y] = 0
#print(visited)
queue = [[from_x, from_y, from_z]] # посещенная вершина
add_vert = 1
while len(queue) != 0:
    counter = 0
    for i in range(add_vert):
        tmp_x, tmp_y, tmp_z = queue[i]
        #print('tmp vert', tmp_x, tmp_y, tmp_z)
        for k in range(6): # 6 соседей
            neig_x = tmp_x + dp_x[k]
            neig_y = tmp_y + dp_y[k]
            neig_z = tmp_z + dp_z[k]
            #print('neig vert', neig_x, neig_y, neig_z)
            # если не решетка, то мы можем туда перемещаться
            if graph[neig_z][neig_x][neig_y] != '#':
                if visited[neig_z][neig_x][neig_y] == -1: # еще не посетили эту вершину
                    visited[neig_z][neig_x][neig_y] = visited[tmp_z][tmp_x][tmp_y] + 1
                    queue.append([neig_x, neig_y, neig_z])
                    counter += 1
    #print('added vert', counter)
    queue = queue[add_vert:]
    #print(queue)
    add_vert = counter
answ = visited[1]
rez = []
for i in range(1, n+1):
    for j in range(1, n+1):
        if answ[i][j] != -1:
            rez.append(answ[i][j])
print(min(rez))
