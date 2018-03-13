#include<iostream>
#include<vector>
using namespace std;
const double K_EPS_DICHOTOMY = 1e-1;
const double K_EPS_MUELLER = 5e-4;
enum ERRORS { DICHOTOMY_ERROR = 1, MUELLER_ERROR = 2, VERIFICATION_ERROR=3 };

struct segment {
	double start;
	double end;
	segment();
	segment(double start, double end);
};
struct root_with_borders {
	segment borders;
	double root;
	root_with_borders();
	root_with_borders(segment borders, double root);
};

double f(double x);
void Dichotomy(root_with_borders &root);
void MuellersMethod(root_with_borders &root);
void Verification(vector<root_with_borders>&roots);
void PrintRoots(vector<root_with_borders>&roots);

int main() {
	setlocale(LC_ALL, "rus");
	cout << "Введите количество корней: ";
	int roots_amount;
	cin >> roots_amount;
	vector<root_with_borders>roots(roots_amount);
	cout << "Введите начальные границы отрезков для каждого из корней: " << endl;
	for (int i = 0; i < roots_amount; i++) {
		cin >> roots[i].borders.start >> roots[i].borders.end;
	}
	for (int i = 0; i < roots_amount; i++)
		Dichotomy(roots[i]);
	for (int i = 0; i < roots_amount; i++)
		MuellersMethod(roots[i]);
	Verification(roots);
	return EXIT_SUCCESS;
}

segment::segment() {
	start = 0;
	end = 0;
}

segment::segment(double start, double end) :start(start), end(end) {};

root_with_borders::root_with_borders() {
	borders.start = 0;
	borders.end = 0;
	root = 0;
}

root_with_borders::root_with_borders(segment borders, double root) :borders(borders.start, borders.end), root(root) {};


double f(double x) {
	return pow(x, 3) + 3 * pow(x, 2) - 1;
}

void Dichotomy(root_with_borders &root) {
	while (root.borders.end - root.borders.start >= K_EPS_DICHOTOMY / 2) {
		if (f(root.borders.end)*f(root.borders.start) > 0) {
			cerr << "Ошибка в методе дихотомии";
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
				cerr << "Ошибка в методе парабол";
				exit(MUELLER_ERROR);
			}
	}
}

void Verification(vector<root_with_borders>&roots) {
	for (int i = 0; i<(int)roots.size(); i++)
		if (fabs(f(roots[i].root)) > K_EPS_MUELLER) {
			cerr << "Были найдены неверные значения корней уравнения";
			exit(VERIFICATION_ERROR);
		}
	cout << "Были найдены верные значения корней уравнения";
}

void PrintRoots(vector<root_with_borders>&roots) {
	for (int i = 0; i < roots.size(); i++) {
		printf("x%d=% .5f;\n", i + 1, roots[i].root);
	}
}