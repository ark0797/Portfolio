# The Pins
# https://contest.yandex.ru/contest/45468/problems/25/

n = int(input())
sp = sorted(list(map(int, input().split())))
if n == 2:
    print(sp[1] - sp[0])
else:
    dp = [0] * (n)
    dp[1] = sp[1] - sp[0]
    dp[2] = dp[1] + sp[2] - sp[1]
    #print(dp)
    for i in range(3, n):
        dp[i] = min(dp[i-2], dp[i-1]) + sp[i] - sp[i-1]
    #print(dp)
    print(dp[n-1])
