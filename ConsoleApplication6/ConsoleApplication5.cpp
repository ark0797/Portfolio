#include <iostream>
#include <vector>
#include <string>
#include <map>
# include <set>
#include<deque>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long long int lli;

lli Mod(lli a, lli x) {
	return ((a % x) + x) % x;
}

lli ModSub(lli a, lli b, lli x) {
	return Mod(Mod(a, x) - Mod(b, x), x);
}

lli ModSum(lli a, lli b, lli x) {
	return Mod(Mod(a, x) + Mod(b, x), x);
}

lli ModMult(lli a, lli b, lli x) {
	return Mod(Mod(a, x) * Mod(b, x), x);
}

void print_vector(vector<int>& v) {
	for (auto elem : v) cout << elem << " ";
	cout << endl;
}

void print_double_vector(vector<vector<int>>& v) {
	for (auto elem : v) {
		print_vector(elem);
	}
	cout << endl;
}

void filling_units(int n, int pos, int k, vector<vector<int>>& v) {
	// заполнение единицами
	// по горизонтали
	for (int j = 0; j < n; ++j) {
		v[pos][j] = 1;
	}
	// по вертикали
	for (int i = 0; i < n; ++i) {
		v[i][k] = 1;
	}
	// правая нижняя диагональ
	int d = 1;
	while ((pos + d) < n && (k + d) < n) {
		v[pos + d][k + d] = 1;
		d++;
	}
	// левая верхняя диагональ
	d = -1;
	while ((pos + d) >= 0 && (k + d) >= 0) {
		v[pos + d][k + d] = 1;
		d--;
	}
	// правая верхняя диагональ
	d = 1;
	while ((pos - d) >= 0 && (k + d) < n) {
		v[pos - d][k + d] = 1;
		d++;
	}
	// левая нижняя диагональ 
	d = 1;
	while ((pos + d) < n && (k - d) >= 0) {
		v[pos + d][k - d] = 1;
		d++;
	}
	print_double_vector(v);
}

// рекурсивная функция
/*int rez = 0;
int ferz(int n, int k, vector<vector<int>>& v) {
	vector<int> pos_x;
	// заполняем возможные позиции ферзей, то есть там, где 0 
	for (int i = 0; i < n; ++i) {
		if (v[i][k] == 0) pos_x.push_back(i);
	}
	if (pos_x.size() == 0) {
		return 0;
	}
	if (k == (n - 1)) {
		return pos_x.size();
	}
	for (auto pos : pos_x) {
		// заполняем единицами 
		filling_units(n, pos, k, v);
		return (rez + ferz(n, k + 1, v));
	}
}*/


void print_vector_1(vector<string>& v) {
	for (auto elem : v) cout << elem << " ";
	cout << endl;
}
 
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	/*int n; // размер поля 
	cin >> n;
	vector<vector<int>> v(n, vector<int>(n, 0));
	cout << ferz(n, 0, v);*/
	//print_double_vector(v);
	
}