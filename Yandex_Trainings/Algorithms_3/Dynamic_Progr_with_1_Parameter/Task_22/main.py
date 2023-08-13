# Grasshopper (Кузнечик)
# https://contest.yandex.ru/contest/45468/problems/22/

def create_steps(k):
    dp = [0] * (k+1)
    dp[0] = 0
    dp[1] = 1
    sm = 1
    for i in range(2, k+1):
        dp[i] = sm + 1
        sm += dp[i]
    return dp

n, k = map(int, input().split())
if n == 1:
    print(1)
else: # n > 1
    rez = create_steps(k)
    if n <= (k + 1):
        print(rez[n-1])
    else: # n > (k + 1)
        for i in range(k+1, n):
            elem = sum(rez[len(rez)-k:len(rez)])
            rez.append(elem)
        print(rez[-1])