#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Максимум в скользящем окне (уровень Hard из LeetCode)
// дана последовательность из n чисел 
// найти максимум в каждом окне длиной m внутри этой последовательности (окна идут последовательно)
// решение реализую через 4 стека 


int main()
{
    stack<int> st_push; // стек для хранения элементов (извлекать можем только при полном заполнении)
    stack<int> st_push_mx; // стек для максимумов хранимых элементов 
    stack<int> st_pop; // стек для извлечения элементов 
    stack<int> st_pop_mx; // стек для максимумов извлекаемых элементов 
    int n, m;
    cin >> n; // кол-во элементов в сиходном массиве 
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    cin >> m; // размер скользящего окна 
    for (int i = 0; i < n; ++i) {
        st_push.push(v[i]);
        if (st_push_mx.size() == 0) st_push_mx.push(v[i]); // если еще стек максимумов пустой 
        else { // если не пустой, то уже нужны проверки 
            if (v[i] < st_push_mx.top()) {
                st_push_mx.push(st_push_mx.top());
            }
            else {
                st_push_mx.push(v[i]);
            }
        }
        // здесь надо проивести сравнение двух стеков максимумов для текущего значения максимума 
        // это делаем только если стек максимумов извлечения не пуст 
        if (st_pop_mx.size() != 0) {
            if (st_push_mx.top() >= st_pop_mx.top()) {
                cout << st_push_mx.top() << ' ';
            }
            else {
                cout << st_pop_mx.top() << ' ';
            }
            // теперь надо удалить уже ненужный элемент в стеке извлечения
            st_pop.pop();
            st_pop_mx.pop();
        }
        if (st_push.size() == m) { // стек заполнения предельно заполнен 
            // здесь надо реализовать перемещение из стека заполнения в стек извлечения 
            for (int j = 0; j < m; ++j) {
                int elem = st_push.top();
                st_push.pop();
                st_push_mx.pop();
                st_pop.push(elem);
                if (st_pop_mx.size() == 0) st_pop_mx.push(elem);
                else { // если не пустой стек максимумов 
                    if (elem < st_pop_mx.top()) {
                        st_pop_mx.push(st_pop_mx.top());
                    }
                    else {
                        st_pop_mx.push(elem);
                    }
                }
            }
            // после всей процедуры перемещения из стека заполнения в стек извлечения - надо извлечь
            cout << st_pop_mx.top() << ' ';
            st_pop_mx.pop();
            st_pop.pop();
        }
    }
    //for (auto& elem : v) cout << elem << ' ';
    return 0;
}

