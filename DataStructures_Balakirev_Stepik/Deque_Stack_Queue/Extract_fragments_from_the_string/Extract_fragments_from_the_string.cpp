#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// Extracting fragments of a string inside brackets
void get_sub_eq(const string& eq_str, vector<string>& res)
{
	stack<int> st;
	for (int i = 0; i < eq_str.size(); ++i) {
		if (eq_str[i] == '(') {
			st.push(i);
		}
		else if (eq_str[i] == ')') {
			res.push_back(eq_str.substr(st.top() + 1, i - 1 - st.top()));
			st.pop();
		}
	}
}

int main()
{
	// задание 2 
	string s = "2 + 3 * (1 - 5 - (3 * x - 5)) + (a - b)";
	vector<string> v;
	get_sub_eq(s, v);
	for (auto elem : v) {
		cout << elem << endl;
	}
	// задание 1 (заполнение стека и извлечение с выводом) 
	/*stack<int> st;
	for (int i = 0; i < 5; ++i) {
		st.push(i);
	}
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}*/
	return 0;
}