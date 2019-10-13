#include <iostream>
#include <string>

#include "Sigmoid.h"
#include "../Matrix/Matrix.h"

using namespace std;

Sigmoid::~Sigmoid(void) {
	cout << "Sigmoid Delete" << endl;
	delete Out;

	cout << "Sigmoid Delete" << endl;
}

Matrix* Sigmoid::forward(Matrix* X) {
	int X_rows = X->get_rows();
	int X_cols = X->get_cols();

	Out = new Matrix;
	Out->set(X_rows, X_cols);

	for (int i = 0; i < X_rows; i++) {
		for (int j = 0; j < X_cols; j++) {
			Out->set(i, j, 1/(1 + exp(-1 * X->get_M_element(i, j))));
		}
	}
	Matrix* out = Out;
	return out;
}

Matrix* Sigmoid::backward(Matrix* dOut) {
	Matrix* dX;

	int dOut_rows = dOut->get_rows();
	int dOut_cols = dOut->get_cols();
	dX = new Matrix;
	dX->set(dOut_rows, dOut_cols);

	for (int i = 0; i < dOut_rows; i++) {
		for (int j = 0; j < dOut_cols; j++) {
			dX->set(i, j, dOut->get_M_element(i, j) * (1 - Out->get_M_element(i, j)) * Out->get_M_element(i, j));
		}
	}

	return dX;
}

