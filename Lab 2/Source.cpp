/**
Лабораторная работа №2 по дисциплине "Вычислительные методы"
@name Main
@memo Итерационные методы решения систем линейных уравнений.
@author (c) 2017 В. В. Зелюков
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

const double INF = 1e9;
const double EPS = 1e-3;

void InputMatrix(vector<vector<double> >&matrix, vector<vector<double> >&instant_matrix) {
    int size = 0;
    cout << "ВНИМАНИЕ: Начальная матрица должна быть приведена к виду матрицы с диагональным преобладанием." << endl;
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

int StepsEstimation(vector<vector<double> >&matrix) {
    int rows = matrix.size(), columns = rows + 1;
    for (int i = 0; i < rows; i++) {
        double divider = matrix[i][i];
        for (int j = 0; j < columns; j++) {
            matrix[i][j] /= divider;
            if (j != i)
                matrix[i][j] *= -1;
        }
    }
    vector<double>sum(rows,0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (i != j)
                sum[i] += fabs(matrix[i][j]);
        }
    }
    double matrixNorm = *max_element(sum.begin(), sum.end());
    double freeNorm = -INF;
    for (int i = 0; i < rows; i++)
        if (fabs(matrix[i][columns - 1]) > freeNorm)
            freeNorm = fabs(matrix[i][columns - 1]);
    double steps = log(EPS*(1-matrixNorm)/freeNorm)/log(matrixNorm)-1;
    return (int)ceil(steps);
}

void Solution(vector<vector<double> >&matrix,int steps, vector<double>&answer, vector<vector<double> >instant_matrix) {
    int rows = matrix.size(), columns = rows + 1;
    for (int i = 0; i < rows; i++)
        answer.push_back(matrix[i][columns - 1]);
    for (int i = 1; i <= steps; i++) {
        for (int j = 0; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < rows; k++) {
                if (k != j)
                    sum += instant_matrix[j][k]*answer[k];
            }
            answer[j] = (1 / (instant_matrix[j][j]))*(instant_matrix[j][columns-1]-sum);
        }
    }
}

void Verification(vector<vector<double> >&instant_matrix, vector<double>&answer) {
    bool isRight = true;
    for (int i = 0; i<instant_matrix.size(); i++) {
        double temp_answer = 0;
        for (int j = 0; j<instant_matrix.size(); j++)
            temp_answer += instant_matrix[i][j] * answer[j];
        if (fabs(temp_answer - instant_matrix[i][instant_matrix.size()]) > EPS) {
            isRight = false;
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
    Solution(matrix,StepsEstimation(matrix),answer,instant_matrix);
    Verification(instant_matrix, answer);
    return 0;
}
