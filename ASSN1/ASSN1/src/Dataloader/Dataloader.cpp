#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Dataloader.h"

using namespace std;


Dataloader::Dataloader(string _mode, string _dataset, string _file_dir, int _feature_num, int _class_num, int _data_num) {
	mode = _mode;
	dataset = _dataset;
	file_dir = _set_file_dir(_dataset, _file_dir);
	feature_num = _feature_num;
	class_num = _class_num;
	data_num = _data_num;

	data = new float* [data_num];
	for (int i = 0; i < data_num; i++) {
		data[i] = new float[feature_num];
	}

	if (_mode != "test") {
		label = new float* [data_num];
		for (int i = 0; i < data_num; i++) {
			label[i] = new float[class_num];
			for (int j = 0; j < class_num; j++) {
				label[i][j] = 0;
			}
		}
	}
}

Dataloader::~Dataloader() {
	cout << "Dataloader Start" << endl;
	for (int i = 0; i < data_num; i++) {
		delete[] data[i];
		if(mode != "test")
			delete[] label[i];
	}

	delete[] data;
	delete[] label;

	cout << "Dataloader Delete" << endl;
}

// If the last name of file_dir argument is dataset_name, just return file_dir.
// However, if If the last name of file_dir argument is "data", return file_dir+"\\"+dataset_name.
string Dataloader::_set_file_dir(string _dataset, string _file_dir) {
	string delimeter = "\\";
	auto front = 0;
	auto back = _file_dir.find(delimeter);

	while (back != std::string::npos) {
		front = back + delimeter.length();
		back = _file_dir.find(delimeter, front);
	}

	if (_file_dir.substr(front, back - front) != _dataset) {
		return _file_dir + "\\" + _dataset;
	}

	return _file_dir;
}

void Dataloader::read(void) {
	// Create a text string, which is used to output the text file
	string line;
	string delimeter = " ";
	string file = file_dir + "\\" + dataset + "_" + mode + ".txt";

	// Read from the text file
	ifstream textfile(file);
	int index_of_data = 0;
	int index_of_feature = 0;
	int index_of_label = 0;

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(textfile, line)) {
		auto front = 0;
		auto back = line.find(delimeter);

		while (back != std::string::npos) {
			data[index_of_data][index_of_feature] = stof(line.substr(front, back - front));
			front = back + delimeter.length();
			back = line.find(delimeter, front);
			index_of_feature++;
		}

		//cout << feature_num << endl;
		if (index_of_feature == feature_num) {
			if(dataset == "iris")
				label[index_of_data][stoi(line.substr(front, back - front)) - 1] = 1;
			else
				label[index_of_data][stoi(line.substr(front, back - front))] = 1;
		}
		else {
			data[index_of_data][index_of_feature] = stof(line.substr(front, back - front));
		}
		index_of_data++;
		index_of_feature = 0;
		//cout << line << endl;
	}

	// Close the file
	textfile.close();
}

float** Dataloader::get_data(void) {
	return data;
}

float** Dataloader::get_label(void) {
	return label;
}

int Dataloader::get_feature_num(void) {
	return feature_num;
}

int Dataloader::get_data_num(void) {
	return data_num;
}

int Dataloader::get_class_num(void) {
	return class_num;
}

void Dataloader::show_data(void) {
	for (int i = 0; i < data_num; i++) {
		for (int j = 0; j < feature_num; j++) {
			cout << data[i][j] << " ";
		}
		cout << "( ";
		for (int k = 0; k < class_num; k++) {
			cout << label[i][k] << " ";
		}
		cout << ")";
		cout << endl;
	}

}
