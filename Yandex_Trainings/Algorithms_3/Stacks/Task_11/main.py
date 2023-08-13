# Just simple Stack Implementation on dynamic array with standard methods
#https://contest.yandex.ru/contest/45468/problems/11/

stack = []
s = input()
while s != 'exit':
    if s == 'pop':
        if len(stack) != 0: # стэк не пустой
            print(stack.pop())
        else:
            print('error')
    elif s == 'back':
        if len(stack) != 0:
            print(stack[-1])
        else:
            print('error')
    elif s == 'size':
        print(len(stack))
    elif s == 'clear':
        stack.clear()
        print('ok')
    else:
        elem = int(s.split()[1])
        stack.append(elem)
        print('ok')
    s = input()
print('bye')