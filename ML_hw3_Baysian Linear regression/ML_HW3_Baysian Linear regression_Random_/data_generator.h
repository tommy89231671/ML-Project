#include<iostream>
#include<cmath>
#include<time.h>
#include<deque>
using namespace std;

double normal_data_generator(double m, double s) {
	//srand(time(NULL));
	double u = rand() / double(RAND_MAX);
	double v = rand() / double(RAND_MAX);
	double x = sqrt(-2 * log(u))*cos(2 * 3.1415926*v)*sqrt(s) + m;
	//y = sqrt(-2 * log(u))*sin(2 * 3.1415926*v)*sqrt(s) + m;
	//cout << x << endl;
	return x;
}
void polynomial_data_generator(int n, double a, deque <double> w,double &x,double &y) {
//srand(time(NULL));
x = ((rand() / double(RAND_MAX)) - 0.5) * 20;
y = 0;
//deque <double> X;
//X.resize(n);
for (int i = 0; i < n; i++) {
y += pow(x, i)*w[i];
}
double temp = 0;
temp=normal_data_generator(0, a);
//cout << "temp:" << temp << endl;
y += temp;
}