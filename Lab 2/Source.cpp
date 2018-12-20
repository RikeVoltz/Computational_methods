/**
Лабораторная работа №2 по дисциплине "Вычислительные методы"
@name Main
@memo Итерационные методы решения систем линейных уравнений. Метод Якоби
@author (c) 2017 В. В. Зелюков
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

const double EPS = 1e-3;

void InputMatrix(vector<vector<double> > &matrix) {
    size_t size = 0;
    cout << "ВНИМАНИЕ: Начальная матрица должна быть приведена к виду матрицы с диагональным преобладанием." << endl;
    cout << "Введите размерность матрицы: ";
    cin >> size;
    matrix.resize(size);
    double element = 0;
    cout << endl << "Введите числовые коэффициенты матрицы:" << endl;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            cin >> element;
            matrix[i].push_back(element);
        }
}

void CheckMatrix(const vector<vector<double> > &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        double row_sum = 0;
        for (int j = 0; j < matrix.size(); j++) {
            if (i != j)
                row_sum += fabs(matrix[i][j]);
        }
        if (row_sum >= fabs(matrix[i][i])) {
            cerr << "ОШИБКА: Начальная матрица не являлась матрицей с диагональным преобладанием." << endl;
            exit(1);
        }
    }
}

void InputFreeTerms(vector<vector<double> > &aug_matrix) {
    double element = 0;
    cout << "Введите столбец свободных членов: " << endl;
    for (auto &row:aug_matrix) {
        cin >> element;
        row.push_back(element);
    }
}

int StepsEstimation(vector<vector<double> > &matrix) {
    size_t rows = matrix.size(), columns = rows + 1;
    for (int i = 0; i < rows; i++) {
        double divider = matrix[i][i];
        for (int j = 0; j < columns; j++) {
            matrix[i][j] /= divider;
            if (j != i)
                matrix[i][j] *= -1;
        }
    }
    vector<double> sum(rows, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (i != j)
                sum[i] += fabs(matrix[i][j]);
        }
    }
    double matrix_norm = *max_element(sum.begin(), sum.end());
    double free_norm = fabs(matrix[0][columns - 1]);
    for (int i = 1; i < rows; i++)
        if (fabs(matrix[i][columns - 1]) > free_norm)
            free_norm = fabs(matrix[i][columns - 1]);
    double steps = log(EPS * (1 - matrix_norm) / free_norm) / log(matrix_norm) - 1;
    return (int) ceil(steps);
}

void Solution(vector<vector<double> > &matrix, int steps, vector<double> &answer) {
    size_t rows = matrix.size(), columns = rows + 1;
    for (int i = 0; i < rows; i++)
        answer.push_back(matrix[i][columns - 1]);
    for (int i = 1; i <= steps; i++) {
        for (int j = 0; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < rows; k++) {
                if (k != j)
                    sum += matrix[j][k] * answer[k];
            }
            answer[j] = (1 / (matrix[j][j])) * (matrix[j][columns - 1] - sum);
        }
    }
}

void Verification(vector<vector<double> > &instant_matrix, vector<double> &answer) {
    bool is_right_answer = true;
    for (int i = 0; i < instant_matrix.size(); i++) {
        double temp_answer = 0;
        for (int j = 0; j < instant_matrix.size(); j++)
            temp_answer += instant_matrix[i][j] * answer[j];
        if (fabs(temp_answer - instant_matrix[i][instant_matrix.size()]) > EPS) {
            is_right_answer = false;
        }
    }
    if (is_right_answer)
        cout << "Были найдены верные значения корней уравнения" << endl;
    else
        cout << "Были найдены неверные значения корней уравнения" << endl;
}

void OutputAnswer(const vector<double> &answer) {
    for (size_t i = 0; i < answer.size(); i++)
        cout << "x" << i + 1 << " = " << answer[i] << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<vector<double> > matrix;
    vector<double> answer;
    InputMatrix(matrix);
    CheckMatrix(matrix);
    InputFreeTerms(matrix);
    Solution(matrix, StepsEstimation(matrix), answer);
    OutputAnswer(answer);
    Verification(matrix, answer);
    return 0;
}
