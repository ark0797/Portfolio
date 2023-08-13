# The Great Lineland Migration
# https://contest.yandex.ru/contest/45468/problems/15/

n = int(input())
sp = list(map(float, input().split()))

rez = [-1] * len(sp)  # список для хранения результата

stack = []
for i in range(len(sp)):
    if len(stack) == 0:
        stack.append([sp[i], i])
    else:  # если стэк не пуст
        tmp = stack[-1]
        if sp[i] >= tmp[0]:
            stack.append([sp[i], i])
        else:  # если элемент меньше, то выталкиваем все,что строго больше него
            stack.pop()
            rez[tmp[1]] = i
            while len(stack) != 0:
                tmp = stack[-1]
                if tmp[0] > sp[i]:
                    stack.pop()
                    rez[tmp[1]] = i
                else:
                    break
            stack.append([sp[i], i])
print(*rez)
