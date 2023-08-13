# The Calculator
# https://contest.yandex.ru/contest/45468/problems/23/

n = int(input())
if n == 1:
    print(0)  # кол-во шагов
    print(1)
else:
    dp = [0] * (n + 1)
    pred = [0] * (n + 1)
    dp[2] = 1
    pred[2] = 1
    for i in range(3, n + 1):
        if i % 2 == 0 and i % 3 == 0:
            if dp[i // 2] < dp[i // 3]:
                dp[i] = dp[i // 2] + 1
                pred[i] = i // 2
            else:
                dp[i] = dp[i // 3] + 1
                pred[i] = i // 3

        elif i % 2 == 0:
            if dp[i // 2] < dp[i - 1]:
                dp[i] = dp[i // 2] + 1
                pred[i] = i // 2
            else:
                dp[i] = dp[i - 1] + 1
                pred[i] = i - 1
        elif i % 3 == 0:
            if dp[i // 3] < dp[i - 1]:
                dp[i] = dp[i // 3] + 1
                pred[i] = i // 3
            else:
                dp[i] = dp[i - 1] + 1
                pred[i] = i - 1
        else:
            pred[i] = i - 1
            dp[i] = dp[i - 1] + 1

    print(dp[n])
    rez = [0] * (dp[n]+1)
    rez[0] = n
    i = 1
    ind = n # индекс, с ктр начинаем
    prev = pred[ind]
    rez[i] = prev
    i += 1
    ind = prev
    prev = pred[ind]
    # И так до тех пор пока prev не станет 0
    while prev != 0:
        rez[i] = prev
        i += 1
        ind = prev
        prev = pred[ind]
    rez.reverse()
    print(*rez)