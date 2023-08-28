#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

// Задача: покрыть отрезки точками (ЖА) 
// Есть n отрезков, заданных началом x и концом y 
//найти мн-во точек минимального размера, чтобы каждый отрезок содержал хотя бы 1 из точек 

// компаратор 
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    // по возрастанию второго аргумента 
    return p1.second < p2.second;
}

int main() {
    int n;
    cin >> n;
    int x, y;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        v[i] = { x, y };
    }
    sort(v.begin(), v.end(), cmp);
    /*for (int i = 0; i < n; ++i) {
        cout << v[i].first << ' ' << v[i].second;
        cout << endl;
    }*/
    // надежный шаг - минимум второго аргумента
    vector<int> rez;
    rez.push_back(v[0].second);
    int i = 1;
    while (i < n) {
        if (v[i].first > rez[rez.size() - 1]) {
            rez.push_back(v[i].second);
        }
        ++i;
    }
    cout << rez.size() << endl;
    for (int k = 0; k < rez.size(); ++k) {
        cout << rez[k] << ' ';
    }
    return 0;
}