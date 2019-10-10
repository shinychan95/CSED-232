#include <iostream>
#include <string>
#include <typeinfo> // ¿¬½À



#include "Dataloader.h"
#include "MLP.h"



using namespace std;


void view_arg(int argc, char* argv[]) {
	cout << "argc: " << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "argv: " << argv[i] << endl;
		cout << "type: " << typeid(argv[i]).name() << endl;
	}
}



int main(int argc, char* argv[]) {
	if (argc != 15) {
		cout << "Error: There Are Not Enough Argument" << endl;
		return false;
	}

	string dataset_type = argv[1];
	int feature_num = atoi(argv[2]);
	int class_num = atoi(argv[3]);
	int hidden_layer_num = atoi(argv[4]);
	int hidden_layer_neurons = atoi(argv[5]);
	int epochs = atoi(argv[6]);
	float learning_rate = atof(argv[7]);
	string train_data_dir = argv[8];
	int train_data_num = atoi(argv[9]);
	string validation_data_dir = argv[10];
	int validation_data_num = atoi(argv[11]);
	string test_data_dir = argv[12];
	int test_data_num = atoi(argv[13]);
	string test_output_dir = argv[14];

	/*
	cout << dataset_type << endl;
	cout << feature_num << endl;
	cout << class_num << endl;
	cout << hidden_layer_num << endl;
	cout << hidden_layer_neurons << endl;
	cout << epochs << endl;
	cout << learning_rate << endl;
	cout << train_data_dir << endl;
	cout << train_data_num << endl;
	cout << validation_data_dir << endl;
	cout << validation_data_num << endl;
	cout << test_data_dir << endl;
	cout << test_data_num << endl;
	cout << test_output_dir << endl;
	*/

	Dataloader train_data("train", train_data_dir, feature_num, class_num, train_data_num);
	train_data.read();
	Dataloader val_data("val", validation_data_dir, feature_num, class_num, train_data_num);
	val_data.read();
	Dataloader test_data("test", test_data_dir, feature_num, class_num, train_data_num);
	test_data.read();

	
	train_data.show_data();

	return 0;
}