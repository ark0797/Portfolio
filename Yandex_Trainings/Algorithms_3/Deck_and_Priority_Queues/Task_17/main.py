# The Drunkard's Game
# https://contest.yandex.ru/contest/45468/problems/17/

pl1 = list(map(int, input().split()))
pl2 = list(map(int, input().split()))
spec = [0, 9]
k = 0
f = True
while len(pl1) != 0 and len(pl2) != 0:
    v1 = pl1[0]
    v2 = pl2[0]
    pl1 = pl1[1:]
    pl2 = pl2[1:]
    if v1 in spec and v2 in spec:
        if v1 < v2:  # выигрывает 1
            pl1.append(v1)
            pl1.append(v2)
        else:  # выигрывает второй
            pl2.append(v1)
            pl2.append(v2)
    else:
        if v1 > v2:  # выигрывает 1
            pl1.append(v1)
            pl1.append(v2)
        else:
            pl2.append(v1)
            pl2.append(v2)
    k += 1

    if k >= 1000000:
        print('botwa')
        f = False
        break

if f:  # если остались тру, то есть победитель
    if len(pl1) != 0:
        print(f"first {k}")
    else:
        print(f"second {k}")