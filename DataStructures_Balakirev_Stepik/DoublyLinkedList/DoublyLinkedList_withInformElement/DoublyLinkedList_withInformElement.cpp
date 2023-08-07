#include <iostream>
using namespace std;

// Модификация структуры двусвязного списка так, что при создании всегда есть спец элемент 
// это первый элемент списка (он вне индекса), его поле data хранит кол-во информац элементов списка  

class Node {
public:
    int data;
    Node* prev, * next;
    unsigned int count; // просят добавить именно в этот класс 

public:
    Node(int data) {
        this->data = data;
        this->prev = this->next = NULL;
        this->count = 0;
    }
};

class LinkedList {
public:
    Node* head, * tail;

public:
    LinkedList() {
        // спец элемент создается в момент инициализации
        Node* spec_node = new Node(0); // data спец элемента хранит в себе count
        this->head = spec_node;
        tail = head;
    }

    ~LinkedList() {
        while (head != tail) pop_front();
        delete head;
    }

    Node* push_front(int data) { // добавление в начало 
        Node* ptr = new Node(data);
        if (head->count == 0) { // есть только спец элемент 
            ptr->prev = head;
            head->next = ptr;
            tail = ptr;
            (head->count)++;
            head->data = head->count;
            return ptr;
        }
        // >= 1 информ элемента 
        Node* node = head->next;
        head->next = ptr;
        ptr->prev = head;
        ptr->next = node;
        node->prev = ptr;
        (head->count)++;
        head->data = head->count;
    }

    Node* push_back(int data) { // добавление в конец 
        Node* ptr = new Node(data);
        if (head->count == 0) { // нет ни одного информ элемента 
            // здесь идет полная аналогия с push_front
            ptr->prev = head;
            head->next = ptr;
            tail = ptr;
            (head->count)++;
            head->data = head->count;
            return ptr;
        }
        // >= 1 информ элемента 
        tail->next = ptr;
        ptr->prev = tail;
        tail = ptr;
        (head->count)++;
        head->data = head->count;
    }

    void pop_front() { // удаление из начала 
        if (head->count == 0) return; // не можем удалить 
        if (head->count == 1) { // 1 информ элемет 
            Node* ptr = head->next;
            delete ptr;
            head->next = NULL;
            tail = head;
            (head->count)--;
            head->data = head->count;
            return;
        }
        // > 1 Информ элемента 
        Node* ptr = head->next;
        Node* tmp = ptr->next;
        delete ptr;
        head->next = tmp;
        tmp->prev = head;
        (head->count)--;
        head->data = head->count;
    }

    void pop_back() { // удаление из конца 
        if (head->count == 0) return; // удалять нечего
        if (head->count == 1) {
            // повторение pop_front для 1 элемента 
            Node* ptr = head->next;
            delete ptr;
            head->next = NULL;
            tail = head;
            (head->count)--;
            head->data = head->count;
            return;
        }
        Node* tmp = tail->prev;
        delete tail;
        tmp->next = NULL;
        tail = tmp;
        (head->count)--;
        head->data = head->count;
    }

    Node* getAt(int index) { // получение по индексу 
        // указываем сразу на первый информ элемент 
        Node* ptr = head->next;
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

    Node* insert(int index, int data) { // вставка по индексу index 
        Node* right = getAt(index);
        if (right == NULL) { // если информ элементов нету
            return push_back(data);
        }

        Node* left = right->prev;
        if (left == head) { // если только 1 информ элемент 
            return push_front(data);
        }
        Node* ptr = new Node(data); // выделили память под новый элемент 
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
        (head->count)++;
        head->data = head->count;
        return ptr;
    }

    void erase(int index) { // удаление по индексу index
        Node* ptr = getAt(index);
        if (ptr == NULL) { // нет удаляемого элемента 
            return;
        }
        if (ptr->prev == head) {
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
        delete ptr;
        (head->count)--;
        head->data = head->count;
    }

    void print_dlst() { // движение вправо 
        for (Node* ptr = head->next; ptr != NULL; ptr = ptr->next) {
            cout << ptr->data << ' ';
        }
        cout << endl;
    }
};

int main(void)
{
    LinkedList lst;
    cout << lst.head->count << endl;
    lst.pop_front();
    lst.push_front(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    cout << lst.head->data << endl;
    lst.push_back(5);
    lst.push_back(6);
    lst.push_front(10);
    lst.push_front(11);
    lst.pop_front();
    lst.erase(5);
    lst.insert(3, 1456);
    lst.pop_back();
    lst.print_dlst();
    cout << lst.head->data << endl;
    cout << lst.head->count << endl;
    return 0;
}