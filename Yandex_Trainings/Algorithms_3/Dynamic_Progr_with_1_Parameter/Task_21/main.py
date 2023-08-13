# Three units in a row
# https://contest.yandex.ru/contest/45468/problems/21/

n = int(input())
if n == 1:
    print(2)
elif n == 2:
    print(4)
else:
    dp = [0]*(n+1)
    dp[0] = 1
    dp[1] = 2
    dp[2] = 4
    for i in range(3, n+1):
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3]
    print(dp[n])