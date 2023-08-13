# Buying tickets
# https://contest.yandex.ru/contest/45468/problems/24/

n = int(input())
M = [list(map(int, input().split())) for i in range(n)]
if n == 1:
    print(M[0][0])
elif n == 2:
    print(min(M[0][0] + M[1][0], M[0][1]))
else: # n >= 3
    dp = [0] * n # заранее выделяем память
    dp[0] = M[0][0]
    dp[1] = min(M[0][0] + M[1][0], M[0][1])
    dp[2] = min(M[0][0] + M[1][0] + M[2][0], M[0][1]+ M[2][0], M[0][0] + M[1][1], M[0][2])
    for i in range(3, n):
        dp[i] = min(dp[i-1] + M[i][0], dp[i-2] + M[i-1][1], dp[i-3] + M[i-2][2])
    print(dp[-1])