#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Собственная реализация своей структуры данных - Префиксное Дерево 
// Это дерево в каждом узле содержит символ, указание на то, заканчивается ли в нем ключ и если да, то значение по ключу 
// Методы, доступные пользователю: 
// insert - добавление пары ключ- значение (string-int) в дерево 
// find_key - поиск ключа в дереве, если ключ найден - выдается значение, если нет - (-1)
// delete_key - удаление ключа из дерева 
// shake_off - "отряхивание" дерева - удаление всех листовых вершин, в ктр уже не заканчиваются ключи
// prefix_keys - получение всех ключей по заданному префиксу 
// get_all_keys - получение абсолютно всех ключей, что хранятся в дереве (работает на основе обхода в глубину)

// ++ - метод протестирован 

// класс для описания отдельного узла 
class Node {
public:
    char value; // значение текущего символа  
    bool is_it_key; // является ли слово, в нем окнчивающееся, ключом 
    int data; // если это окончание ключа, то храним значение по ключу 
    vector<Node*> children; // ДМ ссылок на потомков 

public:
    Node(char value) { // конструктор класса 
        // по умолчанию делаю этот узел без данных и  он не является ключом 
        this->value = value;
        this->is_it_key = false;
        this->data = NULL;
    }
};

// класс для описания префиксного дерева 
class PrefixTree {

public: // атрибуты класса 
    Node* root; // указатель на корневую вершину 

    PrefixTree() { // конструктор класса 
        Node* rt = new Node(' ');
        this->root = rt;
    }

    ~PrefixTree() { // деструктор класса 
        // у каждого узла надо сделать указание на то, что это ключ false 
        // и делать shake_off, пока не останется только корень, а затем и его удалить 
        dfs_anti_keys(root);
        while (root->children.size() != 0) {
            shake_off(root, NULL);
        }
        delete root;
    }

private:
    // ищем символ-ребенок у данного предка 
    // внутренний метод 
    Node* find_char(char desc, Node* anc) {
        // desc - символ, что мы ищем
        // anc - у какой вершины ищем потомка 
        for (auto& elem : anc->children) {
            if (elem->value == desc) {
                return elem; // возвращаем ссылку на найденный элемент 
            }
        }
        return NULL; // нет такого потомка у этой вершины 
    }


    // обход всех ключей в дереве (это будем считать внутренним методом) 
    // ++ 
    void dfs_keys(Node* tmp_vertex, string pref, set<string>& rez) {
        if (tmp_vertex != root) { // надо обрезать пробел в самом начале (тк в корневой вершине пробел)
            pref += tmp_vertex->value;
        }
        if (tmp_vertex->children.size() == 0) { // у этой вершины детей нет (она листовая) 
            if (tmp_vertex->is_it_key) {
                //cout << pref << ' ';
                rez.insert(pref);
            }
            return;
        }
        for (auto& desc : tmp_vertex->children) {
            if (desc->is_it_key) {
                //cout << pref + desc->value << ' ';
                rez.insert(pref + desc->value);
            }
            dfs_keys(desc, pref, rez);
        }
    }

    // обход в глубину для того, чтобы все узлы сделать с пометкой не ключ - false 
    // ++
    void dfs_anti_keys(Node* tmp_vertex) {
        if (tmp_vertex->children.size() == 0) { // у этой вершины детей нет (она листовая) 
            tmp_vertex->is_it_key = false;
            return;
        }
        for (auto& desc : tmp_vertex->children) {
            if (desc->is_it_key) {
                desc->is_it_key = false;
            }
            dfs_anti_keys(desc);
        }
    }

public: // методы класса

    // добавление пары {key, value} в префиксное дерево 
    // ++ 
    void insert(string key, int value) {
        // ключ с пустым значением создать не можем 
        if (key.size() == 0) {
            cout << "empty strings are not added";
            return;
        }
        // теперь в ключе есть хотя бы 1 символ 
        Node* anc = root;
        bool f = true;
        int br_point; // переменная для символа, на котором произойдет обрыв 
        for (int i = 0; i < key.size(); ++i) { // перебираем каждый символ в слове 
            Node* tmp_node = find_char(key[i], anc);
            if (tmp_node == NULL) { // не нашли такого потомка у anc
                // начиная с anc надо добавлять новое слово 
                br_point = i;
                f = false;
                break;
            }
            anc = tmp_node;
        }
        if (f) { // нашли все символы из ключа в дереве (такой префикс уже есть)
            // заменяем значение по ключу 
            anc->data = value; // заменили данные по этому ключу 
            anc->is_it_key = true;
        }
        else { // остановились на anc, где идет обрыв (то есть с него начинаем формировать узлы)
            // начинаем добавлять в дерево узлы с индекса br_point
            for (int i = br_point; i < key.size(); ++i) {
                Node* node = new Node(key[i]);
                anc->children.push_back(node);
                anc = node;
            }
            anc->data = value;
            anc->is_it_key = true;
        }
    }

