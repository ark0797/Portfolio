#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Обработчик сетевых пакетов (Симулятор обработки сетевых пакетов) 

// Вход: размер буфера size и число пакетов n 
// далее для каждого пакета в отлельной строке время прибытия arr и длительность его обработки dur
// Выход: для каждого пакета время начала его обработки или -1 (если пакет поступил в тот момент,
// когда буфер уже полный [там уже size пакетов])


int main()
{
    int size, n;
    cin >> size >> n;
    if (n == 0) return 0; // пакетов нет 
    deque<pair<int, int>> dq; // очередь с исходными данными 
    int arr, dur;
    for (int i = 0; i < n; ++i) {
        cin >> arr >> dur;
        pair<int, int> p = { arr, dur };
        dq.push_back(p);
    }
    if (size == 0) return 0; // буфера нет 

    vector<int> rez(n, 0); // вектор для хранения результата 
    deque<vector<int>> process;
    int ind = 0;
    pair<int, int> tmp = dq.front(); // берем первый пакет из очереди 
    vector<int> tmp_pack = {ind, tmp.first, tmp.first + tmp.second};
    process.push_back(tmp_pack); 
    int tm = tmp.first + tmp.second; // время 
    ind++;
    dq.pop_front(); // удаляем элемент из начала 
    bool f = false;

    while (!dq.empty()) { // пока исходная очередь содержит пакеты на обработку 
        tmp = dq.front();  
        if (process.size() != size) { // пока буфер не переполнен 
            if (process.size() == 0) { // если оказалось равно 0, то надо задать новое время
                tmp = dq.front();
                tm = tmp.first + tmp.second;
                tmp_pack = { ind, tmp.first, tmp.first + tmp.second };
                process.push_back(tmp_pack);
                dq.pop_front();
                ind++;
            }
            else {
                // можно добавлять пока arr[i] < tm
                // при определении времени надо смотреть на последний добавленный 
                if (tmp.first < tm) {
                    vector<int> last_add = process.back();
                    tmp_pack = { ind, last_add[2], last_add[2] + tmp.second};
                    process.push_back(tmp_pack); // добавляем пакет в процессор 
                    dq.pop_front(); // удаляем его из очереди 
                    ind++; // индекс на следующем пакете 
                }
                else { // если время прибытия больше чем время на обработку первого в буфере
                // надо идти в обработку 
                    f = true; // сигнал, что надо идти в обработку
                }
            }
        }
        else { // буфер полностью заполнился
            // надо -1 пометить все пакеты, что не влезут 
            if (tmp.first < tm) { // этот уже не влезает в буфер 
                rez[ind] = -1; 
                dq.pop_front(); // удаляем этот пакет - он не будет обработан никогда 
                ind++;
            }
            else { // идем в обработку 
                f = true;
            }
        }
        if (f) { // прописываем процесс обработки 
            // только по 1 пакету 
            tmp_pack = process.front(); // достали текущий пакет
            rez[tmp_pack[0]] = tmp_pack[1];
            process.pop_front(); // удаляем этот пакет 
            if (process.size() != 0) {
                tmp_pack = process.front();
                tm = tmp_pack[2]; // обновили время 
            }
            f = false; // меняем флаг обработки 
        }
    }
    // здесь надо дописать обработку оставшихся пакетов в процессоре (если он не пуст) 
    while (!process.empty()) {
        tmp_pack = process.front();
        rez[tmp_pack[0]] = tmp_pack[1];
        process.pop_front(); // удаляем этот пакет 
    }
    for (auto& elem : rez) {
        cout << elem << endl;
    }
    return 0;
}

