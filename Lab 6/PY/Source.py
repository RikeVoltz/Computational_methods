import numpy as np
import matplotlib.pyplot as plt


class Point:
    x: float
    f_x: float

    def __init__(self, x, f_x):
        self.x = x
        self.f_x = f_x


class BoundCondition:
    m_first: float
    m_second: float
    sum: float

    def __init__(self, params):
        self.m_first = params[0]
        self.m_second = params[1]
        self.sum = params[2]


def input_values():
    print("Input amount of points:")
    points_amount = int(input())
    print("\nInput x and function values of x in each point:\n")
    points = []
    for i in range(points_amount):
        x, f_x = [float(i) for i in input().split()]
        points.append(Point(x, f_x))
    return points


def input_border_statements():
    left_condition = BoundCondition(
        [float(i) for i in input("Input coefficients from left border statement:\n").split()]
    )
    right_condition = BoundCondition(
        [float(i) for i in input("\nInput coefficients from right border statement:\n").split()]
    )
    return left_condition, right_condition


def make_system_of_equations(points, splines_amount, left_condition, right_condition):
    # Make first (special) equation
    system_of_equations = np.zeros(shape=(splines_amount, splines_amount), dtype=float)
    new_free_terms = np.zeros(shape=splines_amount, dtype=float)
    delta_x = points[1].x - points[0].x
    delta_x_next = points[2].x - points[1].x
    system_of_equations[0][0] = 2 * (
            delta_x + delta_x_next) - delta_x * left_condition.m_second / left_condition.m_first
    system_of_equations[0][1] = delta_x_next
    new_free_terms[0] = -delta_x * left_condition.sum / left_condition.m_first

    # Make from 2 to n-1 ordinary equations
    for i in range(1, splines_amount - 1):
        delta_x = points[i + 1].x - points[i].x
        delta_x_next = points[i + 2].x - points[i + 1].x
        delta_f_x = points[i + 1].f_x - points[i].f_x
        delta_f_x_next = points[i + 2].f_x - points[i + 1].f_x
        system_of_equations[i][i - 1] = delta_x
        system_of_equations[i][i] = 2 * (delta_x + delta_x_next)
        system_of_equations[i][i + 1] = delta_x_next
        new_free_terms[i] = 6 * (delta_f_x_next / delta_x_next - delta_f_x / delta_x)

    # Make last (special) equation
    system_of_equations[splines_amount - 1][splines_amount - 2] = right_condition.m_first
    system_of_equations[splines_amount - 1][splines_amount - 1] = right_condition.m_second
    new_free_terms[splines_amount - 1] = right_condition.sum
    return system_of_equations, new_free_terms


def main():
    points = input_values()
    left_condition, right_condition = input_border_statements()
    points_amount = len(points)
    splines_amount = points_amount - 1
    matrix, free_terms = make_system_of_equations(points, splines_amount, left_condition, right_condition)
    c = np.linalg.solve(matrix, free_terms)
    a = []
    b = []
    d = []
    delta_x = points[1].x - points[0].x
    delta_f_x = points[1].f_x - points[0].f_x
    a.append(points[1].f_x)
    b.append(delta_f_x / (points[1].x - points[0].x) + delta_x / 6 * (
            (2 - left_condition.m_second / left_condition.m_first) * c[0] +
            left_condition.sum / left_condition.m_first))
    d.append(
        (1 + left_condition.m_second / left_condition.m_first) * c[0] -
        left_condition.sum / left_condition.m_first)
    for i in range(1, splines_amount):
        delta_x = points[i + 1].x - points[i].x
        delta_f_x = points[i].f_x - points[i - 1].f_x
        delta_f_x_next = points[i + 1].f_x - points[i].f_x
        a.append(points[i + 1].f_x)
        d.append((c[i] - c[i - 1]) / delta_x)
        b.append((delta_f_x_next - delta_f_x) / delta_x + delta_x * c[i] / 2 - delta_x**2 * d[i] / 6)
    for i in range(splines_amount):
        x_axe = np.arange(points[i].x, points[i + 1].x, 1e-6)
        y_seq = map(lambda x: a[i] + b[i] * (x - points[i].x) + c[i] / 2 * ((x - points[i].x) ** 2) + d[i] / 6 * (
                (x - points[i].x) ** 3), x_axe)
        y_axe = np.fromiter(y_seq, dtype=np.float)
        plt.plot(x_axe, y_axe)
    plt.show()


main()
# print(x_axe,y_axe)
# 0.2 1.2214
# 0.26 1.2765
# 0.28 1.3071
# 0.31 1.3456
# 0.32 1.3775
# 0.38 1.4568
# 2 0.5 1.8765
# 0.3 2 3.4567


# 0.1 1.1052
# 0.15 1.1618
# 0.19 1.2092
# 0.25 1.2840
# 0.28 1.3231
# 0.30 0.3499
# 2 1 3.3722
# 0.5 2 3.3614
