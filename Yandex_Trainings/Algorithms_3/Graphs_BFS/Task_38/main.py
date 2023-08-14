# The Fleas
# https://contest.yandex.ru/contest/45468/problems/38/

n, m, s, t, q = map(int, input().split())
if q == 0: # если блох нет вообще, то по идее сбор невозможен
    print(-1)
else:
    graph = [[-2]*(m+4) for i in range(n+4)]
    for i in range(2, n+2):
        graph[i][2:m+2] = [-1] *(m+2-2)
    coord = [[0] for i in range(q)]
    for i in range(q): # для каждой блохи
        x, y = map(int, input().split()) # считали коорд текущей блохи
        coord[i] = (x, y)
    # запускаем 1 раз обход в ширину из положения кормушки
    visited = [[-1] *(m) for i in range(n)]
    queue = []
    visited[s-1][t-1] = 0 # из этой вершины начали
    queue.append((s+1, t+1)) # коорд блохи именно в графе
    add_vert = 1 # кол-во добавл вершин в очередь
    # массивчики сдвигов по x, y
    dp_x = [-1,1,-1,1,2,2,-2,-2]
    dp_y = [2,2,-2,-2,-1,1,-1,1]
    while len(queue) != 0:
        k = 0
        for i in range(add_vert):
            tmp_x_gr, tmp_y_gr = queue[i]
            for i in range(8):
                #print(neig)
                x_neig, y_neig = tmp_x_gr + dp_x[i], tmp_y_gr + dp_y[i]
                #print('tmp neig', x_neig, y_neig)
                if graph[x_neig][y_neig] != -2:
                    if visited[x_neig-2][y_neig-2] == -1: # если еще не посещено
                        visited[x_neig-2][y_neig-2] = visited[tmp_x_gr - 2][tmp_y_gr-2] + 1
                        queue.append((x_neig, y_neig))
                        k += 1
        queue = queue[add_vert:]
        add_vert = k
    rez = 0
    for i in range(q): # сколько блох
        x, y = coord[i]
        if visited[x-1][y-1] == -1:
            print(-1)
            break
        else:
            rez += visited[x-1][y-1]
    else: # если закончили без брейков
        print(rez)
