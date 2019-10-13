#include <iostream>
#include <string>

#include "Loss.h"
#include "../Matrix/Matrix.h"


Loss::~Loss(void) {
	delete Logit;
	delete Label;
	delete Output;
}

Matrix* Loss::forward(Matrix* logit, Matrix* label) {
	Logit = new Matrix;
	Logit->set(logit->get_matrix(), logit->get_rows(), logit->get_cols());
	Label = new Matrix;
	Label->set(label->get_matrix(), label->get_rows(), label->get_cols());

	rows = Logit->get_rows();
	cols = Logit->get_cols();


	Output = new Matrix;
	Output->set(rows, 1);

	float value = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			value += (Logit->get_M_element(i, j) - Label->get_M_element(i, j)) * (Logit->get_M_element(i, j) - Label->get_M_element(i, j));
		}
		value = value / 2;
		Output->set(i, 0, value);
		value = 0;
	}

	return Output;
}

Matrix* Loss::backward(void) {
	Matrix* output;
	output = new Matrix;
	output->set(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			output->set(i, j, Logit->get_M_element(i, j) - Label->get_M_element(i, j));
		}
	}

	return output;
}
