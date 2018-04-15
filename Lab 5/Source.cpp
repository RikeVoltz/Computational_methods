#include<iostream>
#include<vector>
#include<map>
#include<stdio.h>
using namespace std;

struct point {
    double x;
    double y;
    point(double x, double y): x(x), y(y) {}
    point(): x(0), y(0) {}
};

vector<point> Input() {
	int points_amount;
	cout << "Введите количество исходных точек:\n";
	cin >> points_amount;
	cout << "Введите исходные точки и значения функции в этих точках:\n";
    vector<point>input_values(points_amount);
    for(int i=0;i<points_amount;i++){
        cin >> input_values[i].x >> input_values[i].y;
    }
    return input_values;
}

double omega(vector<point>&values, double param) {
    double W=1;
    for(int i=0; i<(int)values.size(); i++) {
        W*=(param-values[i].x);
    }
    return W;
}

double omegad(vector<point>&values, double param_idx) {
    double Wd=1;
    for(int i=0; i<(int)values.size(); i++) {
        if (i!=param_idx)
            Wd*=(values[param_idx].x-values[i].x);
    }
    return Wd;
}

double Lagrange(vector<point>&values,point &key_point) {
    double L=0;
    for(int i=0; i<(int)values.size(); i++) {
        L+=(omega(values,key_point.x)*values[i].y)/((key_point.x-values[i].x)*omegad(values,i));
    }
    return L;
}


int main() {
    vector<point>initial_values=Input();
    point key_point;
    cout << "Введите точку, в которой нужно найти значение функции: ";
    cin >> key_point.x;
    key_point.y=Lagrange(initial_values,key_point);
    cout << "Значение f(x) в точке " << key_point.x << " равно " << key_point.y;
    return 0;
}
