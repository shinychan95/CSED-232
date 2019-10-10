#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Dataloader
{
private:
	string mode;
	string file_dir;
	float** data;
	float** label;
	int feature_num;
	int class_num;
	int data_num;

public:
	Dataloader(string _mode, string _file_dir, int _feature_num, int _class_num, int _data_num) {
		mode = _mode; 
		file_dir = _file_dir;
		feature_num = _feature_num;
		class_num = _class_num;
		data_num = _data_num;

		data = new float*[data_num];
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
	
	void read(void) {
		// Create a text string, which is used to output the text file
		string line;
		string delimeter = " ";

		// Read from the text file
		ifstream textfile(file_dir);
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
				label[index_of_data][stoi(line.substr(front, back - front)) - 1] = 1;
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

	void show_data(void) {
		for (int i = 0; i < data_num; i++) {
			for (int j = 0; j < feature_num; j++) {
				cout << data[i][j] << " ";
			}
			cout << "&";
			for (int k = 0; k < class_num; k++) {
				cout << label[i][k] << " ";
			}
			cout << "&";
			cout << endl;
		}

	}
};
