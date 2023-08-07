#include <iostream>
using namespace std;

// Описание задачи - внутри двусвязного списка работать со структурой GOODS
// отсортировать элементы в порядке возрастания цены в двусвязном списке 
// исхожный список goods оставить неизменным 

typedef struct {
    unsigned long id;	// идентификатор
    char name[100];		// название
    double price;		// цена
} GOODS;

class Node {
public:
    GOODS data;
    Node* prev, * next;

public:
    Node(GOODS data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

class LinkedList {
public:
    Node* head, * tail;
    int counter;

public:
    LinkedList() {
        this->head = this->tail = NULL;
        this->counter = 0;
    }

    LinkedList(const LinkedList& lst) { // конструктор копий 
        this->head = lst.head;
        this->tail = lst.tail;
        this->counter = lst.counter;
    }

    ~LinkedList() {
        while (head != NULL)
            pop_front();
    }

    Node* push_front(GOODS data) {
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;
        counter++;
        return ptr;
    }


    Node* push_back(GOODS data) {
        Node* ptr = new Node(data);

        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;
        counter++;
        return ptr;
    }

    void pop_front() { // удаление из начала 
        if (head == NULL) { // удалять нечего 
            return;
        }
        Node* ptr = head->next;
        if (ptr == NULL) { // элемент в списке только 1
            delete head;
            head = tail = NULL;
            return;
        }
        ptr->prev = NULL;
        delete head;
        head = ptr;
    }


    void pop_back() {
        if (tail == NULL) return;
        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;
        delete tail;
        counter--;
        tail = ptr;
    }

    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;
        while (n != index) {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }


    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int index, GOODS data) {
        Node* right = getAt(index);
        if (right == NULL)
            return push_back(data);

        Node* left = right->prev;
        if (left == NULL)
            return push_front(data);
        Node* ptr = new Node(data);
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
        counter++;
        return ptr;
    }

    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == NULL)
            return;
        if (ptr->prev == NULL) {
            pop_front();
            return;
        }
        if (ptr->next == NULL) {
            pop_back();
            return;
        }
        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;
        counter--;
        delete ptr;
    }

};
void print_lst(LinkedList& lst) {
    for (int i = 0; lst[i] != NULL; ++i) {
        cout << (lst[i]->data).id << ' ' << (lst[i]->data).name << ' ' << (lst[i]->data).price << endl;
    }
}

// сортировка пузырьком для двусвязного списка по цене  
void bubble_sorting_lst(LinkedList& sort_goods) {
    int n = sort_goods.counter;
    for (int i = 0; i < (n - 1); ++i) { // идем до предпоследнего элемента 
        double mn = (sort_goods[i]->data).price;
        int ind_mn = i;
        for (int j = i + 1; j < n; ++j) {
            if ((sort_goods[j]->data).price < mn) {
                mn = (sort_goods[j]->data).price;
                ind_mn = j;
            }
        }
        if (i != ind_mn) { // минимум поменялся
            Node* node_mn = sort_goods.getAt(ind_mn);
            Node* tmp = sort_goods.getAt(i);
            /*sort_goods.erase(i);
            sort_goods.insert(i, node_mn->data);
            sort_goods.erase(ind_mn);
            sort_goods.insert(ind_mn, tmp->data);*/
            Node* tmp_left = tmp->prev;
            Node* tmp_right = tmp->next;
            Node* left = node_mn->prev;
            Node* right = node_mn->next;
            // напишем случай двух рядом стоящих элементов
            if (left == tmp) {
                tmp->next = right;
                tmp->prev = node_mn;
                node_mn->next = tmp;
                node_mn->prev = tmp_left;
                if (tmp_left != NULL) {
                    tmp_left->next = node_mn;
                }
                if (right != NULL) {
                    right->prev = tmp;
                }
            }
            // между ними только 1 элемент 
            else if (tmp_right == left) {
                tmp->next = right;
                if (right != NULL) {
                    right->prev = tmp;
                }
                tmp->prev = left;
                left->next = tmp;
                left->prev = node_mn;
                node_mn->next = left;
                node_mn->prev = tmp_left;
                if (tmp_left != NULL) {
                    tmp_left->next = node_mn;
                }
            }
            else { // между ними хотя бы 2 элемента 
                tmp->next = right;
                tmp->prev = left;
                if (right != NULL) {
                    right->prev = tmp;
                }
                left->next = tmp;
                node_mn->next = tmp_right;
                node_mn->prev = tmp_left;
                tmp_right->prev = node_mn;
                if (tmp_left != NULL) {
                    tmp_left->next = node_mn;
                }
            }

        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "RUS");
    GOODS g1 = {1, "стол", 5443.77 };
    GOODS g2 = { 5, "зеркало", 12400.0 };
    GOODS g3 = { 2, "кровать", 65000.0 };
    GOODS g4 = { 8, "кресло", 34500.0 };
    GOODS g5 = { 11, "стенка", 120400.0 };
    GOODS g6 = { 3, "холодильник", 65500.0 };
    LinkedList goods;
    goods.push_back(g1);
    goods.push_back(g2);
    goods.push_back(g3);
    goods.push_back(g4);
    goods.push_back(g5);
    goods.push_back(g6); 
    cout << "before sorting" << endl;
    print_lst(goods);
    LinkedList sort_goods;
    // заполняем список sort_goods
    for (int i = 0; i < goods.counter; ++i) {
        sort_goods.push_back(goods[i]->data);
    }
    bubble_sorting_lst(sort_goods);
    cout << endl;
    cout << "after sorting" << endl;
    print_lst(sort_goods);
    return 0;
}