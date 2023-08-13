# The maximum cost route
# https://contest.yandex.ru/contest/45468/problems/27/

n, m = map(int, input().split())
M = [0] * n # заранее выделим память
for i in range(n):
    M[i] = list(map(int, input().split()))

# теперь дпшечка
dp = [[0]*(m+1) for i in range(n+1)]
for i in range(1, n+1):
    for j in range(1, m+1):
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + M[i-1][j-1]
print(dp[n][m])
#print(dp)

elem = dp[n][m]
i = n
j = m
rez = []
for i in range(n+1):
    dp[i][0] = -1
for j in range(m+1):
    dp[0][j] = -1
#print(dp)

while i != 0 and j != 0:
    #print(elem)
    if dp[i-1][j] > dp[i][j-1]:
        rez.append('D')
        i -= 1
    else:
        rez.append('R')
        j -= 1
    #print('tmp rez', rez)
    #print(i, j)
    elem = dp[i][j]
rez.pop()
rez.reverse()
print(*rez)