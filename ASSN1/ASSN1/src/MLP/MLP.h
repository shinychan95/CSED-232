using namespace std;

class Matrix;
class Sigmoid;
class Affine;
class Loss;
class Dataloader;

class MLP
{
private:
	Affine* affine;
	Sigmoid* sigmoid;
	Loss* loss;
	Matrix* train_data;
	Matrix* train_label;
	Matrix* vali_data;
	Matrix* vali_label;
	int epochs;
	int num_of_hidden_layer;
	int features;
	int classes;
	int* arr_of_neuron;
	float learning_rate;

public:
	MLP(int _epochs, float _learning_rate, int _num_of_hidden_layer, int* _arr_of_neuron, int _features, int _classes);

	void read_dataset(Dataloader& train, Dataloader& vali);

	void set_layers(void);

	void visualize_layers(void);

	void train(void);

	void validation(void);

	void predict(Dataloader& test, string test_output_dir);

	float calculate_accuracy(Matrix* y, Matrix* t);

	float calculate_mean_loss(Matrix* M);
};