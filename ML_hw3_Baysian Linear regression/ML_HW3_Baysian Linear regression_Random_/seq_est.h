#include<iostream>
#include<cmath>
#include<time.h>
#include<deque>
using namespace std;

void seq_est(double m, double s,double expect,double var,int n) {
	/*double x = normal_data_generator(m, s);
	n++;
	//cout << x << endl;
	double old_expect = expect;
	expect = old_expect + (x - old_expect) / (double)(n);
	var = ((n - 1)*var + (x - old_expect)*(x - expect)) / (double)(n);
	cout << "expect:" << expect << " var:" << var << endl;
	if(n==10000)
		system("pause");
	
	seq_est(m, s, expect, var, n);*/
	double old_expect = expect;
	for (int n = 1; n < 100; n++) {
		double x = normal_data_generator(m, s);
		expect = old_expect + (x - old_expect) / (double)(n);
		var = ((n - 1)*var + (x - old_expect)*(x - expect)) / (double)(n);
		cout << "expect:" << expect << " var:" << var << endl;
	}
}


