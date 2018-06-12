#include<iostream>
#include<fstream>
#include<deque>
#include<sstream>

using namespace std;

double factorial(double a) {
	double ans = 1;
	for (int i = 1; i < a; i++) {
		ans *= i;
	}
	return ans;
}


int main() {

	fstream file;
	file.open("sample.txt", ios::in);
	
	int size = 0;//num of data point
				 //-------open the file and store data point into X and Y
	while (!file.eof()) {
		//deque <double> outcome;
		int a = 0;
		int b = 0;
		cout << "a:";
		cin >> a;
		cout << "b:";
		cin >> b;
		string temp;
		getline(file, temp); 
		stringstream ss(temp);
		//outcome.resize(temp.length());
		char s;
		double n = temp.length();
		double m = 0;
		for (int i = 0; i < n; i++) {
			ss >> s;
			if (s == '1')
				m++;
		}
		
		double pr = m / n;
		//cout << pow(pr, 2);

		double bino = 0;
		bino = (factorial(n) / (factorial(n - m)*factorial(m)))*pow(pr,m)*pow(1-pr,n-m);
		double beta = 0;
		beta = (factorial(a + b-1) / (factorial(a-1)*factorial(b-1)))*pow(pr, a - 1)*pow(1-pr, b - 1);
		double denom = 0;
		denom = (factorial(n) / (factorial(n - m)*factorial(m)))*(factorial(a + b - 1) / (factorial(a - 1)*factorial(b - 1)))*(factorial(m + a - 1)*factorial(n - m + b - 1) / (factorial(n + a + b - 1)));
		//cout << "denom:" << denom;
		cout << "binomial:" << bino << " " << "beta prior:" << beta<<"posterior probability:"<<bino*beta/denom<<endl;
		//cout << (factorial(n + a + b - 1) / (factorial(m + a - 1)*factorial(n - m + b - 1)))*pow(pr, a + m - 1)*pow(1 - pr, b + n - m - 1) << endl;
	}
	


	system("pause");
	return 0;
}