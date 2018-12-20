/**
Лабораторная работа №1 по дисциплине "Вычислительные методы"
@name Main
@memo Прямые методы решения систем линейных алгебраических уравнений. Метод Гаусса по столбцу.
@author (c) 2017 В. В. Зелюков
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

const double EPS = 1e-9;

void InputMatrix(vector<vector<double> > &matrix) {
    size_t matrix_size = 0;
    cout << "Введите размерность матрицы: ";
    cin >> matrix_size;
    matrix.resize(matrix_size);
    cout << endl << "Введите числовые коэффициенты матрицы:" << endl;
    for (int i = 0; i < matrix_size; i++) {
        matrix[i].resize(matrix_size);
        for (auto &element:matrix[i])
            cin >> element;
    }
}

void InputFreeTerms(vector<double> &free_terms) {
    cout << "Введите столбец свободных членов: " << endl;
    for (auto &free_term:free_terms)
        cin >> free_term;
}

void Solution(vector<vector<double> > matrix, vector<double> free_terms, vector<double> &answer) {
    size_t matrix_size = matrix.size();
    for (int i = 0; i < matrix_size; i++) {
        double max_term = fabs(matrix[i][i]);
        int max_term_row = i;
        for (int j = i+1; j < matrix_size; j++) {
            if (fabs(matrix[j][i]) > max_term) {
                max_term = fabs(matrix[j][i]);
                max_term_row = j;
            }
        }
        swap(matrix[i], matrix[max_term_row]);
        swap(free_terms[i], free_terms[max_term_row]);
        double divider = matrix[i][i];
        for (int j = i; j < matrix_size; j++)
            matrix[i][j] /= divider;
        free_terms[i] /= divider;
        for (int j = i + 1; j < matrix_size; j++) {
            double multiplier = matrix[j][i];
            if (multiplier == 0)
                break;
            for (int k = i; k < matrix_size; k++)
                matrix[j][k] -= (multiplier * matrix[i][k]);
            free_terms[j] -= (multiplier * free_terms[i]);
        }
    }
    answer.push_back(free_terms.back());
    for (long i = matrix_size - 2; i >= 0; --i) {
        double ans_term = 0;
        for (long j = matrix_size - 1; j > i; --j) {
            ans_term += (matrix[i][j] * answer[matrix_size - j - 1]);
        }
        ans_term = free_terms[i] - ans_term;
        answer.push_back(ans_term);
    }
    reverse(answer.begin(), answer.end());
}

void Verification(const vector<vector<double> > &matrix,
                  const vector<double> &free_terms, const vector<double> &answer) {
    bool is_right_answer = true;
    for (int i = 0; i < matrix.size(); i++) {
        double temp_answer = 0;
        for (int j = 0; j < matrix.size(); j++)
            temp_answer += matrix[i][j] * answer[j];
        if (fabs(temp_answer - free_terms[i]) > EPS) {
            is_right_answer = false;
            break;
        }
    }
    if (is_right_answer)
        cout << "Были найдены верные значения корней уравнения" << endl;
    else
        cout << "Были найдены неверные значения корней уравнения" << endl;
}

void OutputAnswers(const vector<double>&answer){
    for (int i = 0; i < answer.size(); i++)
        cout << "x" << i + 1 << " = " << answer[i] << endl;
}
int main() {
    setlocale(LC_ALL, "rus");
    vector<vector<double> > matrix;
    vector<double> free_terms;
    vector<double> answer;
    InputMatrix(matrix);
    free_terms.resize(matrix.size());
    InputFreeTerms(free_terms);
    Solution(matrix, free_terms, answer);
    OutputAnswers(answer);
    Verification(matrix, free_terms, answer);
    return 0;
}