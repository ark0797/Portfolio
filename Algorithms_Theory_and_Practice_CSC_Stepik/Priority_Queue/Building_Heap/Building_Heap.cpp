#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Построение минимальной двоичной кучи

// Вход: число элементов массива и сами элементы 
// Выход: кол-во обменов элементов и индексы каждого из обменов 

// получение индекса родителя
int get_parent(int i) {
    return floor((i - 1) / 2);
}

// получение индекса левого ребенка 
int get_left_child(int i) {
    return 2 * i + 1;
}

// получение индекса правого ребенка 
int get_right_child(int i) {
    return 2 * i + 2;
}

// просеивание вниз для кучи минимумов (функция рекурсивная) 
void sift_down(vector<int>& v, int i, int& counter, vector<pair<int, int>>& rez) {
    // здесь ищем минимум из трех элементов (родителей и двух детей)
    int min_ind = i;
    int l = get_left_child(i);
    if (l < v.size() && v[l] < v[min_ind]) {
        min_ind = l;
    }
    int r = get_right_child(i);
    if (r < v.size() && v[r] < v[min_ind]) {
        min_ind = r;
    }
    if (i != min_ind) { // если минимум не совпал с исходным элементом 
        counter++; 
        // делаем обмен элементов 
        int tmp = v[i];
        v[i] = v[min_ind];
        v[min_ind] = tmp;
        pair<int, int> p = { i, min_ind };
        rez.push_back(p);
        sift_down(v, min_ind, counter, rez);
    }
}

// построение кучи (двоичной) минимумов из массива 
void build_min_heap(vector<int>& v) {
    int count = 0; // число перестановок элементов для получения кучи 
    vector<pair<int, int>> rez; // вектор для хранения результата 
    int n = v.size();
    for (int i = floor((n - 1) / 2); i >= 0; --i) {
        sift_down(v, i, count, rez);
    }
    cout << count << endl;
    for (auto& elem : rez) {
        cout << elem.first << ' ' << elem.second << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    build_min_heap(v);
    return 0;
}
