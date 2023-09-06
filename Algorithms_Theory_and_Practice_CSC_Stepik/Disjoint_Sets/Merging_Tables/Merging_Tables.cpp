#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Симуляция объединения таблиц в Базе Данных 

// в БД есть n таблиц и подается m запросов объединения 
// (каждая таблица содержит либо реальные записи, либо символьную ссылку на родителя)
// дана строка размеров (исходных) каждой таблицы (может быть и 0) - кол-во записей 
// далее идут m столбцов вида destination source
// надо присоединить source к destination с очищением источника (размер source становится 0) 
// + записываем в корень source символьную ссылку на корень destination
// Выход: для каждого запроса надо вывести маскимальный текущий размер среди всех таблиц 

// задача решается с помощью понимания системы непересекающихся множеств и как они строятся на корневых деревьях

// поиск корня (родителя/идентификатора) для каждой вершины реализован с помощью эвристики сжатия путей 
int find_root(int ind, vector<int>& parent) {
    if (ind != parent[ind]) {
        parent[ind] = find_root(parent[ind], parent);
    }
    return parent[ind];
}

int main()
{
    int n, m;
    cin >> n >> m; // считываем кол-во таблиц и кол-во запросов 
    vector<int> size(n); // вектор размеров каждой из таблиц 
    vector<int> parent(n);
    for (int i = 0; i < n; ++i) {
        cin >> size[i];
        parent[i] = i; // каждый элемент есть singleton в самом начале (то есть сам корень) 
    }
    // надо найти максимум среди этих размеров 
    int mx_size = *max_element(size.begin(), size.end());
    int dest, source;
    for (int i = 0; i < m; ++i) { // считываем запросы 
        cin >> dest >> source;
        // сразу здесь будем писать обработку запросов 
        // надо найти корни для обеих таблиц 
        int dest_root = find_root(dest-1, parent); // корень таблицу, в ктр копируем 
        int source_root = find_root(source - 1, parent); // корень таблицы, из ктр копируем 
        if (dest_root == source_root) { // ничего не меняется - они в одном множестве 
            cout << mx_size << endl; // выводим текущий максимум 
        }
        else {
            size[dest_root] += size[source_root]; // обновляем размер приемника 
            size[source_root] = 0; // зануляем размер источника 
            parent[source_root] = dest_root; // делаем символьную ссылку на приемника у источника 
            if (size[dest_root] > mx_size) { 
                // обновляем максимум 
                mx_size = size[dest_root];
            }
            cout << mx_size << endl;
        }
    }
    return 0;
}

