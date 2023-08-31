#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Реализация стека с поддержкой максимума 

// при этом все операции должны происходить за константное время 
// push elem - положить элемент в стек (O(1))
// pop - удалить элемент с вершины стека (O(1))
// max - максимум всех элементов стека (операция производится также за O(1), так как поддерживаем
// дополнительный стек максимумов на текущем шаге) 

int main() {
	vector<int> st;
	vector<int> st_mx; // доп стек с максимумами
	int real_size = 0; // кол-во элементов в стеке 
	int q; // кол-во запросов 
	string oper;
	cin >> q;
	getline(cin, oper); // костыль для считывания пустой строки 
	for (int i = 0; i < q; ++i) {
		getline(cin, oper);
		if (oper == "pop") { // удаление последнего элемента 
			// если стек оказался пуст, то наша программа не должна падать 
			if (real_size != 0) {
				st.pop_back(); // удаляем последний элемент для непустого стека
				st_mx.pop_back(); // и для стека максимумов дублируем удаление 
				real_size--;
			}
		}
		else if (oper.substr(0, 4) == "push") { // добавление элемента наверх стека 
			int elem = stoi(oper.substr(5, oper.size() - 5)); // элемент, что добавляем в стек
			st.push_back(elem);
			if (real_size == 0) st_mx.push_back(elem);
			else {
				if (elem >= st_mx[real_size - 1]) { // добавляем максимум 
					st_mx.push_back(elem);
				}
				else {
					st_mx.push_back(st_mx[real_size - 1]);
				}
			}
			real_size++;
		}
		else if (oper == "max") { // поиск максимума в стеке 
			if (real_size != 0) {
				cout << st_mx[real_size - 1] << endl;
			}
		}
	}
	return 0;
}


