#include <iostream>
#include <deque>
using namespace std;

// Задача по приему пакетов в буфер, а затем получение сообщения (заполнение массива data_str) на основе принятых данных 
// буфер представляет собой очередь типа FIFO 

// структура данных пакет 
typedef struct {
	unsigned int num;	// порядковый номер пакета
	char data[20];		// данные пакета (20 байт)
} PACKAGE;

int main() {
	deque<PACKAGE> buff;
	// пример заполнения буфера 
	PACKAGE p1;
	char a1[20] = "bbbbbbbbb";
	p1.num = 2;
	strcpy_s(p1.data, a1);
	//cout << p1.data << endl;
	buff.push_front(p1);
	PACKAGE p2;
	char a2[20] = "aaaaaaaaa";
	p2.num = 1;
	strcpy_s(p2.data, a2);
	//cout << p2.data << endl;
	buff.push_front(p2);
	PACKAGE p3;
	char a3[20] = "dd";
	p3.num = 4;
	strcpy_s(p3.data, a3);
	//cout << p3.data << endl;
	buff.push_front(p3);
	PACKAGE p4;
	char a4[20] = "ccccccccc";
	p4.num = 3;
	strcpy_s(p4.data, a4);
	//cout << p4.data << endl;
	buff.push_front(p4);

	char data_str[100];
	int buff_size = buff.size(); // размер буфера 
	PACKAGE end_pack;
	// неполноценным по размеру мб только поледний элемент
	for (int i = 0; i < buff_size; ++i) {
		auto it = buff.end();
		PACKAGE tmp_pack = *(--it); // извлекли последний элемент
		int tmp_num = tmp_pack.num; // номер текущего пакета 
		if (tmp_num != buff_size) { // если текущий пакет не последний
			int cnst = 9 * (tmp_num - 1);
			int k = 0;
			for (int j = cnst; j < cnst + 9; ++j) {
				data_str[j] = tmp_pack.data[k];
				k++;
			}
		}
		else { // сохраняем последний элемент 
			end_pack = tmp_pack;
		}
		buff.pop_back(); // удаляем его из буфера 
	}
	// обработка последнего номера (в буфере остался только 1 элемент)
	int tmp_num = end_pack.num;
	// здесь цикл идет не 9 раз, а ровно столько, сколько символов в data + последний служебный '\0'
	int numb = sizeof(end_pack.data) / sizeof(char); // кол-во элементов в массиве 
	int k = 0;
	int cnst = 9 * (tmp_num - 1);
	for (int i = cnst; i < cnst + numb; ++i) {
		data_str[i] = end_pack.data[k];
		k++;
	}
	data_str[cnst + numb] = '\0';
	cout << "my array data_str: " << data_str;
	return 0;
}