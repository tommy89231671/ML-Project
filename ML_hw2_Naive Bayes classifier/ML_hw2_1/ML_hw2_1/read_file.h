#include<iostream>
#include<fstream>
#include<string>
#include<deque>
#include<sstream>
using namespace std;

int ReverseInt(int i) {
	unsigned int ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;

}
deque <double> read_image(string name,int sample) {
	deque <double> pixel;
	ifstream file(name, ios::binary);
	if (file.is_open()) {
		int description = 0;
		int images = 0;
		int rows = 0;
		int cols = 0;
		file.read((char*)&description, 4);
		description = ReverseInt(description);
		file.read((char*)&images, 4);
		images = ReverseInt(images);
		file.read((char*)&rows, 4);
		rows = ReverseInt(rows);
		file.read((char*)&cols, 4);
		cols = ReverseInt(cols); 
		//pixel.resize(images*rows*cols);
		//cout<<"magic:"<<description<<" #images:"<< images<<" rows:"<< rows<<" col"<<cols<<endl; 

		for (int i = 0; i < sample; i++) {
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					//pixel[i*28*28+j*28+k]=((double)temp);
					pixel.push_back((double)temp);
					//cout << (double)temp << " ";
				}
				

			}

		}
		
		//system("pause");
	}
	return pixel;
}
deque <int> read_label(string name, int sample) {
	deque <int> label;
	ifstream file(name, ios::binary);
	if (file.is_open()) {
		int description = 0;
		int images = 0;
		file.read((char*)&description, 4);
		description = ReverseInt(description);
		file.read((char*)&images, 4);
		images = ReverseInt(images);
		//pixel.resize(images*rows*cols);
		//label.resize(images);
		//cout << "magic:" << description << " #images:" << images <<endl;
		for (int i = 0; i < sample; i++) {
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					label.push_back((int)temp);
					//label[i] = (int)temp;
					//cout << (double)temp << " ";
		}

		//system("pause");
	}
	return label;
}


