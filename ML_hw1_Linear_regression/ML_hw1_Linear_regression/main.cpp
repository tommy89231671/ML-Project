#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<deque>
#include<cmath>
using namespace std;
int main() {
	
fstream file;
file.open("datapoint.txt", ios::in);
deque <double> X;
deque <double> Y;
int size = 0;//num of data point
			 //-------open the file and store data point into X and Y
while (!file.eof()) {
	string temp;
	getline(file, temp);
	double a = 0;
	double b = 0;
	stringstream ss(temp);
	char trash;
	ss >> a;
	ss >> trash;
	ss >> b;
	X.push_back(a);
	Y.push_back(b);
	size++;
	//cout << a <<" "<< b << endl;
}
int base;
cout << "Intput the number of polynomial bases:";
cin >> base;
cout << "Intput lambda:";
int lambda;
cin >> lambda;
//A_matrix
deque <double> A_matrix;
for (int i = 0; i < size; i++) {
	for (int j = base; j >-1; j--) {
		A_matrix.push_back(pow(X[i], j));
	}
}
//AT_matrix
deque <double> AT_matrix;
for (int i = base; i >-1; i--) {
	for (int j = 0; j <size; j++) {
		AT_matrix.push_back(pow(X[j], i));
	}
}
/*
//A_matrix
for (int i = 0; i < size; i++) {
	for (int j = 0; j <base+1; j++) {
		A_matrix.push_back(pow(X[i], j));
	}
}
//AT_matrix
deque <double> AT_matrix;
for (int i = 0; i <base+1; i++) {
	for (int j = 0; j <size; j++) {
		AT_matrix.push_back(pow(X[j], i));
	}
}
*/
//print AT
/*cout << "AT:" << endl;
for (int i = 0; i <base + 1; i++) {
	for (int j = 0; j <size; j++) {
		cout << AT_matrix[(size)*i + j] << " ";
	}
	cout << endl;
}
cout << endl;
//print A
cout << "A:" << endl;
for (int i = 0; i < size; i++) {
	for (int j = 0; j <base + 1; j++) {
		cout << A_matrix[(base + 1)*i + j] << " ";
	}
	cout << endl;
}*/
//cout << endl;
//AT*A
deque <double> ATA;
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
		double c = 0;
		for (int k = 0; k < size; k++) {
			c += AT_matrix[i*size + k] * A_matrix[k*(base + 1) + j];
		}
		ATA.push_back(c);
	}
}
//print ATA
/*
cout << "ATA:" << endl;
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
		cout << ATA[i*(base + 1) + j] << " ";
	}
	cout << endl;
}*/
//cout << endl;
//ATA+lambda*I
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
		if (i == j) {
			ATA[i*(base + 1) + j] += lambda;
		}
	}
}
//print ATA+lambda*I
/*
cout << "ATA+lambda*I:" << endl;
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
		cout << ATA[i*(base + 1) + j] << " ";
	}
	cout << endl;
}*/
//cout << endl;
//copy ATA to U
deque <double> U_matrix;
for (int i = 0; i < ATA.size(); i++) {
	U_matrix.push_back(ATA[i]);
}


//LU:determine U first,store multiplier in mulbox so that to determine L
deque <double> mulbox;
int row = base + 1;
for (int i = 0; i < row; i++) {
	//i pivot
	for (int j = i + 1; j <= row-1; j++) {
		//cout<<"xxxxxx"<<endl;
		double mul = U_matrix[j*row + i] / U_matrix[i*row + i];
		//cout<<"1:"<<A[j*row + i]<<" "<<"2:"<<A[i*row + i]<<endl;
		//cout<<"mul:"<<mul<<endl;
		//system ("pause");
		mulbox.push_back(mul);
		for (int k = i; k < row; k++) {
			U_matrix[j*row + k] -= U_matrix[i*row + k] * mul;
		}
	}
}
//print U
cout << "U:" << endl;
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
		cout << U_matrix[i*row + j] << " ";
	}
	cout << endl;
}
cout << endl;

