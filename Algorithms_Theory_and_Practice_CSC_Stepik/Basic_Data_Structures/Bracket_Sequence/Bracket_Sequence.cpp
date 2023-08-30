#include <iostream>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

// Задача - проверить правильно ли расставлены скобки в коде (скобки 3 видов)
// (при решении использован стек и дек)

// если верная расстановка, то выводим Success
// если - неверная, то надо вывести индекс первой закрывающейся скобки, для которой нет пары
// иначе, индекс первой открывающейся для которой нет пары 

int main() {
	// скобки всех тех видов (), {}, []
	string s; // исходная скобочная последовательность 
	cin >> s;
	stack<char> st;
	deque<int> ind;
	bool f = true;
	for (int i = 0; i < s.size(); ++i) {
		char ch = s[i];
		if (ch == ']' || ch == '}' || ch == ')') {
			if (st.empty()) { // стек пуст, а уже закрытая скобка
				cout << i + 1;
				f = false;
				break;
			}
			else {
				// проеряем соответсвие пар 
				if ((ch == ']' && st.top() != '[') || (ch == '}' && st.top() != '{')
					|| (ch == ')' && st.top() != '(')) {
					cout << i + 1;
					f = false;
					break;
				}
				else { // пара схлопывается
					st.pop();
					ind.pop_back(); // удаляем индекс с конца 
				}
			}
		}
		else if (ch == '[' || ch == '{' || ch == '(') { // подается открытая скобка 
			st.push(ch);
			ind.push_back(i + 1);
		}
	}
	if (f) {
		if (st.empty()) cout << "Success";
		else cout << ind.front(); // индекс самой первой открытой скобки 
	}
	return 0;
}