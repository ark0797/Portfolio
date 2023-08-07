#include <iostream>
using namespace std;

// реализуем двусвязный список руками через ООП 

class Node { // один элемент двусвязного списка 
public:
    double data;
    Node* prev;
    Node* next;
public:
    Node(double data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

class DoublyLinkedList { // или просто LinkedList
public:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { // конструктор класса 
        head = tail = NULL;
    }

    ~DoublyLinkedList() { // самостоятельно освобождаем память 
        while (head != NULL) {
            pop_front();
        }
    }

    Node* push_front(double data) { // добавление в начало 
        Node* ptr = new Node(data);
        // если даже head NULL, то ок 
        ptr->next = head;
        if (head != NULL) {
            head->prev = ptr;
        }
        if (tail == NULL) { // список изначально был пустой 
            tail = ptr;
        }
        head = ptr;
        return ptr;
    }

    Node* push_back(double data) { // добавление в конец 
        Node* ptr = new Node(data);
        // если даже head NULL, то ок 
        ptr->prev = tail;
        if (tail != NULL) {
            tail->next = ptr;
        }
        if (head == NULL) { // список изначально был пустой 
            head = ptr;
        }
        tail = ptr;
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

    void pop_back() { // удаление из конца
        if (head == NULL) { // удалять нечего 
            return;
        }
        Node* ptr = tail->prev;
        if (ptr == NULL) { // элемент в списке только 1
            delete tail;
            head = tail = NULL;
            return;
        }
        ptr->next = NULL;
        delete tail;
        tail = ptr;
    }

    Node* getAt(int k) { // получение k-ого элемента 
        if (k < 0) return NULL;
        Node* ptr = head;
        int n = 0;
        while (ptr && n != k) {
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }

    // перегружаем оператор квадратных скобок 
    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int k, double data) { // вставка элемента после k-ого
        Node* left = getAt(k);
        if (left == NULL) { // не мж вставить после такой позиции
            return NULL;
        }
        Node* right = left->next;
        if (right == NULL) { // делаем вставку в конец 
            return push_back(data);
        }
        // здесь реализуем нормальную вставку между элементами 
        Node* ptr = new Node(data);
        left->next = ptr;
        ptr->prev = left;
        ptr->next = right;
        right->prev = ptr;
        return ptr;
    }

    void erase(int k) { // удаление k-ого элемента 
        Node* ptr = getAt(k);
        if (ptr == NULL) return; // нет удаляемого элемента 
        if (ptr->prev == NULL) { // это удаление 1-ого элемента 
            pop_front();
            return;
        }
        if (ptr->next == NULL) { // это удаление конечного элемента 
            pop_back();
            return;
        }
        // здесь обычная ситуация удаления
        Node* left = ptr->prev;
        Node* right = ptr->next;
        delete ptr;
        left->next = right;
        right->prev = left;
    }

    void print_dlst() { // движение вправо 
        for (Node* ptr = head; ptr != NULL; ptr = ptr->next) {
            cout << ptr->data << ' ';
        }
        cout << endl;
    }

    void revprint_dlst() { // движение влево 
        for (Node* ptr = tail; ptr != NULL; ptr = ptr->prev) {
            cout << ptr->data << ' ';
        }
        cout << endl;
    }
};
int main()
{
    DoublyLinkedList dlst;
    dlst.push_back(1.56);
    dlst.push_back(3.56);
    dlst.push_back(4.56);
    dlst.push_back(7.56);
    dlst.push_back(2.56);
    dlst.push_back(8.56);
    dlst.push_back(19.56);
    dlst.push_back(47.56);
    dlst.print_dlst();
    cout << dlst[3]->data << ' ' << dlst[0]->data << endl;
    //cout << dlst[10]->data << endl;
    dlst.erase(4);
    cout << "printing" << endl;
    dlst.print_dlst();
    dlst.revprint_dlst();
    cout << endl;
    Node* node = dlst.getAt(0);
    if (node != NULL) {
        cout << node->data << endl;
    }
    else {
        cout << NULL << endl;
    }
    dlst.insert(0, 78.90);
    dlst.pop_front();
    dlst.pop_back();
    dlst.print_dlst();

    cout << "here" << endl;
    DoublyLinkedList dlst1;
    dlst1.push_front(4.56);
    dlst1.pop_back();
    dlst1.pop_back();
    dlst1.print_dlst();
    dlst1.erase(6);
    dlst1.insert(1, 78.9);
    dlst1.print_dlst();
    dlst1.push_front(1.56);
    dlst1.insert(0, 78.9);
    dlst1.print_dlst();
    dlst1.erase(50);
    //cout << node;*/
}