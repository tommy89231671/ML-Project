#include<iostream>
#include<cmath>
#include<time.h>
#include"data_generator.h"
#include<time.h>
#include<deque>
#include"seq_est.h"
#include"baysian.h"
using namespace std;


int main() {
	srand(time(NULL));
	deque <double> a;
	deque <double> b;
	//a.resize(100);
	//b.resize(100);
	/*for (int i = 0; i < 20; i++) {
		a.push_back(i);
	}
	for (int i = 0; i < 15; i++) {
		b.push_back(i);
	}
	matrix_mul(a, b, 4, 5, 5, 3);*/
	//seq_est(0, 1, 0, 0, 0);
	//system("pause");
	deque <double> x;
	/*for (int i = 0; i < 5; i++) {
		x.push_back(i);
	}
	a=design_matrix(x,5,3);
	b=design_Tmatrix(x, 5, 3);
	system("pause");*/
	//matrix_mul(b, a, 5, 1, 1, 5);

	bay_LR();
	system("pause");
	return 0;
}