    // поиск ключа в дереве
    // возвращаем значение по данному ключу, если он есть 
    // ++ 
    int find_key(string key) {
        Node* tmp_vertex = root;
        for (auto ch : key) {
            Node* desc = find_char(ch, tmp_vertex);
            if (desc == NULL) {
                return -1; // если хотя бы одного символа нет, то такого слова нет 
            }
            tmp_vertex = desc;
        }
        if (tmp_vertex->is_it_key) return tmp_vertex->data;
        return -1;
    }

    // удаление ключа из дерева (без удаления листовых узлов) 
    // ++ 
    void delete_key(string key) {
        Node* tmp_vertex = root;
        for (auto ch : key) {
            Node* desc = find_char(ch, tmp_vertex);
            if (desc == NULL) {
                cout << "DeleteKeyError: there is no such key in the tree" << endl;
                return;
            }
            tmp_vertex = desc;
        }
        if (tmp_vertex->is_it_key) { // такой ключ есть 
            tmp_vertex->is_it_key = false;
            cout << "Successful Deletion" << endl;
            return;
        }
        cout << "DeleteKeyError: there is no such key in the tree" << endl;
        return;
    }

    // "отряхивание" дерева - удаляем все листовые узлы, что уже не ключи (функция рекурсивная) 
    // чтобы освободить память и не перегружать дерево 
    // ++
    void shake_off(Node* tmp_vertex, Node* anc) {
        if (tmp_vertex->children.size() == 0) { // у этой вершины детей нет (она листовая) 
            if (!tmp_vertex->is_it_key) { // в этой вершине не заканчивается ключ 
                auto it = find(anc->children.begin(), anc->children.end(), tmp_vertex);
                anc->children.erase(it); // удаляем лишнего ребенка 
                delete tmp_vertex;
            }
            return;
        }
        for (auto& desc : tmp_vertex->children) {
            shake_off(desc, tmp_vertex);
        }
    }

    // получение всех доступных слов по заданному префиксу
    // ++
    void prefix_keys(string pref) {
        // обход в глубину надо вызывать от последнего символа префикса
        // для этого надо получить на него ссылку 
        Node* tmp_vertex = root; // корень
        for (auto ch : pref) {
            Node* desc = find_char(ch, tmp_vertex); // ссылка на потомка 
            if (desc == NULL) { // такого потомка нет - такого префикса нет 
                cout << "PrefixKeyError: there is not such prefix in the tree" << endl;
                return;
            }
            tmp_vertex = desc;
        }
        // сейчас в tmp_vertex как раз ссылка на необходимую вершину 
        set<string> rez;
        if (tmp_vertex->is_it_key) {
            rez.insert(pref);
        }
        string pref_tmp = pref.substr(0, pref.size() - 1);
        dfs_keys(tmp_vertex, pref_tmp, rez);
        for (auto& elem : rez) {
            cout << elem << endl;
        }
    }

    // получение всех ключей в дереве без лишних костылей - сразу на экран 
    // ++ 
    void get_all_keys() {
        set<string> rez;
        string pref = "";
        dfs_keys(root, pref, rez);
        for (auto& elem : rez) {
            cout << elem << endl;
        }
        if (rez.size() == 0) { // в дереве нет ключей 
            cout << "The tree does not have keys" << endl;
            return;
        }
    }
};

int main()
{
    PrefixTree pr;
    pr.insert("o", 2345);
    pr.insert("dog", 2);
    pr.insert("dos", 1);
    pr.insert("mul", 3);
    pr.insert("d", 5);
    pr.insert("dom", 8);
    pr.insert("do", 9);
    pr.prefix_keys("do");
    cout << endl;
    pr.get_all_keys();
    /*string pref = "";
    set<string> rez;
    pr.dfs_keys(pr.root, pref, rez);
    for (auto& elem : rez) {
        cout << elem << endl;
    }*/
    /*string pref = "";
    set<string> rez;
    pr.dfs_keys(pr.root, pref, rez);
    for (auto& elem : rez) {
        cout << elem << endl;
    }
    cout << pr.find_key("do") << endl;
    pr.delete_key("dom");
    pr.delete_key("do");
    pr.delete_key("mul");
    pr.shake_off(pr.root, NULL);
    rez.clear();
    pr.dfs_keys(pr.root, pref, rez);
    for (auto& elem : rez) {
        cout << elem << endl;
    }*/

    /*vector<int> v = {1,2,3,4,5,6};
    auto it = find(v.begin(), v.end(), 5);
    cout << v.size() << endl;
    //remove(v.begin(), v.end(), 4);
    v.erase(it);
    cout << v.size();*/
    /*char c = 'd';
    string s = "mama";
    cout << s + c;*/
    return 0;
}
