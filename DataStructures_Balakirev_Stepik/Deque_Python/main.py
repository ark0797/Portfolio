from collections import deque

dq = deque([1, 2, 3, 4, 5])
print(dq)
dq1 = deque()
try:
    dq1.pop()
except IndexError as err:
    print(err)

dq1 = deque((1, 2, 3))
dq1.insert(1, 100)
print(dq1)

data = list(map(int, input().split()))  # этот список в программе не менять
buff = deque([], maxlen = 10)
for elem in data:
    buff.appendleft(elem)
print(buff.pop(), end = ' ')
print(buff.pop(), end = ' ')
print(buff.pop(), end = ' ')