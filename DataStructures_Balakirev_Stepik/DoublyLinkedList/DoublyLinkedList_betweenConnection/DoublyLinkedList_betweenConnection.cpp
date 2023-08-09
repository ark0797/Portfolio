#include <iostream>
#include <list>
using namespace std;

// Модификация двусвязного списка такая, что ссылка next последнего элемента ведет на первый
// а ссылка prev первого на последний (некий замкнутый круг) 

class Node {
public:
    int data;
    Node* prev, * next;

public:
    Node(int data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

class LinkedList {
public:
    Node* head, * tail;
    int count;

public:
    LinkedList() { // конструктор класса 
        this->head = this->tail = NULL;
        this->count = 0;
    }

    ~LinkedList() {
        while (head != NULL)
            pop_front();
    }

    Node* push_front(int data) { // добавление в начало 
        Node* ptr = new Node(data);
        if (head == NULL) { // элементов нет
            ptr->prev = ptr->next = ptr;
            head = tail = ptr;
            count++;
            return ptr;
        }
        if (head == tail) { // только 1 элемент есть в списке
            ptr->next = head;
            head->prev = ptr;
            head->next = ptr;
            ptr->prev = head;
            head = ptr;
            count++;
            return ptr;
        }
        ptr->next = head;
        head->prev = ptr;
        ptr->prev = tail;
        tail->next = ptr;
        head = ptr;
        count++;
        return ptr;
    }


    Node* push_back(int data) { // добавление в конец 
        Node* ptr = new Node(data);
        if (head == NULL) {
            // аналогия с push_front для пустого списка 
            ptr->prev = ptr->next = ptr;
            head = tail = ptr;
            count++;
            return ptr;
        }
        if (head == tail) { // только 1 элемент есть в списке
            ptr->next = head;
            head->prev = ptr;
            head->next = ptr;
            ptr->prev = head;
            tail = ptr;
            count++;
            return ptr;
        }
        tail->next = ptr;
        ptr->prev = tail;
        ptr->next = head;
        head->prev = ptr;
        tail = ptr;
        count++;
        return ptr;
    }

    void pop_front() { // удаление из начала 
        if (head == NULL) return; // нет элементов 
        if (head == tail) { // только 1 элемент 
            delete head;
            head = tail = NULL;
            count--;
            return;
        }
        Node* ptr = head->next;
        delete head;
        head = ptr;
        if (head == tail) { // ссылаемся сами на себя 
            head->next = head->prev = head;
        }
        else {
            head->prev = tail;
            tail->next = head;
        }
        count--;
    }


    void pop_back() { // удаление из конца 
        if (tail == NULL) return;
        if (head == tail) { // только 1 элемент 
            delete head;
            head = tail = NULL;
            count--;
            return;
        }
        Node* ptr = tail->prev;
        delete tail;
        tail = ptr;
        if (head == tail) {
            head->next = head->prev = head;
        }
        else {
            head->prev = tail;
            tail->next = head;
        }
        count--;
    }

    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;
        while (ptr->next != head && n != index) {
            ptr = ptr->next;
            n++;
        }
        return (n == index) ? ptr : NULL;
    }


    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int index, int data) { // вставка на место index
        Node* right = getAt(index);
        if (right == NULL) { // просто вставка в конец 
            return push_back(data);
        }
        Node* left = right->prev;
        if (left == right || right == head) { // только 1 элемент, указыв на себя 
            return push_front(data);
        }
        Node* ptr = new Node(data);
        count++;
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
        return ptr;
    }

    void erase(int index) { // удаление по индексу 
        Node* ptr = getAt(index);
        if (ptr == NULL) return; // не можем удалить по этому индексу 

        if (ptr->prev == ptr || ptr == head) { // удаление из начала 
            pop_front();
            return;
        }
        if (ptr->next == head) { // удаление из конца 
            pop_back();
            return;
        }
        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;
        delete ptr;
        count--;
    }

    void print_lst() {
        if (head == NULL) return;
        Node* ptr = head;
        cout << ptr->data << ' ';
        while (ptr->next != head) {
            cout << (ptr->next)->data << ' ';
            ptr = ptr->next;
        }
        cout << endl;
    }
};

int main(void)
{
    LinkedList digits;
    int a[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
    int size_a = sizeof(a) / sizeof(int);
    //cout << size_a << endl;
    for (int i = 0; i < size_a; ++i) {
        digits.push_back(a[i]);
    }
    digits.print_lst();
    digits.pop_back();
    digits.pop_front();
    digits.erase(1);
    digits.push_back(1);
    digits.push_front(2);
    digits.print_lst();
    cout << digits.getAt(0)->data << endl;
    digits.insert(0, 3);
    digits.print_lst();
    return 0;
}