#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;
typedef long long int lli; 

// Хэширование Цепочками 

// реализовать хэш-таблицу на основе полиномиальной хэш-функции с заданными паметрами x, p
// к таблице могут подаваться 4 вида запросов (add string, del string, find string, check ind) 
// вывести результат к каждому из них 

const int p = 1000000007; // простое большое число для хэширования 
const int x = 263; // заранее заданный параметр хэш-функции 

// отдельно посчитаем x в степенях (прекальк степеней x) 
vector<lli> power_x() { 
    // строка максимально может состоять из 15 символов (по условию задачи) 
    vector<lli> rez(15);
    rez[0] = 1;
    for (int i = 1; i < 15; ++i) {
        rez[i] = ((rez[i - 1] % p) * (x % p)) % p;
    }
    return rez;
}

// реализация полиномиальной хэш-функции для строк 
lli hash_func(const string& s, int m, vector<lli>& pow_x) {
    lli hash_val = 0;
    for (int i = 0; i < s.size(); ++i) { // идем по всем символам строки 
        lli symb = int(s[i]);
        hash_val += (symb * pow_x[i]);
    }
    return (hash_val % p) % m;
}

// поиск значения в хэш таблице 
bool find_value(const string& s, vector<forward_list<string>>& hash_table, vector<lli>& pow_x) {
    int hash_value = hash_func(s, hash_table.size(), pow_x); // посчитали хэш 
    if (hash_table[hash_value].empty()) return false; // по этому хэшу нет вообще ничего 
    // список оказался не пустой - надо перебрать все его элементы 
    auto it = hash_table[hash_value].begin();
    while (it != hash_table[hash_value].end()) {
        if (*it == s) return true;
        ++it;
    }
    return false; // так и не нашли элемент 
}

int main()
{
    int m; // кол-во ячеек хэш-таблицы 
    cin >> m; 
    int n; // кол-во запросов к таблице 
    cin >> n; 
    vector<forward_list<string>> hash_table(m); // наша хэш-таблица (массив из односвязных списков)
    vector<lli> v = power_x();
    string oper, value;
    int ind;
    for (int i = 0; i < n; ++i) {
        cin >> oper;
        if (oper == "add") { // добавление строки value в ХТ, если ее нет, иначе - ничего 
            cin >> value;
            if (!find_value(value, hash_table, v)) { // добавляем, если только такой строки нет 
                hash_table[hash_func(value, m, v)].push_front(value);
            }
        }
        else if (oper == "del") { // удаление строки value из ХТ, если такое нет, то ничего не делаем 
            cin >> value;
            int hash_value = hash_func(value, m, v); // посчитали хэш 
            if (!hash_table[hash_value].empty()) { // если список по хэшу не пустой 
                auto it = hash_table[hash_value].begin(); // итератор на начало 
                auto prev = hash_table[hash_value].before_begin(); // итератор на предначало 
                while (it != hash_table[hash_value].end()) {
                    if (*it == value) {
                        // метод удаляет элемент после элемента, на ктр указывает итератор (prev)
                        hash_table[hash_value].erase_after(prev);
                        break;
                    }
                    prev = it;
                    ++it;
                }
            }
        }
        else if (oper == "find") { // поиск строки value в ХТ
            cin >> value;
            if (find_value(value, hash_table, v)) { // такая строка есть 
                cout << "yes" << endl;
            }
            else { // такой строки нет 
                cout << "no" << endl;
            }
        }
        else if (oper == "check") { // вывод через пробел всех элементов списка под индексом ind в ХТ
            cin >> ind;
            if (hash_table[ind].empty()) cout << "" << endl;
            else { // вывести все элементы текущего списка
                for (auto& elem : hash_table[ind]) {
                    cout << elem << ' ';
                }
                cout << endl;
            }
        }
    }
    /*forward_list<int> fl;
    fl.push_front(56);
    auto it = fl.before_begin();
    fl.erase_after(it);
    cout << fl.empty();*/
    return 0;
}


