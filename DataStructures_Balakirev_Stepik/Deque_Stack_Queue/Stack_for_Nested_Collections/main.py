# Stack for hierarchical sorting of nested collections
# отбираем элементы из data в res по порядку уровня вложенности, сохраняя порядок исходного следования

from collections import deque

def get_flat_data(data):
    st = deque()
    work_st = deque(data)
    res = []
    while work_st:
        for elem in work_st:
            print('elem', elem)
            if type(elem) != list:
                res.append(elem)
            else: # тип List
                print('here')
                for inner_elem in elem:
                    print('inner_elem', inner_elem)
                    st.append(inner_elem)
        work_st = st.copy()
        print('work_st', work_st)
        st.clear()
    return res


data = [1, "abc", [[100, 200], 10, 20], [30, 40]]
dat = ['a', 'b', [['c', 'd'], 'e'], [[['f', 'g'], 'e'], 'd'], 'r']
res = get_flat_data(dat)
print(res)

