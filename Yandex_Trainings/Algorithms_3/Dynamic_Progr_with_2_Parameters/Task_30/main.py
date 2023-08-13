# The greatest common subsequence (GCS) with the recovery of the answer
# https://contest.yandex.ru/contest/45468/problems/30/

n = int(input())
sp1 = list(map(int, input().split()))
m = int(input())
sp2 = list(map(int, input().split()))
dp = [[0] * (m + 1) for i in range(n + 1)]

for i in range(1, n + 1):
    for j in range(1, m + 1):
        if sp1[i - 1] != sp2[j - 1]:
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
        else:  # если элементы совпадают, то +1 к диаг
            dp[i][j] = dp[i - 1][j - 1] + 1
elem = dp[n][m]  # последний элемент
rez = []
i = n
j = m
while elem != 0:
    # если диаг элементы совпадают
    if dp[i - 1][j] == dp[i][j - 1]:
        if dp[i - 1][j] != elem:
            rez.append(sp1[i - 1])
            i -= 1
            j -= 1
        else:
            i -= 1
    elif dp[i - 1][j] > dp[i][j - 1]:
        i -= 1
    else:
        j -= 1
    elem = dp[i][j]

# print(rez)
rez.reverse()
print(*rez)
