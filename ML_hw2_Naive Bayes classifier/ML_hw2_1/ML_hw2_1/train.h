#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<deque>
#include<cmath>
using namespace std;

deque <double> train(deque <double> img,deque <int> label) {
	deque <double> bin;
	bin.resize(10*784*32);
	int num_img = img.size() / 28 / 28;
	//cout << num_img << endl;
	for (int i = 0; i < num_img; i++) {
		int index = label[i];
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++) {
				bin[index * 28 * 28 * 32 + 28 * 32 * j + 32 * k + (((int)img[i * 28 * 28 + j * 28 + k]) / 8)]++;
			}
		}
	}
		int a = 0;

		for (int i = 0; i < 10; i++) {
			double min = 100000000000000000;
			for (int j = 0; j < 784; j++) {
				for (int k = 0; k < 32; k++) {
					if (bin[i * 32 * 28 * 28 + 32 * j + k] < min &&bin[i * 32 * 784 + 32 * j + k] != 0)
						min = bin[i * 32 * 784 + 32 * j + k];
				}
				for (int k = 0; k < 32; k++) {
					if (bin[i * 32 * 784 + 32 * j + k] == 0)
						bin[i * 32 * 784 + 32 * j + k] = min;
				}
			}

		}
	
	return bin;
}