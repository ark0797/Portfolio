# The Cafe
# https://contest.yandex.ru/contest/45468/problems/29/

n = int(input())
M = [[0]*n for i in range(n)]
for i in range(n):
    M[i][0] = int(input())
#print(M)
dp = [[10000]*(n+3) for i in range(n+1)]
#dp[0][1] = dp[0][0] = 0
dp[0][1] = 0
for i in range(1, n+1):
    for j in range(1, n+2):
        #print('tmp elem', M[i-1][0])
        if M[i-1][0] > 100:
            #print('case 1')
            dp[i][j] = min(dp[i-1][j+1], dp[i-1][j-1] + M[i-1][0])
            #print(dp[i][j])
        else: # <= 100
            #print('case 2')
            dp[i][j] = min(dp[i-1][j+1], dp[i-1][j] + M[i-1][0])
            #print(dp[i][j])
mn = min(dp[n])
tmp = dp[n][:] # копия массива
tmp.reverse()
ind = n + 2 - tmp.index(mn)
j = ind
days = []
k_use = 0
for i in range(n, 0, -1):
    if dp[i][j] == dp[i-1][j+1]: # точно воспользовались купоном в этот день
        days.append(i)
        j += 1
        k_use += 1
    else: # если не равны, то надо понять, какой у нас элемент > 100 или нет
        if M[i-1][0] > 100:
            j -= 1
# Ответ задача
print(mn)
len_days = len(days)
print(ind - 1, len_days)
if len_days != 0:
    days.reverse()
    for elem in days:
        print(elem)