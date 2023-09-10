#include <iostream>
#include <vector>
using namespace std;

// Реализация простой структуры данных, что эффективно будет поддерживать запросы типа:
// add number name - внести в таблицу пару (name, number)
// del number - удалить запись по номеру телефона (если такого нет, то ничего не делать)
// find number - найти имя name по номеру телефона (если такого номера нет, то not found) 
// любой номер телефона содержит не более 7 цифр 

// Практика реализации хэш-таблицы методом прямой адресации (самый простой способ на массиве) 


int main()
{
    int n; // число запросов
    cin >> n;
    string oper, name;
    int number;
    vector<string> hash_table(10000000, ""); // хэш-таблица 
    for (int i = 0; i < n; ++i) {
        cin >> oper;
        if (oper == "add") { // добавление пары 
            cin >> number >> name;
            hash_table[number] = name;
        }
        else if (oper == "del") { // удаление по номеру телефона 
            cin >> number;
            hash_table[number] = "";
        }
        else if (oper == "find") { // поиск имени по номеру 
            cin >> number;
            if (hash_table[number] == "") cout << "not found" << endl;
            else {
                cout << hash_table[number] << endl;
            }
        }
    }
    return 0;
}

