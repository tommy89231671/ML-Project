#include<iostream>
#include<cmath>
#include<time.h>
#include<deque>
using namespace std;
void print_matrix(deque <double>A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << A[i*col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
deque <double> matrix_mul(deque <double> A, deque <double> B,int a_row,int a_col,int b_row,int b_col) {
	deque <double> C;
	for (int i = 0; i < a_row; i++) {
		for (int j = 0; j < b_col; j++) {
			double c = 0;
			//cout << "xxxxx";
			
			for (int k = 0; k < b_row; k++) {
				c += A[i*b_row + k] * B[k*(b_col) + j];
				
			}
			//cout << "c:" << c << endl;
			
			C.push_back(c);
		}
		
	}
	//print_matrix(C, a_row, a_col);
	return C;
}
deque <double> matrix_scalar(double a, deque <double> A, int a_row, int a_col) {
	deque <double> C;
	for (int i = 0; i < a_row; i++) {
		for (int j = 0; j < a_col; j++) {
			C.push_back(a*A[i*a_col + j]);
		}
	}
	//print_matrix(C, a_row, a_col);
	return C;
}
deque <double> matrix_add(deque <double> A, deque <double> B, int row, int col) {
	deque <double> C;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			C.push_back(A[i*col + j]+B[i*col+j]);
		}
	}
	//print_matrix(C, row, col);
	return C;
}
deque <double> matrix_inverse(deque <double>A, int row, int col) {

	deque <double> U_matrix;
	for (int i = 0; i < A.size(); i++) {
		U_matrix.push_back(A[i]);
	}
	deque <double> mulbox;
	for (int i = 0; i < row; i++) {
		//i pivot
		for (int j = i + 1; j <= row - 1; j++) {
			double mul = U_matrix[j*row + i] / U_matrix[i*row + i];
			mulbox.push_back(mul);
			for (int k = i; k < row; k++) {
				U_matrix[j*row + k] -= U_matrix[i*row + k] * mul;
			}
		}
	}
	deque <double> L_matrix;
	L_matrix.resize(U_matrix.size());
	for (int i = 0; i < row; i++) {
		for (int j = 0; j <row; j++) {
			if (i == j) {
				L_matrix[i*row + j] = 1;
			}
			else if (i < j) {
				double temp = mulbox[0];
				L_matrix[j*row + i] = temp;
				mulbox.pop_front();
			}
		}
	}
	deque <double> z;
	deque <double> inverse;
	inverse.resize(row*row);

	for (int n = 0; n<row; n++) {
		z.clear();
		z.resize(row);
		z[n] = 1;
		for (int i = n + 1; i<row; i++) {
			double temp = 0;
			for (int j = 0; j<i; j++) {
				temp += L_matrix[i*row + j] * z[j];
			}
			z[i] = -temp;
		}
		deque <double>x;
		x.resize(row);
		x[row - 1] = z[row - 1] / U_matrix[row*row - 1];

		for (int i = row - 2; i>-1; i--) {
			double temp = 0;
			for (int j = row - 1; j>i; j--) {
				temp += x[j] * U_matrix[i*row + j];
			}
			x[i] = (z[i] - temp) / U_matrix[i*row + i];
		}
		for (int i = 0; i<row; i++) {
			inverse[i*row + n] = x[i];
		}


	}
	//print_matrix(inverse, row, col);
	return inverse;
}
deque <double> design_matrix(deque <double> x,int size,int base) {
	deque <double> D;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < base; j++) {
			D.push_back(pow(x[i], j));
		}
	}
	//print_matrix(D, size, base);
	return D;

}
deque <double> design_Tmatrix(deque <double> x,  int size, int base) {
	deque <double> DT;
	for (int i = 0; i < base; i++) {
		for (int j = 0; j < size; j++) {
			DT.push_back(pow(x[j], i));
		}
	}
	//print_matrix(DT,base,size);
	return DT;

}
void bay_LR() {
	//for data generator
	int n,a = 0;
	deque <double> weight;//for data generator 
	cout << "n:";//n for base
	cin >> n;
	cout << "a:";//a for precision
	cin >> a;
	weight.resize(n);
	cout << "weight:";
	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}
	deque <double> b;//precision
	b.resize(n*n);
	cout << "b:";
	for (int i = 0; i < n; i++) {
		cin >> b[i*n + i];
	}
	//first iteration
	double x,y = 0;
	polynomial_data_generator(n, a, weight, x, y);
	deque <double> xbox;
	deque <double> Y;//size*1
	xbox.push_back(x);
	Y.push_back(y);
	deque <double> XT;//n*size
	deque <double> X;//size*n
	
	int size = 1;
	XT=design_Tmatrix(xbox,size,n);
	X=design_matrix(xbox, size, n);
	
	deque <double> post_sig;//sigma matrix n*n
	post_sig = matrix_mul(XT, X, n, 1, 1, n);
	post_sig = matrix_scalar(a, post_sig,n,n);
	post_sig = matrix_add(post_sig, b,n,n);

	deque <double> post_sig_inverse;//n*n
	post_sig_inverse = matrix_inverse(post_sig, n, n);

	deque <double> post_mean;//n*1
	post_mean = matrix_mul(post_sig_inverse, XT, n, n, n, size);
	post_mean = matrix_mul(post_mean, Y, n, size, size, 1);
	post_mean = matrix_scalar(a, post_mean, n, 1);

	deque <double> prior_mean;
	deque <double> prior_sig;
	//i #datapoint try 100 times
	for (int i = 2; i <= 100; i++) {
		size=i;
		prior_mean = post_mean;
		prior_sig = post_sig;
		polynomial_data_generator(n, a, weight, x, y);
		//cout << x << " " << y << endl;
		xbox.push_back(x);
		Y.push_back(y);
		XT = design_Tmatrix(xbox, size, n);
		X = design_matrix(xbox, size, n);
		post_sig = matrix_add(prior_sig, matrix_scalar(a, matrix_mul(XT, X, n, size, size, n), n, n), n, n);
		post_sig_inverse = matrix_inverse(post_sig, n, n);
		post_mean = matrix_mul(post_sig_inverse, matrix_add(matrix_mul(prior_sig, prior_mean, n, n, n, 1), matrix_scalar(a, matrix_mul(XT, Y, n, size, size, 1), n, 1), n, 1),n,n, n, 1);
		print_matrix(post_mean, n, 1);
		//print_matrix(post_sig, n, n);
		//print_matrix(post_sig_inverse, n, n);
	}




	


}