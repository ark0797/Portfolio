#include <iostream>
#include <vector>
#include <deque>
#include <math.h>
using namespace std;
typedef long long int lli;

// Параллельная обработка 
// Вход: число процессоров n и число задач m
// Для каждой задачи также известно время ее обработки dur
// Выход: для каждой задачи определить каким процессором и в какое время она будет обработана 
// (каждая задача поступает на обработку первому свободному процессору) 


// надо реализовать кучу минимумов (она будет вектором векторов из 4 элементов) 
// задача реализована с помощью процедурного подхода (для простоты не использую ООП) 

// получение индекса родителя 
int get_parent(int i) {
    return floor((i - 1) / 2);
}

// получение индекса левого ребенка 
int get_left_child(int i) {
    return 2 * i + 1;
}

// получение индекса правого ребенка 
int get_right_child(int i) {
    return 2 * i + 2;
}

// просеивание вверх для кучи минимумов 
void sift_up(int ind, vector<vector<lli>>& heap) {
    // корневой элемент вверх не просеиваем 
    while (ind > 0 && heap[ind][2] <= heap[get_parent(ind)][2]) {
        if (heap[ind][2] < heap[get_parent(ind)][2]) { // если меньше, то доп проверки не нужны 
            // меняем местами 
            vector<lli> tmp = heap[ind];
            heap[ind] = heap[get_parent(ind)];                                                                                                                                                                                                                                                                                                                                                                                                                                             
            heap[get_parent(ind)] = tmp;
        }
        else { // случай равенства - надо сравнивать по процессорам (минимальный номер проц приоритетнее)
            if (heap[ind][0] < heap[get_parent(ind)][0]) { // у текущего индекса меньше процессор
                vector<lli> tmp = heap[ind];
                heap[ind] = heap[get_parent(ind)];
                heap[get_parent(ind)] = tmp;
            }
        }
        ind = get_parent(ind);
    }
}

void insert_heap(vector<lli>& tmp_elem, vector<vector<lli>>& heap, int& heap_size) {
    heap[heap_size] = tmp_elem;
    // далее надо сделать просеивание вверх 
    sift_up(heap_size, heap);
    heap_size++; // куча увеличилась на 1 элемент 
}

// просеивание вниз для кучи минимумов (=утопление элемента) 
// это рекурсивная функция 
void sift_down(int ind, vector<vector<lli>>& heap, int& heap_size) {
    // необходимо выбрать минимум из 3 элементов 
    int mn_ind = ind;
    int left = get_left_child(ind);
    if (left < heap_size && heap[left][2] <= heap[mn_ind][2]) {
        if (heap[left][2] < heap[mn_ind][2]) {
            mn_ind = left;
        }
        else { // если равны, то сравниваем по процессорам 
            if (heap[left][0] < heap[mn_ind][0]) {
                mn_ind = left;
            }
        }
    }
    int right = get_right_child(ind);
    if (right < heap_size && heap[right][2] <= heap[mn_ind][2]) {
        if (heap[right][2] < heap[mn_ind][2]) {
            mn_ind = right;
        }
        else { // если равны, то сравниваем по процессорам 
            if (heap[right][0] < heap[mn_ind][0]) {
                mn_ind = right;
            }
        }
    }
    if (ind != mn_ind) { // если минимум не совпал 
        vector<lli> tmp = heap[ind];
        heap[ind] = heap[mn_ind];
        heap[mn_ind] = tmp;
        sift_down(mn_ind, heap, heap_size);
    }
}

vector<lli> extract_min(vector<vector<lli>>& heap, int& heap_size) {
    vector<lli> mn = heap[0]; // минимум лежит в корне 
    // делаем обмен минимума с последним листовым элементом 
    heap[0] = heap[heap_size - 1];
    heap_size--;
    // далее идет просеивание вниз
    sift_down(0, heap, heap_size);
    return mn; // возвращаем наш минимум 
}


int main()
{
    int n, m;
    cin >> n >> m; // считываем кол-во процессоров и кол-во задач 
    deque<lli> dq; // в этой очереди хранится время, необходимое на обработку каждой задачи
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        dq.push_back(x);
    }
    vector<vector<lli>> heap(n); // двоичная куча минимумов 
    vector<pair<int, lli>> rez(m); // вектор для хранения результата 
    int heap_size = 0; // изначально куча пустая 
    lli tm = 0;
    int ind = 0;
    int process, numb;
    lli tm_beg, tm_end;
    vector<lli> tmp_task, mn;
    while (!dq.empty()) { // пока дек не пуст (там есть задачи) 
        // каждую задачу надо добавить в кучу 
        // можно добавлять только до максимального размера кучи (равного числу процессоров)
        if (heap_size != n) { // еще есть свободные процессора 
            if (dq.front() == 0) { // особый случай, когда процессор сразу освобождается 
                // тогда он вновь берет работу на себя 
                rez[ind] = make_pair(heap_size, tm);
                ind++;
                dq.pop_front();
                continue;
            }
            // каждый элемент кучи - вектор, содержащий 4 значения ниже 
            process = heap_size; // номер процессора 
            tm_beg = tm; // время начала обработки 
            tm_end = tm + dq.front(); // время конца обработки 
            numb = ind; // индекс текущей задачи 
            tmp_task = { process, tm_beg, tm_end, numb };
            insert_heap(tmp_task, heap, heap_size); // добаляем текущую задачу в кучу 
            ind++;
            dq.pop_front(); // удалаяем добавленный элемент 
        }
        else { // свободных мест больше нет - надо освобождать процессор, то есть извлекать мин из кучи 
            mn = extract_min(heap, heap_size);
            // обновляем результат 
            rez[mn[3]] = make_pair(mn[0], mn[1]); // номер процессора + время начала обработки 
            // обновляем время на новое 
            tm = mn[2];
            process = mn[0]; // освободившийся процессор 
            tm_beg = tm;
            tm_end = tm + dq.front();
            numb = ind;
            tmp_task = { process, tm_beg, tm_end, numb };
            insert_heap(tmp_task, heap, heap_size); // добаляем текущую задачу в кучу 
            ind++;
            dq.pop_front(); // удалаяем добавленный элемент 
        }
    }
    while (heap_size != 0) {
        // извлекаем минимумы
        mn = extract_min(heap, heap_size);
        rez[mn[3]] = make_pair(mn[0], mn[1]);
    }
    for (auto& elem : rez) {
        cout << elem.first << ' ' << elem.second << endl;
    }
    return 0;
}
