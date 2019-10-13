#include <iostream>
#include <string>

#include "./Matrix/Matrix.h"
#include "./Dataloader/Dataloader.h"
#include "./MLP/MLP.h"

using namespace std;

// change data type from string to array.
int* divide_neurons(string neurons, int num) {
	string delimeter = " ";
	auto front = 0;
	auto back = neurons.find(delimeter);
	int* neuron_arr;
	neuron_arr = new int[num];
	
	for (int i = 0; i < num - 1; i++) {
		neuron_arr[i] = stoi(neurons.substr(front, back - front));
		front = back + delimeter.length();
		back = neurons.find(delimeter, front);
	}
	neuron_arr[num-1] = stoi(neurons.substr(front, back - front));
	
	return neuron_arr;
}

int main(int argc, char* argv[]) {
	if (argc != 15) {
		cout << "Error: There Are Not Enough Argument" << endl;
		return false;
	}

	string dataset_type = argv[1];
	if (dataset_type == "two moon")
		dataset_type = "two_moon";

	int feature_num = atoi(argv[2]);
	int class_num = atoi(argv[3]);
	int hidden_layer_num = atoi(argv[4]);
	string hidden_layer_neurons = argv[5];

	// change data type.
	int* hidden_layer_neuron_arr;
	hidden_layer_neuron_arr = new int[hidden_layer_num];
	hidden_layer_neuron_arr = divide_neurons(hidden_layer_neurons, hidden_layer_num);

	int epochs = atoi(argv[6]);
	float learning_rate = atof(argv[7]);
	string train_data_dir = argv[8]; 
	int train_data_num = atoi(argv[9]); 
	string validation_data_dir = argv[10]; 
	int validation_data_num = atoi(argv[11]); 
	string test_data_dir = argv[12]; 
	int test_data_num = atoi(argv[13]); 
	string test_output_dir = argv[14]; 


	Dataloader train_data("train", dataset_type, train_data_dir, feature_num, class_num, train_data_num);
	Dataloader vali_data("val", dataset_type, validation_data_dir, feature_num, class_num, validation_data_num);
	Dataloader test_data("test", dataset_type, test_data_dir, feature_num, class_num, test_data_num);

	MLP mlp(epochs, learning_rate, hidden_layer_num, hidden_layer_neuron_arr, feature_num, class_num);
	mlp.read_dataset(train_data, vali_data);
	mlp.set_layers();
	mlp.visualize_layers();
	mlp.train();
	mlp.validation();
	mlp.predict(test_data, test_output_dir);

	return 0;
}