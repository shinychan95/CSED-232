#include <iostream>
#include <string>
#include <random>

#include "Affine.h"
#include "../Matrix/Matrix.h"

using namespace std;


Affine::~Affine(void) {
	cout << "Affine Start" << endl;
	delete W;
	delete B;
	delete dW;
	delete dB;
	delete X;
	cout << "Affine Delete" << endl;
}

void Affine::set(int _in_dimension, int _out_dimention) {
	in_dimension = _in_dimension;
	out_dimension = _out_dimention;
	W = new Matrix;
	W->set(in_dimension, out_dimension);
	B = new Matrix;
	B->set(1, out_dimension);
};

void Affine::initial_value_setting(float std) {
	W->init_val_set(std);
}

int Affine::get_in_dm(void) {
	return in_dimension;
}

int Affine::get_out_dm(void) {
	return out_dimension;
}

Matrix* Affine::forward(Matrix* _X) {
	X = new Matrix;
	X->set(_X->get_matrix(), _X->get_rows(), _X->get_cols());
	Matrix* Out;
	Out = X->multiply(W);
	Out->add_bias(B);
	return Out;
}

Matrix* Affine::backward(Matrix* dOut) {
	Matrix* dX;
	dX = W->get_transpose();
	dX = dOut->multiply(dX);
	dW = X->get_transpose();
	dW = dW->multiply(dOut);
	dB = dOut->sum_by_col();


	return dX;
}

void Affine::update(float learning_rate) {
	
	int W_rows = W->get_rows();
	int W_cols = W->get_cols();

	int B_rows = B->get_rows();
	int B_cols = B->get_cols();

	for (int i = 0; i < W_rows; i++) {
		for (int j = 0; j < W_cols; j++) {

			W->set(i, j, W->get_M_element(i, j) - (learning_rate * dW->get_M_element(i, j)));
		}
	}

	for (int i = 0; i < B_rows; i++) {
		for (int j = 0; j < B_cols; j++) {
			B->set(i, j, B->get_M_element(i, j) - (learning_rate * dB->get_M_element(i, j)));
		}
	}
}




