#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
	short data;
	Node* next;
	unsigned int count;

public:
	Node(short data) {
		this->data = data;
		this->next = NULL;
		this->count = 0;
	}
};

class OneLinkedList {
public:
	Node* head, * tail;

public:
	OneLinkedList() {
		Node* node = new Node(0);
		// если объект толькo 1 - спец элемент 
		this->head = node;
		this->tail = head;
	}

	~OneLinkedList() { // деструктор надо тоже переписать 
		while (head != tail) pop_front();
		delete head;
	}

	void pop_front() { // удаление из начала 
		// надо будет править инфу в head
		//if (head == NULL) return;
		/*if (head == tail) {
			delete tail;
			head = tail = NULL;
			return;
		}*/
		// у нас всегда хотя бы есть 1 элемент (это спец элемент)
		// его удалять не нужно
		if (head == tail) return;
		// имеем хотя бы 1 информ элемент 
		Node* node = head->next; // удаляемый узел 
		// больше элементов нет, кроме 1
		if (node->next == NULL) {
			delete node;
			(head->count)--;
			tail = head; // переопределяем ссылки 
			return;
		}
		// есть хотя бы еще 1 элемент информац 
		head->next = node->next;
		delete node;
		// уменьшить на 1 счетчик head
		(head->count)--;
	}

	void push_back(short data) { // добавление в конец 
		/*Node* node = new Node(data);
		if (head == NULL) head = node;
		if (tail != NULL) tail->next = node;
		tail = node;*/
		Node* node = new Node(data); // выделили память под новый объект 
		if (head == tail) { // только 1 элемент в списке 
			head->next = node;
			tail = node;
			(head->count)++;
			return;
		}
		// элементов в списке хотя бы 2
		tail->next = node;
		tail = node;
		(head->count)++; // увеличили список на 1 элем
	}

	void push_front(short data) { // добавление в начало (спец элемент остается на месте)
		Node* node = new Node(data);
		/*node->next = head;
		head = node;
		if (tail == NULL) tail = node;*/
		if (head == tail) {// имеем только 1 спец элемент
			head->next = node;
			tail = node;
			(head->count)++;
			return;
		}
		Node* tmp = head->next; // первый элемент сейчас 
		// перераспределяем ссылки 
		head->next = node;
		node->next = tmp;
		(head->count)++;
	}

	void pop_back() { // удаление из конца 
		/*if (tail == NULL) return;
		if (head == tail) {
			delete tail;
			head = tail = NULL;
			return;
		}

		Node* node = head;
		for (; node->next != tail; node = node->next);

		node->next = NULL;
		delete tail;
		tail = node;*/
		if (head == tail) return; // ничего удалять не нужно, так как у нас только 1 спец элемент 
		Node* node = head->next; // на 1 элементе 
		if (tail == node) {
			delete node;
			tail = head;
			(head->count)--;
			return;
		}
		// есть хотя бы 2 информ элемента 
		// ищем предпоследний элемент 
		for (; node->next != tail; node = node->next);
		node->next = NULL;
		delete tail;
		tail = node;
		(head->count)--;
	}

	Node* getAt(int k) { // получение элемента по индексу 
		if (k < 0) return NULL;
		// здесь надо переделать, так как 0 элемент тип 1 в списке
		if (head == tail) return NULL;
		Node* node = head->next; // указываю на след после спец элемента элемент 
		int n = 0;
		while (node && n != k && node->next) {
			node = node->next;
			n++;
		}
		return (n == k) ? node : NULL;
	}

	void insert(int k, short data) { // вставка элемента после позиции k
		Node* left = getAt(k);
		if (left == NULL) return; // проверка на то, есть ли вообще такой элем с индексом k
		if (left->next == NULL) { // вставка в конец будет 
			push_back(data);
		}
		Node* right = left->next;
		// надо вставить между left и right 
		Node* node = new Node(data); // выделяем память под новый элем 
		left->next = node;
		node->next = right;
		(head->count)++;
	}

	void erase(int k) { // удаление по индексу k 
		if (k < 0) return;
		// мы не удаляем спец элемент 
		// случай k = 0 надо отдельно обработать 
		if (k == 0) {
			Node* node = getAt(k);
			if (node == NULL) return;
			if (node->next == NULL) { // это 1 и последний элемент 
				head->next = NULL;
				tail = head;
				delete node;
				(head->count)--;
				return;
			}
			// это не последний элемент 
			head->next = node->next;
			delete node;
			(head->count)--;
			return;
		}
		// k >= 1
		Node* left = getAt(k - 1); // нашли левый элемент 
		if (left == NULL) return; // элемента с таким индексом нет 
		Node* node = left->next; // удаляемый элемент 
		if (node == NULL) return; // ничего не удаляем
		Node* right = node->next;
		if (right == NULL) { // то есть node послед элемент 
			// просто удаляем из конца 
			pop_back();
			return;
		}
		left->next = right;
		delete node;
		(head->count)--;
	}
};

int main(void)
{
    setlocale(LC_ALL, "RUS");
	OneLinkedList lib;
	cout << lib.head->count << endl;
	lib.push_back(8);
	lib.push_back(8);
	lib.push_back(8);
	lib.push_back(8);
	cout << lib.head->count << endl;
	lib.erase(2);
	cout << lib.head->count << endl;
    return 0;
}