cout << "mulbox:" << endl;
//print mulbox
for (int i = 0; i < mulbox.size(); i++) {
	cout << mulbox[i] << " ";
}
cout << endl;

//determin L
deque <double> L_matrix;
L_matrix.resize(U_matrix.size());
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < base + 1; j++) {
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

//print L
cout << "L:" << endl;
for (int i = 0; i < row; i++) {
	for (int j = 0; j < row; j++) {
		cout << L_matrix[i*row + j] << " ";
	}
	cout << endl;
}
//cout << endl;
//find inverse by LUx=b;let z=Ux and Lz=b b=I;x will be the inverse matrix. 
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
	/*for(int i=0;i<row;i++){
	cout<<z[i]<<" ";
	}*/
	//cout << endl;
	deque <double>x;
	x.resize(row);
	x[row - 1] = z[row - 1] / U_matrix[row*row - 1];

	//system("pause");

	for (int i = row - 2; i>-1; i--) {
		double temp = 0;
		for (int j = row - 1; j>i; j--) {
			temp += x[j] * U_matrix[i*row + j];
		}
		x[i] = (z[i] - temp) / U_matrix[i*row + i];
	}
	/*for(int i=0;i<row;i++){
	cout<<x[i]<<" ";
	}*/
	for (int i = 0; i<row; i++) {
		inverse[i*row + n] = x[i];
	}

}
cout << "inverse:" << endl;
for (int i = 0; i<row; i++) {
	for (int j = 0; j<row; j++) {
		cout << inverse[i*row + j] << " ";

	}
	cout << endl;
}
cout << endl;

/*for (int i = 0; i < row; i++) {
	for (int j = 0; j < row; j++) {
		double temp = 0;
		
	}
}
*/
//inv(ATA + lambda*I)*AT
deque <double> invATA_AT;
for (int i = 0; i < base + 1; i++) {
	for (int j = 0; j < size; j++) {
		double c = 0;
		for (int k = 0; k < row; k++) {
			
			c += inverse[i*row + k] * AT_matrix[k*size + j];
			/*if (i == 1) {
				cout << "inverse:" << inverse[i*row + k] << endl;
				cout << "AT:" << AT_matrix[k*size + j] << endl;
				
			}*/
		}
		//cout << "result:" << c << endl;
		invATA_AT.push_back(c);
	}
}
//print inv(ATA + lambda*I)*AT
//cout << "ATA - 1 * AT" << endl;
/*for (int i = 0; i < size*row; i++) {
	cout << invATA_AT[i] << " ";

}*/
/*
for (int i = 0; i < row; i++) {
	for (int j = 0; j < size; j++) {
		cout<<invATA_AT[i*size+j]<<" ";
	}
	cout << endl;
}
cout << endl;
*/
//get the coefficient of function inv(ATA+lambda*I)*AT*b;
deque <double> cof;
for (int i = 0; i < row; i++) {
	double temp = 0;
	for (int j = 0; j < size; j++) {
		temp+= invATA_AT[i*size + j] * Y[j];
	}
	cof.push_back(temp);
}
//print cof
cout << "cof:" << endl;
for (int i = 0; i < cof.size(); i++) {
	
	cout << "x"<<cof.size()-1-i<<":"<<cof[i] << endl;
}

//error
double error = 0;
for (int i = 0; i < size; i++) {
	double temp = 0;
	for (int j = 0; j < row; j++) {
		temp += A_matrix[i*row + j] * cof[j];
		//cout << "temp:" << temp << endl;
	}
	//cout << "Y[i]:"<<Y[i] << endl;
	//cout << "xxx:" << temp - Y[i] << endl;
	error += pow(temp-Y[i], 2);

}
cout << endl;
cout << "error:" << error << endl;


	system("pause");
	return 0;
}