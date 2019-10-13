#include <iostream>
#include <string>
#include <random>

#include "Matrix.h"

using namespace std;

void Matrix::set(float** data, int _rows, int _cols) {
	rows = _rows;
	cols = _cols;

	M = new float* [rows];
	for (int i = 0; i < rows; i++) {
		M[i] = new float[cols];
		for (int j = 0; j < cols; j++) {
			M[i][j] = data[i][j];
		}
	}
}

void Matrix::set(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
	M = new float* [rows];
	for (int i = 0; i < rows; i++) {
		M[i] = new float[cols];
		for (int j = 0; j < cols; j++) {
			M[i][j] = 0;
		}
	}
}

void Matrix::set(int i, int j, float val) {
	M[i][j] = val;
}

int Matrix::get_rows(void) {
	return rows;
}

int Matrix::get_cols(void) {
	return cols;
}

float Matrix::get_M_element(int i, int j) {
	return M[i][j];
}

void Matrix::init_val_set(float std) {
	default_random_engine generator;
	normal_distribution<float> distribution(0, std);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			M[i][j] = distribution(generator);
		}
	}
}

Matrix* Matrix::multiply(Matrix *W) {
	try {
		if (cols != W->get_rows())
		{
			throw cols;
		}
	}
	catch (int &cols) {
		cout << "Error: Can't Multiply. dimensions are not match." << endl;
	}

	Matrix* Output;
	Output = new Matrix;
	Output->set(rows, W->get_cols());
	float value = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < W->get_cols(); j++) {
			for (int k = 0; k < cols; k++) {
				value += M[i][k] * W->get_M_element(k, j);
			}
			Output->set(i, j, value);
			value = 0;
		}
	}

	

	return Output;


}

void Matrix::add_bias(Matrix *B) {
	try {
		if (cols != B->get_cols())
		{
			throw cols;
		}
	}
	catch (int &cols) {
		cout << "Error: Can't Add Bias. dimensions are not match." << endl;
	}

	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			M[i][j] += B->get_M_element(0, j);
		}
	}

}

Matrix* Matrix::get_transpose(void) {
	Matrix* Output;
	Output = new Matrix;
	Output->set(cols, rows);
	

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			Output->set(i, j, M[j][i]);
		}
	}

	return Output;
}

Matrix* Matrix::sum_by_col(void) {
	Matrix* Output;
	Output = new Matrix;
	Output->set(1, cols);
	
	float value = 0;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			value += M[j][i];
		}
		Output->set(0, i, value);
		value = 0;
	}

	return Output;
}

void Matrix::view_matrix(void) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::view_size(void) {
	cout << "Size : " << rows << " X " << cols << endl;
}