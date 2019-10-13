#include <iostream>
#include <string>
#include <random>

using namespace std;

class Matrix;

class Affine
{
private:
	int in_dimension;
	int out_dimension;
	Matrix* W;
	Matrix* B;
	Matrix* dW;
	Matrix* dB;
	Matrix* X;

public:
	void set(int _in_dimension, int _out_dimention);

	void initial_value_setting(float std);

	int get_in_dm(void);

	int get_out_dm(void);

	Matrix* forward(Matrix* _X);

	Matrix* backward(Matrix* dOut);

	void update(float learning_rate);

};

