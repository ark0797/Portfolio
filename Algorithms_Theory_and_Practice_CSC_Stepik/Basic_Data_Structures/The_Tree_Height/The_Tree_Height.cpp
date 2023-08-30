#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Задача: Подсчитать высоту корневого дерева 
// вершины пронумерованы от 0 до n-1, дерево подается списком родителей 
// если в корневом дереве только 1 корень, то считаем (против Кормена), что высота 1


// рекурсивная функция подсчета высоты дерева 
// эта реализация довольно долгая, поэтому ниже более оптимизированный вариант  
int Tree_Height(int vertex, vector<vector<int>> graph) {
    int height = 1;
    vector<int> children = graph[vertex];
    for (auto& child : children) {
        height = max(height, 1 + Tree_Height(child, graph));
    }
    return height;
}

// рекурсивная функция подсчета высоты дерева через дополнительный буфер heights
// если мы уже посещали эту вершину, то повторно заходить не будем 
int count_way_root_adv(int tmp_vertex, int root, vector<int>& par, vector<int>& heights) {
    //++
    if (par[tmp_vertex] == -1) { // вершина корневая 
        heights[tmp_vertex] = 1;
        return 1;
    }
    //++
    if (par[tmp_vertex] == root) { // наткнулись на корень 
        //heights[tmp_vertex] = height + 1;
        heights[tmp_vertex] = 2;
        return 2;
    }
    int tmp_par = par[tmp_vertex]; // текущий родитель (это не корень и не -1)
    if (heights[tmp_par] != 0) { // если мы уже были в этой вершине
        //heights[tmp_vertex] = heights[tmp_par] + 1; // вытаскиваем уже имеющиеся данные  
        heights[tmp_vertex] = 1 + heights[tmp_par];
        return 1 + heights[tmp_par];
    }
    heights[tmp_vertex]++;
    heights[tmp_vertex] += count_way_root_adv(tmp_par, root, par, heights);
    return heights[tmp_vertex];
}

int main()
{
    // решение 2 (оптимизированное) 
    int n;
    cin >> n;
    vector<int> par(n); // список родителей 
    int root = 0;
    for (int i = 0; i < n; ++i) {
        cin >> par[i];
        if (par[i] == -1) root = i; // находим корень сразу (он единственен)
    }
    vector<int> heights(n, 0);
    for (int vert = 0; vert < n; ++vert) {
        count_way_root_adv(vert, root, par, heights);
    }
    /*for (auto& elem : heights) {
        cout << elem << ' ';
    }
    cout << endl;*/
    cout << *max_element(heights.begin(), heights.end());

    // решение 1 (неоптимизированное)
    /*int n;
    cin >> n;
    vector<int> par(n); // список родителей 
    int root = 0;
    for (int i = 0; i < n; ++i) {
        cin >> par[i];
        if (par[i] == -1) root = i; // находим корень сразу (он единственен)
    }
    // теперь из вида дерева "список родителей" сформируем "список смежности"
    vector<vector<int>> graph(n);
    for (int vert = 0; vert < n; ++vert) {
        for (int i = 0; i < n; ++i) {
            if (par[i] == vert) { // то у этого элемента родитель vert
                graph[vert].push_back(i);
            }
        }
    }
    vector<int> rez;
    cout << Tree_Height(root, graph);*/
    return 0;
}

