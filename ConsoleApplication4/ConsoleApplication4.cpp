#include <iostream>
#include <vector>
#include <string>
# include <set>
#include <algorithm>
using namespace std;
typedef long long int64; // создали константу для удобства 

void print_vector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    int64 x;
    set<int64> st;
    for (int i = 0; i < n; i++) {
        cin >> x;
        string s = "";
        auto it = st.find(x);
        if (it == st.end()) {
            st.insert(x); // добавили элемент, ктр нет
            s = s + '0' + ' ';
            it = st.find(x);
        }
        else {
            s = s + '1' + ' ';
        }
        // максим число, меньшее x или -, если не существует
        if (it == st.begin()) {
            s = s + '-' + ' ';
        }
        else {
            auto x = *(it--);
            s = s + to_string(x) + ' ';
        }
        // минимальное число, большее чем X
        it = st.find(x); // поиск справа
        if ((it++) == st.end()) {
            s = s + '-';
        }
        else {
            auto y = *(it++);
            s = s + to_string(y);
        }
        cout << s << endl;
    }
    for (auto elem : st) {
        cout << elem << ' ';
    }
}

