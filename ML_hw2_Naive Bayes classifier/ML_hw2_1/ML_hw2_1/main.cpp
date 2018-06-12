#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<deque>
#include"read_file.h"
#include"train.h"
#include"test.h"

using namespace std;

int main() {
	deque <double> train_image;
	deque <int> train_label;
	deque <double> test_image;
	deque <int> test_label;
	int train_sample = 0;
	int test_sample = 0;
	cout << "train:";
	cin >> train_sample;
	cout << "test:";
	cin >> test_sample;
	
	//cout << train_image.size();
	int option = 0;
	cout << "option:";
	cin >> option;

	train_image = read_image("train-images.idx3-ubyte", train_sample);
	train_label = read_label("train-labels.idx1-ubyte", train_sample);
	test_image = read_image("t10k-images.idx3-ubyte", test_sample);
	test_label = read_label("t10k-labels.idx1-ubyte", test_sample);
	
	deque <double> bin;
	bin=train(train_image, train_label);
	
	if (option == 0) {
		test_1(bin, train_label, test_image, test_label);
	}
	else
		test_2(bin, train_label, test_image, test_label);

	
	
	
	


	system("pause");
	return 0;
}