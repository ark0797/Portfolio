# Implementation of the standard queue and its methods
# https://contest.yandex.ru/contest/45468/problems/16/

queue = []
comm = input()
while comm != 'exit':
    if comm == 'size':
        print(len(queue))
    elif comm == 'clear':
        queue.clear()
        print('ok')
    elif comm == 'pop':  # удаление 1 элемента
        if len(queue) == 0:
            print('error')
        else:
            print(queue[0])
            queue = queue[1:]
    elif comm == 'front':
        if len(queue) == 0:
            print('error')
        else:
            print(queue[0])
    else:
        n = int(comm.split()[1])
        queue.append(n)
        print('ok')
    comm = input()

print('bye')