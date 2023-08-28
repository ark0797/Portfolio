#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;

// Задача Различные Натуральные Слагаемые (ЖА)
// по данному числу n найти максимальное число k, для которого исходное n мж представить
// как сумму различных k натуральных слагаемых 
// 6 -> 1 2 3, 11 -> 1 2 3 5 

int main() {
    int n;
    cin >> n;
    vector<int> rez;
    int sm = 0;
    int d = n;
    for (int i = 1; i <= n; ++i) {
        d -= i; // остаток от исходного числа минус текущее натуральное число 
        if (d > i) {
            rez.push_back(i); // добавляем текущее салагаемое 
            sm += i;
        }
        else if (d == 0) { // ровно влезли в наше исходное число 
            rez.push_back(i);
            break;
        }
        else { // d < i
            // ровно не влезли, значит, надо добавить разность от исходного и набранной суммы 
            rez.push_back(n - sm);
            break;
        }
    }
    cout << rez.size() << endl;
    for (int i = 0; i < rez.size(); ++i) {
        cout << rez[i] << ' ';
    }
    return 0;
}