#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
using namespace std;
typedef long long int lli;


//Тех Задание

// (Описание в классе LongTable)
// Cервер хранит очень длинную таблицу, строки ктр отсортированы в некотором порядке 
// таблица живая и поддерживает несколько сотен (десятков) изменений в секунду 
// она поддерживает операции добавления (insert_row), обновления (update_row) и удаления (delete_row_by_ind, delete_row_by_data) строк 
// (Описание в классе ClientTable)
// Далее существует клиент, у ктр памяти недостаточно для выгрузки всей таблицы, а доступно лишь окно высотой N (scrol_param) строк 
// в этом окне есть скроллер, с помощью ктр можно передвигаться вверх (scroll_up), вниз (scroll_down) и к определенной строке (scroll_to_ind)
// также пользователь может сортировать отображаемые у него данные по любому столбцу (sort_client_table)


// класс для описания таблицы на сервере 
class LongTable {
public:
    map<lli, vector<string>> table;
    int cols;

    // конструктор класса таблицы на сервере (параметр - кол-во столбцов) 
    LongTable(int cols) {
        this->cols = cols;
    }

private:
    // функция-проверка на правильный размер вектора 
    bool check_vector_size(vector<string>& value) {
        if (value.size() != cols) return false;
        return true;
    }

public:
    // обновление записи по текущему индексу 
    int update_row(lli ind, vector<string>& value) {
        auto it = table.find(ind);
        if (it == table.end()) {
            cout << "there is no such key in table" << endl;
            return -1; // error 
        }
        if (!check_vector_size(value)) {
            cout << "invalid size of vector" << endl;
            return -2;
        }
        table.erase(it);
        table.insert({ ind, value });
        return 0;
    }

    // вставка новой пары (записи) в таблицу 
    // если по такому индексу запись уже есть, то проброс ошибки 
    // ++
    int insert_row(lli ind, vector<string> value) {
        if (!check_vector_size(value)) {
            cout << "InsertError: invalid size of vector" << endl;
            return -2;
        }
        if (table.find(ind) != table.end()) {
            cout << "InsertError: this index is already in the table" << endl;
            return -3;
        }
        table.insert({ ind, value });
        return 0;
    }

    // удаление записи из таблицы по индексу (идентификатору) 
    // ++
    int delete_row_by_ind(lli ind) {
        if (table.find(ind) == table.end()) {
            cout << "DeleteIndError: this index is not in the table" << endl;
            return -4;
        }
        table.erase(ind);
        cout << "Successful delete by index" << endl;
        return 0;
    }

    // удаление записи из таблицы по данным 
    // ++ 
    int delete_row_by_data(vector<string> value) {
        if (!check_vector_size(value)) {
            cout << "DeleteDataError: invalid size of vector" << endl;
            return -2;
        }
        for (auto& item : table) {
            if (item.second == value) {
                table.erase(item.first);
                cout << "Successful delete by data" << endl;
                return 0;
            }
        }
        cout << "DeleteDataError: no such data in the table" << endl;
        return -5;
    }

