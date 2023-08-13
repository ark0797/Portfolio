# Implementation of a HEAP to store integers with its standard methods
#https://contest.yandex.ru/contest/45468/problems/19/

# добавление элемента в кучу максимумов
def push_heap(sp, x):
    sp.append(x)  # сначала этот элемент добавляем
    tmp_pos = len(sp) - 1  # текущая позиция нашего элемента
    while tmp_pos > 0 and sp[tmp_pos] > sp[(tmp_pos - 1) // 2]:
        sp[tmp_pos], sp[(tmp_pos - 1) // 2] = sp[(tmp_pos - 1) // 2], sp[tmp_pos]
        tmp_pos = (tmp_pos - 1) // 2

    # удаление узла из кучи + куча должна преобразоваться


def pop_heap(sp):
    answ = sp[0]  # извлекли верхушку
    sp[0] = sp[-1]  # копируем в верхушку последний элемент
    tmp_pos = 0
    while 2 * tmp_pos + 2 <= len(sp) - 1:
        max_son_ind = 2 * tmp_pos + 1
        if sp[max_son_ind] < sp[2 * tmp_pos + 2]:
            max_son_ind = 2 * tmp_pos + 2
        if sp[tmp_pos] < sp[max_son_ind]:
            sp[tmp_pos], sp[max_son_ind] = sp[max_son_ind], sp[tmp_pos]
        else:  # если я уже стою правильно
            break
        tmp_pos = max_son_ind
    sp.pop()  # удаление последнего элемента
    return answ


n = int(input())
heap = []
for _ in range(n):
    cm = input()
    if cm == '1':  # extract
        print(pop_heap(heap))
    else:  # insert
        numb = int(cm.split()[1])
        push_heap(heap, numb)