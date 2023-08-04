#include <iostream>
#include<utility>
#include <typeinfo>
#include <string.h>
using namespace std;

// реализуем модифицированный односвязный список такой, что ссылка послед элем ведет на первый 

class Node {
public:
	char data[50];
	//char* data;
	Node* next;

public:
	Node(const char* data) {
		//this->data = new char[50];
		for (int i = 0; i < 50; ++i) {
			if (data[i] != '\0') {
				this->data[i] = data[i];
			}
			else {
				this->data[i] = data[i];
				break;
			}
		}
		this->next = NULL;
	}
	/*~Node() {
		delete [] data;
	}*/
};

class OneLinkedList {
public:
	Node* head, * tail;

public:
	OneLinkedList() { // конструктор класса 
		// если элементов нет, то ссылаемся на NULL
		this->head = this->tail = NULL;
	}

	~OneLinkedList() { // деструктор менять не нужно 
		while (head != NULL) pop_front();
	}

	void pop_front() { // удаление из начала 
		if (head == NULL) return; // в списке нет элементов 
		if (head == tail) { // только 1 элемент 
			delete tail;
			head = tail = NULL;
			return;
		}
		// хотя бы 2 элемента 
		Node* node = head;
		head = node->next;
		delete node;
		// зацикливаем ссылку на 1 объект 
		tail->next = head;
	}

	void push_back(char* data) { // добавление в конец 
		Node* node = new Node(data);
		if (head == NULL) { // изначально список пустой 
			head = node;
			tail = node;
			tail->next = head;
			return;
		}
		// список не пустой 
		tail->next = node;
		tail = node;
		tail->next = head;
	}

	void push_front(char* data) { // добавление в начало 
		Node* node = new Node(data);
		//node->next = head;
		//head = node;
		if (head == NULL) { // если список был пустой изначально 
			head = node;
			tail = node;
			tail->next = head;
			return;
		}
		// если не пустой
		node->next = head;
		head = node;
		tail->next = head;
	}

	void pop_back() { // удаление из конца 
		if (tail == NULL) return; // пустой список 
		if (head == tail) { // только 1 элемент 
			delete tail;
			head = tail = NULL;
			return;
		}
		Node* node = head;
		// ищем предпоследний элемент 
		for (; node->next != tail; node = node->next);
		node->next = head;
		delete tail;
		tail = node;
	}

	Node* getAt(int k) { // получение элемента по индексу
		// здесь правится только условие в цикле  
		if (k < 0) return NULL;
		Node* node = head;
		int n = 0;
		while (node && n != k && (node->next != head)) {
			node = node->next;
			n++;
		}
		return (n == k) ? node : NULL;
	}

	void insert(int k, char* data) { // вставка элемента после позиции k 
		Node* left = getAt(k);
		if (left == NULL) return; // не мж вставить после такой позиции 

		Node* right = left->next;
		Node* node = new Node(data);

		left->next = node;
		if (right == head) { // left был послед элем 
			tail = node; 
			tail->next = head;
			return;
		}
		node->next = right;
	}

	void erase(int k) { // удаление элемента с индексом k 
		if (k < 0) return;
		if (k == 0) { // удаление из начала 
			pop_front();
			return;
		}
		// удаляем из произв места 
		Node* left = getAt(k - 1);
		if (left == NULL) return; // нет элемента с таким индексом 

		Node* node = left->next;
		if (node == head) return; // Left последний элемент - удалить не мж 

		Node* right = node->next;
		if (right == head) { // просто удаляем послед элемент node
			delete node;
			tail = left;
			tail->next = head;
			return;
		}
		// здесь right полноценный элемент (даже мб и последним)
		left->next = right;
		delete node;
	}
};

int main(void)
{
	setlocale(LC_ALL, "RUS");
	OneLinkedList strings;
	char data1[] = { "Я к вам пишу – чего же боле?" };
	strings.push_back(data1);
	//Node* node = strings.getAt(0);
	//cout << (*node).data << endl;
	//cout << (*(node->next)).data;
	char data2[] = {"Что я могу еще сказать?"};
	strings.push_back(data2);
	char data3[] = { "Теперь, я знаю, в вашей воле" };
	strings.push_back(data3);
	char data4[] = { "Меня презреньем наказать." };
	strings.push_back(data4);
	char data5[] = { "Но вы, к моей несчастной доле" };
	strings.push_back(data5);
	char data6[] = { "Хоть каплю жалости храня," };
	strings.push_back(data6);
	char data7[] = { "Вы не оставите меня." };
	strings.push_front(data7);
	strings.pop_back();
	strings.pop_front();
	char data8[] = { "Where is my mind?" };
	strings.insert(3, data8);
	cout << (*strings.getAt(4)).data << endl;
	cout << (*strings.getAt(1)).data << endl;
	strings.erase(1);
	cout << (*strings.getAt(1)).data << endl;
	Node* node = strings.getAt(10);
	if (node != NULL) {
		cout << (*(node->next)).data;
	}
	return 0;
}