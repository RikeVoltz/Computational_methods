/**
Лабораторная работа №1 по дисциплине "Вычислительные методы"
@name Main
@memo Прямые методы решения систем линейных алгебраических уравнений.
@author (c) 2017 В. В. Зелюков
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;

void InputMatrix(vector<vector<double> >&matrix, vector<vector<double> >&instant_matrix) {
	int size = 0;
	cout << "Введите размерность матрицы: ";
	cin >> size;
	matrix.resize(size);
	double element = 0;
	cout << endl << "Введите числовые коэффициенты матрицы:" << endl;
	for (int i = 0; i<size; i++)
		for (int j = 0; j<size; j++) {
			cin >> element;
			matrix[i].push_back(element);
		}
	instant_matrix.resize(matrix.size());
	for (int i = 0; i<matrix.size(); i++)
		for (int j = 0; j<matrix.size(); j++)
			instant_matrix[i].push_back(matrix[i][j]);
}

void InputFreeTerms(vector<vector<double> >&aug_matrix, vector<vector<double> >&aug_instant_matrix) {
	double element = 0;
	cout << "Введите столбец свободных членов: " << endl;
	for (int i = 0; i<aug_matrix.size(); i++) {
		cin >> element;
		aug_matrix[i].push_back(element);
		aug_instant_matrix[i].push_back(element);
	}
}

void Solution(vector<vector<double> >&matrix, vector<double>&answer) {
	int rows = matrix.size(), columns = rows + 1;
	for (int i = 0; i<rows; i++) {
		double max_term = -INF;
		int max_term_row = 0;
		for (int j = i; j<rows; j++) {
			if (fabs(matrix[j][i])>max_term) {
				max_term = fabs(matrix[j][i]);
				max_term_row = j;
			}
		}
		swap(matrix[i], matrix[max_term_row]);
		double divider = matrix[i][i];
		for (int j = i; j<columns; j++)
			matrix[i][j] /= divider;
		for (int j = i+1; j < rows; j++) {
			double multiplier = matrix[j][i];
			if (multiplier == 0)
				break;
			for (int k = i; k < columns; k++)
				matrix[j][k] -= (multiplier *matrix[i][k]);
		}
	}
	answer.push_back(matrix[rows - 1][columns - 1]);
	for (int i = rows - 2; i >= 0; i--) {
		double ans_term = 0;
		for (int j = rows - 1; j>i; j--) {
			ans_term += (matrix[i][j] * answer[rows - j - 1]);
		}
		ans_term = matrix[i][columns - 1]-ans_term;
		answer.push_back(ans_term);
	}
	reverse(answer.begin(), answer.end());
	for (int i = 0; i<rows; i++)
		cout << "x" << i + 1 << "= " << answer[i] << endl;
}

void Verification(vector<vector<double> >&instant_matrix, vector<double>&answer) {
	bool isRight = true;
	for (int i = 0; i<instant_matrix.size(); i++) {
		double temp_answer = 0;
		for (int j = 0; j<instant_matrix.size(); j++)
			temp_answer += instant_matrix[i][j] * answer[j];
		if (fabs(temp_answer - instant_matrix[i][instant_matrix.size()]) > EPS) {
			isRight = false;
			break;
		}
	}
	if (isRight)
		cout << "Были найдены верные значения корней уравнения" << endl;
	else
		cout << "Были найдены неверные значения корней уравнения" << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	vector<vector<double> >matrix;
	vector<vector<double> >instant_matrix;
	vector<double>answer;
	InputMatrix(matrix, instant_matrix);
	InputFreeTerms(matrix, instant_matrix);
	Solution(matrix, answer);
	Verification(instant_matrix, answer);
	return 0;
}