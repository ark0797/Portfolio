# Determining the correct bracket sequence via using a stack
#https://contest.yandex.ru/contest/45468/problems/12/

s = input()
stack = []
for skobk in s:
    if skobk == '(' or skobk == '[' or skobk == '{':
        stack.append(skobk)
    else: # встретили закрыв скобку
        if len(stack) == 0:
            print('no')
            break
        else: # длина стэка не 0
            last_elem = stack[-1] # последний элемент
            if (skobk == '}' and last_elem == '{') or (skobk == ')' and last_elem == '(') or (skobk == ']' and last_elem == '['):
                stack.pop()
            else:
                print('no')
                break
else:
    if len(stack) == 0:
        print('yes')
    else:
        print('no')