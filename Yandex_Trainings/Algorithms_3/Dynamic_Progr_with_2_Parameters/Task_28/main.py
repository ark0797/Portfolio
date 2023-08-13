# The Knight's move
# https://contest.yandex.ru/contest/45468/problems/28/

n, m = map(int, input().split())
if n == m == 1:
    print(1)
else:
    dp = [[0]*(m+2) for i in range(n+2)]
    dp[2][1] = 1
    dp[1][2] = 1
    #print_matr(dp)
    for i in range(1, n):
        for j in range(1, m):
            if dp[i][j] != 0:
                dp[i+2][j+1] += dp[i][j]
                dp[i+1][j+2] += dp[i][j]
        #print_matr(dp)

    #print_matr(dp)
    print(dp[n-1][m-1])