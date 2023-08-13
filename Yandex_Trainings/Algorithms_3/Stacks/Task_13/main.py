# Postfix Notation (or Reverse Polish Notation)
# https://contest.yandex.ru/contest/45468/problems/13/

sp = input().split()
stack = []
ops = ['+', '-', '*']

for elem in sp:
    if elem not in ops:
        stack.append(int(elem))
    else: # арифм операция
        el1 = stack.pop() # последний
        el2 = stack.pop() # предпоследний
        if elem == '+':
            stack.append(el1 + el2)
        elif elem == '-':
            stack.append(el2 - el1)
        elif elem == '*':
            stack.append(el2 * el1)

print(stack[0])