    // распечатка серверной таблицы в консоль 
    // ++
    void print_server_table() {
        cout << "Full Server Table: " << endl;
        for (auto& item : table) {
            cout << item.first << ": ";
            for (auto& elem : item.second) {
                cout << elem << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

};

// взаимодействие между сервером и клиентом пропишем через внешние функции 

// получение таблицы клиентом (строк ровно столько - чему равен параметр скроллинга) 
map<lli, vector<string>> response_to_client_on_start(LongTable& tb, int scrol_param) {
    map<lli, vector<string>> mp;
    int i = 0;
    for (auto it = tb.table.begin(); it != tb.table.end(); ++it) {
        if (i < scrol_param) {
            mp.insert(*it);
            ++i;
        }
        else {
            return mp;
        }
    }
    return mp;
}

// получение пары по индексу из таблицы на сервере 
pair<int, vector<string>> get_pair(LongTable& tb, int ind) {
    int i = 0;
    for (auto it = tb.table.begin(); it != tb.table.end(); ++it) {
        if (i == ind) {
            return *it;
        }
        ++i;
    }
    //cout << "GetPairError: no such pair in the table" << endl;
    pair<int, vector<string>> p(NULL, NULL);
    return p;
}


// класс для описания таблицы на клиенте 
class ClientTable {
public:
    map<lli, vector<string>> table;
    int scrol_param = 5; // параметр, заранее заданный 
    int pos_now = 0;
    int cols; // кол-во стобцов 
    vector<vector<string>> sorted_table; // копия данных в другой структуре 
    int flag;

    // конструктор таблицы на клиенте
    // ++
    ClientTable(LongTable& tb) {
        map<lli, vector<string>> table = response_to_client_on_start(tb, scrol_param);
        this->table = table;
        this->cols = tb.cols;
        vector<vector<string>> sorted_tb;
        for (auto& item : table) {
            vector<string> tmp = item.second;
            tmp.push_back(to_string(item.first));
            sorted_tb.push_back(tmp);
        }
        this->sorted_table = sorted_tb;
        this->flag = -1; // данные не сортированы 
    }

public:
    // методы скроллинга 

    // скроллинг на 1 строку вниз (с учетом сортировки) 
    // +++
    void scroll_down(LongTable& tb) {
        pair<int, vector<string>> tmp_pair = get_pair(tb, pos_now + scrol_param);
        if (tmp_pair.first == NULL) {
            cout << "ScrollDownError: not allowed to scroll down" << endl;
            return;
        }
        if (flag == -1) { // данные не отсортированы 
            auto it = table.begin();
            table.erase(it);
            table.insert(tmp_pair);
            pos_now++;
            return;
        }
        // если уже отсортировано, то надо сделать сортировку
        //vector<string> tmp = item.second;
        //tmp.push_back(to_string(item.first));
        //sorted_tb.push_back(tmp);
        vector<string> tmp = tmp_pair.second;
        tmp.push_back(to_string(tmp_pair.first));
        sorted_table.push_back(tmp);
        sort_client_table(flag + 1);
        pos_now++;
        return;
    }

    // скроллинг на 1 строку вверх 
    // +++
    void scroll_up(LongTable& tb) {
        if (pos_now == 0) {
            cout << "ScrollUpError: not allowed to scroll up" << endl;
            return;
        }
        pair<int, vector<string>> tmp_pair = get_pair(tb, pos_now - 1);
        if (tmp_pair.first == NULL) {
            return;
        }
        if (flag == -1) { // данные не отсортированы 
            auto it = table.end();
            if (table.size() >= scrol_param) {
                table.erase(--it);
            }
            table.insert(tmp_pair);
            pos_now--;
            return;
        }
        vector<string> tmp = tmp_pair.second;
        tmp.push_back(to_string(tmp_pair.first));
        if (sorted_table.size() >= scrol_param) {
            sorted_table.pop_back();
        }
        sorted_table.push_back(tmp);
        sort_client_table(flag + 1);
        pos_now--;
        return;
    }

    // скроллинг к строке по определенному индексу - она будет отображаться в самом верху 
    // ++ 
    // если скроллим к определенному индексу, то сортировка обнуляется 
    void scroll_to_ind(LongTable& tb, lli ind) {
        pair<int, vector<string>> tmp_pair = get_pair(tb, ind);
        if (tmp_pair.first == NULL) {
            cout << "ScrollIndError: there is no such index in the table" << endl;
            return;
        }
        flag = -1; // обнуление сортировки 
        table.clear();
        table.insert(tmp_pair);
        pos_now = ind;
        for (int i = 1; i < scrol_param; ++i) {
            pair<int, vector<string>> tmp_pair = get_pair(tb, ind + i);
            if (tmp_pair.first != NULL) {
                table.insert(tmp_pair);
            }
        }
        vector<vector<string>> sorted_tb;
        for (auto& item : table) {
            vector<string> tmp = item.second;
            tmp.push_back(to_string(item.first));
            sorted_tb.push_back(tmp);
        }
        this->sorted_table = sorted_tb;
    }

    // сортировка по любому введенному столбцу 
    void sort_client_table(int col) {
        if (col <= 0 || col > cols) {
            cout << "SortColError: there is no such column number in the table" << endl;
            return;
        }
        // такой номер столбца существует 
        // я работаю со струткурой sorted_table (vector<vector<string>>)
        int ind = col - 1;
        flag = ind; // во флаге содержим параметр отсортированности 
        for (int i = 0; i < sorted_table.size() - 1; ++i) {
            int left = 0;
            int step = 0;
            int right = left + 1;
            for (int j = 0; j < sorted_table.size() - 1; ++j) {
                if (sorted_table[left][ind] > sorted_table[right][ind]) {
                    auto elem = sorted_table[left];
                    sorted_table[left] = sorted_table[right];
                    sorted_table[right] = elem;
                }
                left = right;
                right = left + 1;
            }
        }
    }


    // распечатка таблицы клиента в консоль 
    // ++ 
    void print_client_table() {
        cout << "Temporary Client Table: " << endl;
        if (flag == -1) { // неотсортированное состояние 
            for (auto& item : table) {
                cout << item.first << ": ";
                for (auto& elem : item.second) {
                    cout << elem << ' ';
                }
                cout << endl;
            }
            cout << endl;
            return;
        }
        // отсортированное состояние 
        for (auto& item : sorted_table) {
            cout << item[item.size() - 1] << ": ";
            for (int i = 0; i < item.size() - 1; ++i) {
                cout << item[i] << ' ';
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

};

// в этой функции проведено тестирование 
int main()
{
    LongTable ltb(3);
    vector<string> v1 = { "mama", "papa", "brat" };
    vector<string> v2 = { "ded", "baba", "sos" };
    //vector<string> v3 = { "luch", "dwaff", "peppa", "ger"};
    //vector<string> v4 = { "dwaff", "peppa" };
    vector<string> v5 = { "sea", "my", "futur" };
    vector<string> v6 = { "fff", "foo", "had" };
    vector<string> v7 = { "exx", "oracle", "mine" };
    vector<string> v8 = { "furth", "machine", "blizzard" };
    vector<string> v9 = { "loy", "posit", "neg" };
    vector<string> v10 = { "lek", "urge", "gaig" };
    vector<string> v11 = { "moon", "nein", "ipol" };
    ltb.insert_row(3, v1);
    ltb.insert_row(1, v2);
    ltb.insert_row(2, v5);
    ltb.insert_row(28, v6);
    ltb.insert_row(4, v7);
    ltb.insert_row(9, v8);
    ltb.insert_row(2019, v9);
    ltb.insert_row(1000, v10);
    ltb.insert_row(15, v11);
    ltb.print_server_table();

    ClientTable cltb(ltb);
    cltb.print_client_table();
    //cltb.sort_client_table(1);
    //cltb.print_client_table();
    cltb.scroll_to_ind(ltb, 4);
    cltb.print_client_table();
    cltb.sort_client_table(1);
    cltb.print_client_table();
    cltb.scroll_down(ltb);
    cltb.print_client_table();
    cltb.scroll_down(ltb);
    cltb.print_client_table();
    cltb.sort_client_table(1);
    cltb.print_client_table();
    /*cltb.scroll_down(ltb);
    cltb.scroll_down(ltb);
    cltb.scroll_down(ltb);
    cltb.scroll_up(ltb);
    cltb.scroll_up(ltb);*/
    //cltb.scroll_to_ind(ltb, 9);
    //cltb.scroll_down(ltb);
    //cltb.scroll_down(ltb);
    //cltb.scroll_down(ltb);
    //cltb.scroll_down(ltb);
    //cltb.scroll_down(ltb);


    //auto p = get_pair(ltb, 5);
    //cout << p.first;

    //ltb.insert_row(10, v4);
    //ltb.insert_row(1, v2);
    //ltb.insert_row(2, v3);
    //ltb.delete_row_by_data({ "mama", "papa", "brat" });
    //ltb.delete_row_by_data({ "ded", "baba", "sos" });
    //ltb.delete_row_by_data({ "mama", "papa", "brat" });
    //ltb.delete_row_by_ind(1);
    //ltb.delete_row_by_ind(3);
    //ltb.delete_row_by_ind(5);*/
    return 0;
}
