#include "../Affine/Affine.h"
#include "../Sigmoid/Sigmoid.h"
#include "../Loss/Loss.h"
#include "../Matrix/Matrix.h"
#include "../Dataloader/Dataloader.h"

#include "MLP.h"

#include <math.h> 

using namespace std;


MLP::~MLP(void) {
	delete[] affine;
	delete[] sigmoid;
	delete loss;
	delete train_data;
	delete train_label;
	delete vali_data;
	delete vali_label;
	delete test_data;

}

MLP::MLP(int _epochs, float _learning_rate, int _num_of_hidden_layer, int* _arr_of_neuron, int _features, int _classes) {
	epochs = _epochs;
	learning_rate = _learning_rate;
	num_of_hidden_layer = _num_of_hidden_layer;
	arr_of_neuron = _arr_of_neuron;
	features = _features;
	classes = _classes;
}

void MLP::read_dataset(Dataloader& train, Dataloader& vali, Dataloader& test) {
	train.read();
	vali.read();
	test.read();

	train_data = new Matrix;
	train_label = new Matrix;
	vali_data = new Matrix;
	vali_label = new Matrix;
	test_data = new Matrix;

	train_data->set(train.get_data(), train.get_data_num(), train.get_feature_num());
	train_label->set(train.get_label(), train.get_data_num(), train.get_class_num());
	vali_data->set(vali.get_data(), vali.get_data_num(), vali.get_feature_num());
	vali_label->set(vali.get_label(), vali.get_data_num(), vali.get_class_num());
	test_data->set(test.get_data(), test.get_data_num(), test.get_feature_num());

}


void MLP::set_layers(void) {
	if (num_of_hidden_layer >= 2) {
		affine = new Affine[num_of_hidden_layer + 1];
		sigmoid = new Sigmoid[num_of_hidden_layer + 1];
		affine[0].set(features, arr_of_neuron[0]);
		affine[0].initial_value_setting(10 / sqrt(features));
		for (int i = 1; i < num_of_hidden_layer; i++) {
			affine[i].set(arr_of_neuron[i - 1], arr_of_neuron[i]);
			affine[i].initial_value_setting(10 / sqrt(arr_of_neuron[i - 1]));
		}
		affine[num_of_hidden_layer].set(arr_of_neuron[num_of_hidden_layer - 1], classes);
		affine[num_of_hidden_layer].initial_value_setting(10.2 / sqrt(arr_of_neuron[num_of_hidden_layer - 1]));
	}
	else {
		affine = new Affine[num_of_hidden_layer + 1];
		sigmoid = new Sigmoid[num_of_hidden_layer + 1];
		affine[0].set(features, arr_of_neuron[0]);
		affine[0].initial_value_setting(10 / sqrt(features));
		affine[num_of_hidden_layer].set(arr_of_neuron[num_of_hidden_layer - 1], classes);
		affine[num_of_hidden_layer].initial_value_setting(10.1 / sqrt(arr_of_neuron[num_of_hidden_layer - 1]));
	}

}

void MLP::visualize_layers(void) {
	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "Layer 0 - in_dimension:  " << features <<
		"  out_dimension:  " << arr_of_neuron[0] << endl;
	for (int i = 0; i < num_of_hidden_layer - 1; i++) {
		cout << "Layer " << i + 1 << " - in_dimension:  " << arr_of_neuron[i]
			<< "  out_dimension:  " << arr_of_neuron[i + 1] << endl;
	}
	cout << "Layer " << num_of_hidden_layer << " - in_dimension:  " << arr_of_neuron[num_of_hidden_layer - 1]
		<< "  out_dimension:  " << classes << endl;


	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << endl;
}

void MLP::train(void) {
	Matrix* X;
	loss = new Loss;
	for (int i = 0; i < epochs; i++) {
		X = train_data;
		for (int j = 0; j < num_of_hidden_layer + 1; j++) {
			X = affine[j].forward(X);
			X = sigmoid[j].forward(X);
		}
		float accuracy = calculate_accuracy(X, train_label);

		X = loss->forward(X, train_label);
		float m_loss = calculate_mean_loss(X);

		cout << "Epoch:   " << i << "     " << "Train Loss:   " << m_loss << "     " << "Train Accuracy:   " << accuracy << endl;

		X = loss->backward();
		for (int j = num_of_hidden_layer; j >= 0; j--) {
			X = sigmoid[j].backward(X);
			X = affine[j].backward(X);
		}

		for (int j = 0; j < num_of_hidden_layer + 1; j++)
			affine[j].update(learning_rate);
	}

}



void MLP::validation(void) {
	Matrix* V;
	V = vali_data;

	for (int j = 0; j < num_of_hidden_layer + 1; j++) {
		V = affine[j].forward(V);
		V = sigmoid[j].forward(V);
	}
	float accuracy = calculate_accuracy(V, train_label);

	V = loss->forward(V, train_label);
	float m_loss = calculate_mean_loss(V);

	cout << "Validation Loss:   " << m_loss << "     "<< "Validation Accuracy:   " << accuracy << endl;

}

void MLP::predict(Dataloader &test, string test_output_dir) {
	test.read();

	ofstream file;
	float max_value = 0;
	float max_index = 0;

	Matrix* T;
	T = test_data;
	
	
	for (int i = 0; i < num_of_hidden_layer + 1; i++) {
		T = affine[i].forward(T);
		T = sigmoid[i].forward(T);
	}

	file.open(test_output_dir + "\\result.txt");
	for (int i = 0; i < test.get_data_num(); i++) {
		for (int j = 0; j < test.get_class_num(); j++) {
			if (T->get_M_element(i, j) > max_value) {
				max_value = T->get_M_element(i, j);
				max_index = j;
			}
		}
		file << max_index << endl;
	}
	file.close();

}

float MLP::calculate_accuracy(Matrix* y, Matrix* t) {
	int rows = y->get_rows();
	int cols = y->get_cols();

	float count = 0;

	float max_y_value = 0;
	int max_y_index = 0;
	float max_t_value = 0;
	int max_t_index = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (y->get_M_element(i, j) > max_y_value) {
				max_y_value = y->get_M_element(i, j);
				max_y_index = j;
			}
			if (t->get_M_element(i, j) > max_t_value) {
				max_t_value = t->get_M_element(i, j);
				max_t_index = j;
			}
		}
		if (max_y_index == max_t_index) {
			count = count + 1;
		}
		max_y_value = 0;
		max_y_index = 0;
		max_t_value = 0;
		max_t_index = 0;
	}
	return count / rows;
}

float MLP::calculate_mean_loss(Matrix* M) {
	float sum = 0;
	for (int i = 0; i < M->get_rows(); i++) {
		sum += M->get_M_element(i, 0);
	}

	return sum / M->get_rows();
}
