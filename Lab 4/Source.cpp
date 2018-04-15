#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

const double EPS = 1e-4;
const double CRITICAL_EPS = 1e-9;
const enum ERRORS { NEWTONIAN_METHOD_ERROR=1, ANSWER_CHECK_ERROR=2 };

double F(double x, double y) {
	return sin(x + y) - 1.2*x - 0.2;
}

double G(double x, double y) {
	return pow(x, 2) + pow(y, 2) - 1;
}

double Fdash_x(double x, double y){
	return cos(x + y) - 1.2;
}

double Fdash_y(double x, double y) {
	return cos(x + y);
}

double Gdash_x(double x, double y) {
	return 2 * x;
}

double Gdash_y(double x, double y) {
	return 2 * y;
}

void inputStartApproximation(double &x,double &y){
	cout << "Введите стартовые приближения корней уравнения:" << endl;
	cout << "x = ";
	cin >> x;
	cout  << "y = ";
	cin >> y;
}

void NewtonianMethod(double &x, double &y) {
	double xnew = INT_MAX;
	double ynew = INT_MAX;
	while (fabs(xnew - x) >= EPS) {
		x = xnew;
		y = ynew;
		double A = F(x, y)*Gdash_y(x, y) - Fdash_y(x, y)*G(x, y);
		double B = Fdash_x(x, y)*G(x, y) - F(x, y)*Gdash_x(x, y);
		double J = Fdash_x(x, y)*Gdash_y(x, y) - Fdash_y(x, y)*Gdash_x(x, y);
		if (fabs(J) < CRITICAL_EPS) {
			cerr << "Ошибка в методе Ньютона";
			exit(NEWTONIAN_METHOD_ERROR);
		}
		xnew = x - A / J;
		ynew = y - B / J;
	}
	x = xnew;
	y = ynew;
	return;
}

bool isRightAnswer(double x, double y) {
	return fabs(F(x, y)) < EPS && fabs(G(x, y)) < EPS;
}

void printAnswer(double x, double y,double index) {
	cout << "Корни уравнения:" << endl;
	cout << "x" << index << " = " << x << endl;
	cout << "y" << index << " = " << y << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	int rootsAmount = 0;
	cout << "Введите количество корней уравнения:" << endl;
	cin >> rootsAmount;
	for(int i=0;i<rootsAmount;i++){
		double x = 0, y = 0;
		inputStartApproximation(x, y);
		NewtonianMethod(x, y);
		printAnswer(x, y, i+1);
		if (isRightAnswer(x,y))
			cout << "Корни найдены верно." << endl;
		else {
			cerr << "Корни найдены неверно" << endl;
			exit(ANSWER_CHECK_ERROR);
		}
	}
	return 0;
}