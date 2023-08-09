#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
    char name[100];     // наименование экспоната
    int weight;         // вес экспоната (в граммах)
    short old;          // возраст экспоната (число лет)
} EXHIBIT;

typedef struct {
    char fio[100];			// ФИО студента
    vector<char>* marks;	// динамический массив для оценок
} STUDENT;

typedef struct {
    char model[50];		// модель
    short year;		// год выпуска
    int distance;		// пробег (в  км.)
    short power;		// мощность (в л.с.)
} AUTO;

void copy_to_array(std::vector<EXHIBIT>& dest, const std::list<EXHIBIT>& src)
{
    // копирование значений двусвязного списка src в динамич массив dest
    for (auto it = src.cbegin(); it != src.cend(); ++it) {
        dest.push_back(*it);
    }
}

bool cmp(EXHIBIT& ex1, EXHIBIT& ex2) {
    return ex1.old < ex2.old;
}

void filter_auto(const std::list<AUTO>& autos, std::list<AUTO>* results)
{
    for (auto it = autos.cbegin(); it != autos.end(); ++it) {
        if ((*it).year < 2014) {
            results->push_back(*it);
        }
    }
}

template <typename T>
void insert_to_list(list<T>& lst, unsigned int pos, const T& value)
{
    // переопределение метода insert, чтобы работа была через индекс, а не через итераторы
    auto iter = lst.begin();
    for (int k = 0; k < pos; ++iter, ++k);
    lst.insert(iter, value);
}

template <typename T>
void copy_to_lst(vector<T>& src, list<T>& dest)
{
    // копирование значений вектора src в двусвязный список dest
    for (auto it = src.cbegin(); it != src.cend(); ++it) {
        dest.push_back(*it);
    }
}

int main()
{
    // задача 7 
    list<int> d_lst;
    vector<int> d_in = {1,2,3,4,5};
    copy_to_lst(d_in, d_lst);
    insert_to_list(d_lst, 2, -3);
    insert_to_list(d_lst, 3, -5);

    // задача 6
    /*setlocale(LC_ALL, "RUS");
    list<AUTO> autos;
    AUTO a1 = { "порше", 2005, 200430, 143};
    autos.push_back(a1);
    AUTO a2 = { "тойота", 2011, 80754, 124 };
    autos.push_back(a2);
    AUTO a3 = { "опель", 2017, 75730, 147 };
    autos.push_back(a3);
    AUTO a4 = { "бмв", 2015, 100450, 230 };
    autos.push_back(a4);
    AUTO a5 = { "мерседес", 2004, 245034, 156 };
    autos.push_back(a5);
    list<AUTO>* results = new list<AUTO>();
    filter_auto(autos, results);
    for (auto it = results->begin(); it != results->end(); ++it) {
        cout << (*it).model << ' ';
    }*/
    /*vector<int>* v = new vector<int>(5);
    v->push_back(4);
    v->at(0) = 4;
    list<int>* results = new list<int>();
    results->push_back(4);
    results->push_back(8);*/
    //auto iter = results->begin();
    //*iter = 10;
    
    // задача 5
    /*setlocale(LC_ALL, "RUS");
    list<STUDENT> students;
    vector<char>* marks1 = new vector<char>({ 1, 2, 3, 4, 5 });
    STUDENT s1 = { "Галий Ю.",  marks1};
    students.push_back(s1);
    vector<char>* marks2 = new vector<char>({ 5, 3, 5, 2, 5, 5 });
    STUDENT s2 = { "Аврелий М.", marks2 };
    students.push_back(s2);
    vector<char>* marks3 = new vector<char>({ 2,4});
    STUDENT s3 = { "Балакирев С.", marks3 };
    students.push_back(s3);
    delete marks1;
    delete marks2;
    delete marks3;*/

    // задача 4 
    //list<int> lst = {3,10,22,4,9,0,22,43};
    //int x;
    /*while (!feof(stdin)) {
        cin >> x;
        lst.push_back(x);
    }*/
    /*auto iter = lst.cbegin();
    ++iter;
    lst.insert(++iter, -1);
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == 22) {
            lst.erase(it);
            break;
        }
    }
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == 8) {
            lst.erase(it);
            break;
        }
    }
    lst.push_back(100);
    lst.push_front(-100);
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << ' ';
    }*/

    // задание 3
    /*setlocale(LC_ALL, "RUS");
    list<EXHIBIT> exhibits;
    vector<EXHIBIT> vex;
    EXHIBIT ex1 = { "Евангелие от Матфея", 1020, 800 };
    EXHIBIT ex2 = { "Евангелие от Марка", 1100, 921 };
    EXHIBIT ex3 = { "Евангелие от Иоанна", 1205, 1024 };
    EXHIBIT ex4 = { "Python от ван Россума", 256, 32 };
    EXHIBIT ex5 = { "С++ от Страуструпа", 128, 28 };
    EXHIBIT ex6 = { "Структуры данных от Балакирева", 16, 1 };
    exhibits.push_back(ex1);
    exhibits.push_back(ex2);
    exhibits.push_back(ex3);
    exhibits.push_back(ex4);
    exhibits.push_back(ex5);
    exhibits.push_back(ex6);
    copy_to_array(vex, exhibits);
    // отсортировать экспонаты в порядке возрастания веса 
    // исходный список не менять 
    sort(vex.begin(), vex.end(), cmp);
    for (auto it = vex.cbegin(); it != vex.cend(); ++it) {
        cout << (*it).old << ' ';
    }
    cout << endl;
    for (auto it = vex.cbegin(); it != vex.cend(); ++it) {
        cout << (*it).weight << ' ';
    }*/

    // задача 2 
    /*list<unsigned int> lst;
    vector<unsigned int> ar_d;
    int a[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
        lst.push_back(a[i]);
    }
    copy_to_array(ar_d, lst);*/

    // задача 1
    //list<short> lst = {1,2};
    //short x;
    /*while (!feof(stdin)) {
        cin >> x;
        lst.push_back(x);
    }*/
    /*for (auto iter = lst.cbegin(); iter != lst.cend(); ++iter) {
        cout << *iter << ' ';
        if (iter != (--lst.cend())) ++iter;
    }*/

    return 0;
}

