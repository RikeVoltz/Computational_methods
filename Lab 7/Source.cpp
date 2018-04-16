#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

const int NODES_AMOUNT = 100000;
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = 1;

struct point {
	double x;
	double f_x;
	point() :x(0), f_x(0) {};
	point(double x, double f_x) :x(x), f_x(f_x) {};
};

double f(double x) {
	return 1.0 / (2 + pow(x, 3));
}

double RectangleMethod(vector<point>&midpoints, double &step){
	double integralValue = 0;
	for (int i = 0; i < midpoints.size(); i++)
		integralValue += midpoints[i].f_x;
	integralValue *= step;
	return integralValue;
}

double TrapezoidMethod(vector<point>&grid,double &step) {
	double integralValue = 0;
	for (int i = 1; i < grid.size(); i++)
		integralValue += (grid[i].f_x+grid[i-1].f_x);
	integralValue /= 2;
	integralValue *= step;
	return integralValue;
}

double SimpsonsMethod(vector<point>&grid, vector<point>&midpoints, double &step) {
	double integralValue = 0;
	for (int i = 1; i < grid.size(); i++)
		integralValue += (grid[i-1].f_x + 4*midpoints[i-1].f_x+grid[i].f_x);
	integralValue /= 6;
	integralValue *= step;
	return integralValue;
}

vector<point> MakeGrid(double &step) {
	vector<point>grid;
	for (double i = LEFT_BORDER; i <= RIGHT_BORDER; i += step)
		grid.push_back(point(i,f(i)));
	return grid;
}

vector<point> MakeMidpoints(vector<point>&grid) {
	vector<point>midpoints;
	for (int i = 1; i < grid.size(); i++) {
		point midpoint;
		midpoint.x = (grid[i].x + grid[i - 1].x) / 2;
		midpoint.f_x = f(midpoint.x);
		midpoints.push_back(midpoint);
	}
	return midpoints;
}


int main() {
	double step = (RIGHT_BORDER - LEFT_BORDER)*1.0 / NODES_AMOUNT;
	vector<point>grid=MakeGrid(step);
	vector<point>midpoints=MakeMidpoints(grid);
	printf("Rectangle method gives %.10f\n", RectangleMethod(midpoints, step));
	printf("Trapezoid method gives %.10f\n", TrapezoidMethod(grid, step));
	printf("Simpsons method gives %.10f\n", SimpsonsMethod(grid, midpoints, step));
	return 0;
}