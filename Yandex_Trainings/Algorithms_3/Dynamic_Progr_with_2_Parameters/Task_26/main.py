# The cheapest way
# https://contest.yandex.ru/contest/45468/problems/26/

n, m = map(int, input().split())
M = [[0]*m for i in range(n)]
for i in range(n):
    M[i] = list(map(int, input().split()))
dp = [[1000]*(m+1) for i in range(n+1)]
dp[1][1] = M[0][0]
for j in range(2, m+1):
    dp[1][j] = min(dp[1][j-1], dp[0][j]) + M[0][j-1]
for i in range(2, n+1):
    for j in range(1, m+1):
        dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + M[i-1][j-1]
#print(dp)        
print(dp[n][m])