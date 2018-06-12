#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<deque>
using namespace std;

deque <int> test_1(deque <double> bin, deque <int> train_label, deque <double> test_img, deque <int> test_label) {
	deque <int> result;
	result.resize(test_label.size());
	double prior[10] = {};
	

	for (int i = 0; i < train_label.size(); i++) {
		prior[train_label[i]]++;
	}
	for (int i = 0; i < 10; i++) {
		prior[i]=prior[i]/train_label.size();
	}
	for (int i = 0; i < test_img.size()/28/28; i++) {
		deque <double> temp_bin;
		deque <double> temp_result;
		temp_bin.resize(28*28);
		temp_result.resize(10);
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++) {
				temp_bin[28*j+k]= ((int)(test_img[i * 28 * 28 + j * 28 + k])) / 8;
			}
		}
		
		double nom[10] = {};
		double denom = 0;
		
		for (int n = 0; n < 10; n++) {
			for (int j = 0; j < 28; j++) {
				for (int k = 0; k < 28; k++) {
					double bin_sum = 0;
					for (int x = 0; x < 32; x++) {
						bin_sum += bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + x];
					}
					nom[n] += log(bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + temp_bin[28 * j + k]] / bin_sum);
					//cout<<bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + temp_bin[28 * j + k]] << " ";
				}
				//cout << endl;

				//cout << "bin:" << bin[n * 32 + k] << endl;
				//nom[n] += -log(temp_bin[k] * bin[n * 32 + k]);
			}
			//system("pause");
			nom[n] += log(prior[n]);
			//cout << nom[n] << " ";
			denom += nom[n];
		}
		double max = -1000000000;
		int max_index = 0;
		for (int n = 0; n < 10; n++) {
			//temp_result[n]= nom[n]/denom;
			temp_result[n] = nom[n];
			 //temp_result[n] = nom[n] - denom;
			 cout << temp_result[n] << " ";
			//cout << nom[n] << " ";
			 if (temp_result[n] > max) {
				 max = temp_result[n];
				 max_index = n;
			 }
		}
		cout << "result:" << max_index << endl;
		result[i] = max_index;
		
	}
	double count = 0;
	for (int i = 0; i < test_label.size(); i++) {
		if (test_label[i] != result[i])
			count++;
	}
	cout << "error:" << count / test_label.size() << endl;
	
	return result;
}

double gd(double x,double u, double var) {
	double p = 0;

	p = (1 / sqrt((2 * 3.1415926*var)))*exp(-1 * ((x - u)*(x - u) / (2 * var)));
	return p;
}



deque <int> test_2(deque <double> bin, deque <int> train_label, deque <double> test_img, deque <int> test_label) {
	deque <int> result;
	result.resize(test_label.size());
	double prior[10] = {};
	for (int i = 0; i < train_label.size(); i++) {
		prior[train_label[i]]++;
	}
	for (int i = 0; i < 10; i++) {
		prior[i] = prior[i] / train_label.size();
	}
	for (int i = 0; i < test_img.size() / 28 / 28; i++) {
		//cout << "index:" << i << endl;
		deque <double> temp_bin;
		deque <double> temp_result;
		temp_bin.resize(28 * 28);
		temp_result.resize(10);
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++) {
				temp_bin[28 * j + k] = ((int)(test_img[i * 28 * 28 + j * 28 + k])) / 8;
			}
		}
		//cout << "xxxxxxxxxx" << endl;

		deque <double> expect;
		deque <double> var;
		for (int n = 0; n < 10; n++) {

			expect.resize(10 * 28 * 28);
			var.resize(10 * 28 * 28);
			for (int j = 0; j < 28; j++) {
				for (int k = 0; k < 28; k++) {
					double sum = 0;
					double num = 0;
					for (int x = 0; x < 32; x++) {
						sum += bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + x] * x;
						num += bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + x];
					}

					/*cout << "sum:" << sum << " " << "num:" << num << endl;
					system("pause");*/
					expect[n * 28 * 28 + j * 28 + k] = sum / num;
					//cout << "expect:" << expect[i* 28 * 28 + j * 28 + k]<<endl;
					//system("pause");
					double var_sum = 0;
					for (int x = 0; x < 32; x++) {
						var_sum += bin[n * 28 * 28 * 32 + j * 28 * 32 + k * 32 + x] * pow((x - expect[n * 28 * 28 + j * 28 + k]), 2);
						var[n * 28 * 28 + j * 28 + k] = var_sum / num;
					}
					//cout << "expect:" << expect[i * 28 * 28 + j * 28 + k] << endl;
					//cout << "var:" << var[i * 28 * 28 + j * 28 + k] << endl;
				}
				//cout << endl;
			}
			//system("pause");
		}
		double nom[10] = {};
		for (int n = 0; n < 10; n++) {
			for (int j = 0; j < 28; j++) {
				for (int k = 0; k < 28; k++) {
					
					nom[n] += log(gd(temp_bin[28*j+k],expect[n * 28 * 28 + j * 28 + k], var[n * 28 * 28 + j * 28 + k]));
					//cout<<"gd:"<< log(gd(temp_bin[28 * j + k], expect[n * 28 * 28 + j * 28 + k], var[n * 28 * 28 + j * 28 + k])) <<"temp_bin:"<< temp_bin[28 * j + k]<<"exp:"<< expect[n * 28 * 28 + j * 28 + k]<<"var:"<< var[n * 28 * 28 + j * 28 + k]<<endl;
					//cout << nom[n] << " ";
				}
				//cout << nom[n] << " ";
				//system("pause");
			}
			//system("pause");
			nom[n] += log(prior[n]);
			//cout << nom[n] << " ";
			//system("pause");
			//denom += nom[n];
		}
		double max = -1000000000;
		int max_index = 0;
		for (int n = 0; n < 10; n++) {
			//temp_result[n]= nom[n]/denom;
			temp_result[n] = nom[n];
			//temp_result[n] = nom[n] - denom;
			cout << temp_result[n] << " ";
			//cout << nom[n] << " ";
			if (temp_result[n] > max) {
				max = temp_result[n];
				max_index = n;
			}
		}
		cout << "result:" << max_index << endl;
		result[i] = max_index;
		

	}
	double count = 0;
	for (int i = 0; i < test_label.size(); i++) {
		if (test_label[i] != result[i])
			count++;
	}
	cout << "error:" << count / test_label.size() << endl;
	
	return result;
}