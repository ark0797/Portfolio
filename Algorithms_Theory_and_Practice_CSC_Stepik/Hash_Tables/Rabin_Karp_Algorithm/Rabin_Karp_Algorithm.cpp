#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;

// Поиск образца в тексте (на алгоритме Рабина-Карпа)
// найти индексы всех вхождений строки Pattern в строку Text 

// работаем с полиномиальной хэш-функцией с параметрами указанными ниже в виде констант 

const int p = 1000000007;
const int x = 263;

// нужно посчитать столько степеней x, сколько составляет длина образца + 1 (доп нужды, когда образец из 1 символа) 
vector<lli> power_x(int size) {
    vector<lli> rez(size + 1);
    rez[0] = 1;
    for (int i = 1; i < (size+1); ++i) {
        rez[i] = ((rez[i - 1] % p) * (x % p)) % p;
    }
    return rez;
}

// реализация полиномиальной хэш-функции для строк 
lli hash_func(const string& s, int ind_beg, vector<lli>& pow_x) {
    // ind_beg - с какого индекса в строке начинаем считать хэш 
    lli hash_val = 0;
    int ind = 0;
    for (int i = ind_beg; i < s.size(); ++i) { // идем по всем символам строки 
        //lli symb = int(s[i]) % p;
        lli symb = int(s[i]) % p;
        // hash_val += (symb * pow_x[ind]) % p;
        hash_val += (symb * (pow_x[ind] % p)) % p;
        ind++;
    }
    return (hash_val % p);
}

lli hash_const(char symb_new, char symb_old, lli lash_last, vector<lli>& pow_x) {
    lli sumnd1 = int(symb_new) % p; // слагаемое 1 (summand)
    //lli a1 = int(symb_old) % p;
    //lli a2 = pow_x[pow_x.size() - 2] % p;
    //lli a3 = a1 * a2;
    //lli a4 = a3 % p;
    lli sumnd2 = ((int(symb_old) % p) * (pow_x[pow_x.size() - 2] % p)) % p; // слагаемое 2 
    lli diff = lash_last - sumnd2; // это число може быть отрицательным (надо аккуратно считаь остатки)
    // формула для подсчета остатка, если число отрицательное
    lli diff_mod = ((diff % p) + p) % p;
    lli tmp = (diff_mod * (pow_x[1] % p)) % p;
    return (tmp % p + sumnd1 % p) % p;
}


int main()
{
    string pattern, text;
    cin >> pattern >> text;
    // сначала надо посчитаь хэш для образца 
    int patrn_size = pattern.size(); // длина образца
    int text_size = text.size();
    vector<lli> x_pow = power_x(patrn_size); // вектор для степеней x
    lli patrn_hash = hash_func(pattern, 0, x_pow);
    // далее надо считать хэши для подстрок текста, начиная с конца 
    // хэш для самого последнего окна считаем честно
    lli last_hash = hash_func(text, text_size - patrn_size, x_pow);
    // далее для каждого следующего хэша влево будет пересчет хэша не напрямую 
    // lli hash_const(char symb_new, char symb_old, lli lash_last, vector<lli>& pow_x)
    vector<lli> hash_vals(text_size - patrn_size + 1); // ровно столько вхождений образца в текст 
    hash_vals[text_size - patrn_size] = last_hash;
    int last_ind = text_size - 1;
    // идем по тексту влево до самого первого символа 
    for (int i = text_size - patrn_size - 1; i >= 0; --i) {
        lli tmp_hash = hash_const(text[i], text[last_ind], last_hash, x_pow);
        hash_vals[i] = tmp_hash;
        last_ind--;
        last_hash = tmp_hash;
    }
    // далее сравниваем хэши для образца и окон, если равны, то надо сделать еще посимвольную проверку 
    for (int i = 0; i < (text_size - patrn_size + 1); ++i) {
        if (patrn_hash == hash_vals[i]) {
            // делаем посимвольную проверку 
            int ind = 0;
            bool f = true;
            for (int j = i; j < (i + patrn_size); ++j) {
                if (pattern[ind] != text[j]) {
                    f = false;
                    break;
                }
                ind++;
            }
            if (f) {
                cout << i << ' '; // распечатка индекса первого вхождения 
            }
        }
    }
    return 0;
}

