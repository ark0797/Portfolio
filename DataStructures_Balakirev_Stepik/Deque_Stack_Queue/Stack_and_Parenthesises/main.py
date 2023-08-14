# выделение выражений из строки внутри скобок квадратных и круглых

from collections import deque

def get_sub_eq(eq_str):
    st1 = deque()
    res = []
    st2 = deque()
    for i, x in enumerate(eq_str):
        if x == "(":
            st1.append(i)
        elif x == ")":
            res.append(eq_str[st1.pop()+1: i])
        elif x == '[':
            st2.append(i)
        elif x == ']':
            res.append(eq_str[st2.pop() + 1: i])
    return res


s = "2 + 3 * (1 - 5 - [3 * (x) - 5]) + (a - b)"
res = get_sub_eq(s)
print(res)