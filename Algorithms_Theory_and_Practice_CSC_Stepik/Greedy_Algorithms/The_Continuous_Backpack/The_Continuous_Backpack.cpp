#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;

// Задача о Непрерывном Рюкзаке (ЖА)
// задано n - кол-во имеющихся предметов, cpt - вместимость рюкзака 
// у каждого предмета есть своя стоимость C и объем W (они могут быть нулями) 
// надо найти максимальную стоимость частей предметов (от каждого предмета мб взята только его часть)
// чтобы они поместились в рюкзак (вывод ответа с точностью не менее 3 знаков) 

// компаратор для встроенной функции sort 
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return ((double)p1.first / p1.second) > ((double)p2.first / p2.second);
}

int main() {
    int n;
    int cpt;
    cin >> n >> cpt;
    int c, w;
    vector<pair<int, int>> sub(n); // вектор предметов 
    for (int i = 0; i < n; ++i) {
        cin >> c >> w;
        sub[i] = { c, w };
    }
    // сортировка идет по максимальной стоимости на ед объема
    sort(sub.begin(), sub.end(), cmp);
    int i = 0;
    double rez = 0; // максим стоимость влезших предметов 
    while (cpt > 0 && i < n) {
        // сначала всегда самый дорогой предмет 
        if (sub[i].first == 0) { // если предмет с 0 ценой, то его не надо в рюкзак - переходим к след 
            ++i;
            continue;
        }
        if (sub[i].second > cpt) { // если объем предмета больше остаточной вместимости рюкзака 
            // добавляем только часть
            rez += ((double)sub[i].first * cpt / sub[i].second);
            cpt = 0;
        }
        else { // текущий объем меньше рюкзака
            rez += sub[i].first; // добавляем полную стоимость, без деления 
            cpt -= sub[i].second;
        }
        ++i;
    }
    cout << fixed << setprecision(3) << rez;
    return 0;
}