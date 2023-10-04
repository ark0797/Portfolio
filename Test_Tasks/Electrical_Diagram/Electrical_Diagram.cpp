#include <iostream>
#include <vector>
using namespace std;

// Режим гармонических колебаний в идеальном LC-контуре 

double sq_w; // глобальная переменная 

struct vector2D { // двухкомпонентный вектор 
    double x1;
    double x2;
};

// вектор-функция производной 
vector2D diff_func(vector2D& y, double& t) {
    vector2D dy;
    dy.x1 = y.x2;
    dy.x2 = -sq_w * y.x1;
    return dy;
}

// явня схема Эйлера 
vector<vector2D> explicit_euler_scheme(vector2D(*)(vector2D&, double&), vector<double>& t, vector2D& y_start) {
    vector<vector2D> y_rez(t.size());
    y_rez[0].x1 = y_start.x1;
    y_rez[0].x2 = y_start.x2;
    double step = t[1] - t[0];
    for (int i = 1; i < t.size(); ++i) {
        vector2D df_value = diff_func(y_rez[i - 1], t[i - 1]);
        y_rez[i].x1 = y_rez[i - 1].x1 + df_value.x1 * step;
        y_rez[i].x2 = y_rez[i - 1].x2 + df_value.x2 * step;
    }
    return y_rez;
}

// неявная схема Эйлера 
vector<vector2D> implicit_euler_scheme(vector2D(*)(vector2D&, double&), vector<double>& t, vector2D& y_start) {
    vector<vector2D> y_rez(t.size());
    y_rez[0].x1 = y_start.x1;
    y_rez[0].x2 = y_start.x2;
    double step = t[1] - t[0];
    vector2D y_tmp;
    for (int i = 1; i < t.size(); ++i) {
        vector2D df_value = diff_func(y_rez[i - 1], t[i - 1]);
        // через пробную точку 
        y_tmp.x1 = y_rez[i - 1].x1 + df_value.x1 * step;
        y_tmp.x2 = y_rez[i - 1].x2 + df_value.x2 * step;
        vector2D df_value_1 = diff_func(y_tmp, t[i]);
        double av_deriv_1 = (df_value.x1 + df_value_1.x1) / 2;
        double av_deriv_2 = (df_value.x2 + df_value_1.x2) / 2;
        y_rez[i].x1 = y_rez[i - 1].x1 + av_deriv_1 * step;
        y_rez[i].x2 = y_rez[i - 1].x2 + av_deriv_2 * step;
    }
    return y_rez;
}

// классический метод Рунге-Кутты четвертого порядка точности
vector<vector2D> method_runge_kutta(vector2D(*)(vector2D&, double&), vector<double>& t, vector2D& y_start) {
    vector<vector2D> y_rez(t.size());
    y_rez[0].x1 = y_start.x1;
    y_rez[0].x2 = y_start.x2;
    double step = t[1] - t[0];
    vector2D y_shift, k1, k2, k3, k4;
    double shift = step / 2;
    for (int i = 1; i < t.size(); ++i) {
        // первый коэфф 
        k1 = diff_func(y_rez[i - 1], t[i - 1]);
        double new_t = t[i - 1] + shift;
        y_shift.x1 = y_rez[i - 1].x1 + shift * k1.x1;
        y_shift.x2 = y_rez[i - 1].x2 + shift * k1.x2;
        // второй коэфф 
        k2 = diff_func(y_shift, new_t);
        y_shift.x1 = y_rez[i - 1].x1 + shift * k2.x1;
        y_shift.x2 = y_rez[i - 1].x2 + shift * k2.x2;
        // третий коэфф 
        k3 = diff_func(y_shift, new_t);
        new_t = t[i - 1] + step;
        y_shift.x1 = y_rez[i - 1].x1 + step * k3.x1;
        y_shift.x2 = y_rez[i - 1].x2 + step * k3.x2;
        // четвертый коэфф 
        k4 = diff_func(y_shift, new_t);
        // итерационная формула 
        y_rez[i].x1 = y_rez[i - 1].x1 + step / 6 * (k1.x1 + 2 * k2.x1 + 2 * k3.x1 + k4.x1);
        y_rez[i].x2 = y_rez[i - 1].x2 + step / 6 * (k1.x2 + 2 * k2.x2 + 2 * k3.x2 + k4.x2);
    }
    return y_rez;

}


int main()
{
    vector2D y_start;
    // начальные значения (задача Коши) 
    y_start.x1 = 1;
    y_start.x2 = 0;
    int N = 4000; // кол-во точек области решения (оценочо) 
    double T = 100; // по условию (полный диапазон по времени) 
    double dt = T / (N-1); // шаг по времени 
    vector<double> t(N); // сетка по времени 
    for (int i = 0; i < N; ++i) {
        t[i] = i * dt;
    }
    sq_w = 1;
    // определили указатель на функцию 
    vector2D(*ptr_f)(vector2D&, double&);
    ptr_f = diff_func;
    /*vector<vector2D> rez = explicit_euler_scheme(ptr_f, t, y_start);
    for (int i = 0; i < rez.size(); ++i) {
        cout << t[i] << " " << rez[i].x1 << " " << rez[i].x2 << endl;
    }*/
    /*vector<vector2D> rez = implicit_euler_scheme(ptr_f, t, y_start);
    for (int i = 0; i < rez.size(); ++i) {
        cout << t[i] << " " << rez[i].x1 << " " << rez[i].x2 << endl;
    }*/
    vector<vector2D> rez = method_runge_kutta(ptr_f, t, y_start);
    for (int i = 0; i < rez.size(); ++i) {
        cout << t[i] << " " << rez[i].x1 << " " << rez[i].x2 << endl;
    }
    return 0; 
}

