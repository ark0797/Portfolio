# Sorting of wagons lite
#https://contest.yandex.ru/contest/45468/problems/14/

n = int(input())
sp = list(map(float, input().split()))
stack = []
stack.append(sp[0])
rez = []  # список, хранящий результат
for i in range(1, n):
    if sp[i] < stack[-1]:
        stack.append(sp[i])
    else:  # не складываем в стэк, а наоборот надо вывести оттуда
        rez.append(stack.pop())
        while len(stack) != 0:
            if stack[-1] < sp[i]:
                rez.append(stack.pop())
            else:
                break
        stack.append(sp[i])

while len(stack) != 0:
    rez.append(stack.pop())

if rez == sorted(sp):
    print('YES')
else:
    print('NO')