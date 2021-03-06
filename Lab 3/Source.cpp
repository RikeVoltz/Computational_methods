/**
������������ ������ �3 �� ���������� "�������������� ������"
@name Main
@memo ������� ���������� ���������. ����� ������� (�������) � ����� ���������.
@author (c) 2017 �. �. �������
*/
#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#include<stdio.h>
using namespace std;
const double K_EPS_DICHOTOMY = 1e-1;
const double K_EPS_MUELLER = 5e-4;
enum ERRORS { DICHOTOMY_ERROR = 1, MUELLER_ERROR = 2, VERIFICATION_ERROR=3 };

struct segment {
    double start;
    double end;
    segment();
};
struct root_with_borders {
    segment borders;
    double root;
    root_with_borders();
};

double f(double x);
void Dichotomy(root_with_borders &root);
void MuellersMethod(root_with_borders &root);
void Verification(vector<root_with_borders>&roots);
void PrintRoots(vector<root_with_borders>&roots);

int main() {
    setlocale(LC_ALL, "rus");
    cout << "������� ���������� ������: ";
    size_t roots_amount;
    cin >> roots_amount;
    vector<root_with_borders>roots(roots_amount);
    cout << "������� ��������� ������� �������� ��� ������� �� ������: " << endl;
    for (int i = 0; i < roots_amount; i++) {
        cin >> roots[i].borders.start >> roots[i].borders.end;
    }
    for (int i = 0; i < roots_amount; i++)
        Dichotomy(roots[i]);
    for (int i = 0; i < roots_amount; i++)
        MuellersMethod(roots[i]);
    Verification(roots);
    PrintRoots(roots);
    return 0;
}

segment::segment() {
    start = 0;
    end = 0;
}


root_with_borders::root_with_borders() {
    borders.start = 0;
    borders.end = 0;
    root = 0;
}


double f(double x) {
    return pow(x, 3) + 3 * pow(x, 2) - 1;
}

void Dichotomy(root_with_borders &root) {
    while (root.borders.end - root.borders.start >= K_EPS_DICHOTOMY / 2) {
        if (f(root.borders.end)*f(root.borders.start) > 0) {
            cerr << "������ � ������ ���������" << endl;
            exit(DICHOTOMY_ERROR);
        }
        double middle = (root.borders.end + root.borders.start) / 2;
        if (f(middle)*f(root.borders.end) <= 0)
            root.borders.start = middle;
        else
            root.borders.end = middle;
    }
}

void MuellersMethod(root_with_borders &root) {
    double x = rand();
    while (fabs(x - root.root) >= K_EPS_MUELLER) {
        root.root = x;
        double a = root.borders.start;
        double b = root.borders.end;
        double c = (a + b) / 2;
        double fa = f(a);
        double fb = f(b);
        double fc = f(c);
        double A = ((fb - fc) / (b - c) - (fc - fa) / (c - a)) / (b - a);
        double B = (fc - fa) / (c - a) + ((fb - fc) / (b - c) - (fc - fa) / (c - a)) / (b - a)*(a - c);
        double C = fa;
        double D = sqrt(pow(B, 2) - 4 * A*C);
        double x1 = a - (2 * C) / (B + D);
        double x2 = a - (2 * C) / (B - D);
        if (x1 >= a && x1 <= b)
            x = x1;
        else
            x = x2;
        if (f(a)*f(x) < 0)
            root.borders.end = x;
        else
        if (f(b)*f(x) < 0)
            root.borders.start = x;
        else {
            cerr << "������ � ������ �������" << endl;
            exit(MUELLER_ERROR);
        }
    }
}

void Verification(vector<root_with_borders>&roots) {
    for (const auto &root_with_borders:roots)
        if (fabs(f(root_with_borders.root)) > K_EPS_MUELLER) {
            cerr << "���� ������� �������� �������� ������ ���������" << endl;
            exit(VERIFICATION_ERROR);
        }
    cout << "���� ������� ������ �������� ������ ���������" << endl ;
}

void PrintRoots(vector<root_with_borders>&roots) {
    for (int i = 0; i < roots.size(); i++) {
        printf("x%d=% .5f;\n", i + 1, roots[i].root);
    }
}