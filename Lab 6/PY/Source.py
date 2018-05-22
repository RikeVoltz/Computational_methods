import numpy as np


def input_values():
    print("Input amount of points:")
    points_amount = int(input())
    print("\nInput x and function values of x in each point:\n")
    instant_values = []
    for i in range(points_amount):
        x, f_x = (float(i) for i in input().split())
        instant_values.append((x, f_x))
    return instant_values


def make_matrix(instant_values):
    splinesAmount = len(instant_values)
    matrix = [[0] * (splinesAmount * 3)] * (splinesAmount * 3)
    free_terms = [0] * (splinesAmount * 3)
    for i in range(1, splinesAmount):
        delta_x = instant_values[i][0] - instant_values[i - 1][0]
        delta_f = instant_values[i][1] - instant_values[i - 1][1]
        matrix[i][i] = delta_x
        matrix[i][i + splinesAmount] = -delta_x ** 2 / 2
        matrix[i][i + splinesAmount * 2] = delta_x ** 3 / 6
        free_terms[i] = delta_f
        if i != 1:
            matrix[i + splinesAmount][i - 1] = 1
            matrix[i + splinesAmount][i] = -1
            matrix[i + splinesAmount][i + splinesAmount] = delta_x
            matrix[i + splinesAmount][i + splinesAmount * 2] = -delta_x ** 2 / 2
            matrix[i + splinesAmount * 2][i + splinesAmount - 1] = 1
            matrix[i + splinesAmount * 2][i + splinesAmount] = -1
            matrix[i + splinesAmount * 2][i + splinesAmount * 2] = delta_x
        else:
            m0, m1, alpha = (float(j) for j in input().split())
            m4, m5, beta = (float(j) for j in input().split())
            matrix[i + splinesAmount][splinesAmount + 1] = m0 + m1
            free_terms[i + splinesAmount] = alpha
            matrix[i + splinesAmount * 2][splinesAmount * 2] = m4 + m5
            free_terms[i + splinesAmount * 2] = beta
    return matrix, free_terms


instant_values = input_values()
matrix, free_terms = make_matrix(instant_values)
answer = np.linalg.solve(matrix, free_terms)
print(answer)

# S[i](x)=a[i]+b[i](x-x[i])+c[i](x-x[i])^2/2+d[i](x-x[i])^3/6
