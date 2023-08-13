# Implementation of the standard data structure - deque and its main methods
# https://contest.yandex.ru/contest/45468/problems/18/

deque = []
comm = input()
while comm != 'exit':
    if comm == 'front':
        if len(deque) == 0:
            print('error')
        else:
            print(deque[0])
    elif comm == 'back':
        if len(deque) == 0:
            print('error')
        else:
            print(deque[-1])
    elif comm == 'size':
        print(len(deque))
    elif comm == 'clear':
        deque.clear()
        print('ok')
    elif comm == 'pop_front':
        if len(deque) == 0:
            print('error')
        else:
            print(deque[0])
            deque = deque[1:]
    elif comm == 'pop_back':
        if len(deque) == 0:
            print('error')
        else:
            print(deque.pop())
    else:
        cm, n = comm.split()
        if cm == 'push_front':
            deque = [int(n)] + deque
        elif cm == 'push_back':
            deque.append(int(n))
        print('ok')
    comm = input()

print('bye')