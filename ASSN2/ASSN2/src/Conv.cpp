#include <iostream>
#include <string>
#include <random>

#include "Conv.h"

using namespace std;

Conv::Conv(float**& kernel, int& k_row, int& k_col) {
	this->k_row = k_row;
	this->k_col = k_col;

	this->kernel = new float* [k_row];
	for (int i = 0; i < k_row; i++)
		this->kernel[i] = new float[k_col];

	for (int i = 0; i < k_row; i++) {
		for (int j = 0; j < k_col; j++) {
			this->kernel[i][j] = kernel[i][j];
		}
	}

};

Conv::~Conv() {
	for (int i = 0; i < k_row; i++) {
		delete[] this->kernel[i];
	}
	delete[] this->kernel;
};

void Conv::implement(float**& input, int& i_row, int& i_col) {
	// kernel matrix에 대한 시각화
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << k_row << " * " << k_col << " kernel";
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << endl;
	_show(this->kernel, k_row, k_col);

	// input matrix에 대한 시각화
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << "matrix";
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << endl;
	_show(input, i_row, i_col);

	// output matrix 선언 및 계산
	int o_row = i_row - k_row + 1;
	int o_col = i_col - k_col + 1;
	float** output;
	output = new float* [o_row];
	for (int i = 0; i < o_row; i++)
		output[i] = new float[o_col];

	float element;
	for (int i = 0; i < o_row; i++) {
		for (int j = 0; j < o_col; j++) {
			element = 0;
			for (int k = 0; k < k_row; k++) {
				for (int l = 0; l < k_col; l++) {
					element += input[i + k][j + l] * kernel[k][l];
				}
			}
			output[i][j] = element;
		}
	}

	// convolution 결과 시각화
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << "convolution";
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << endl;
	_show(output, o_row, o_col);

	// 포인터 해제
	for (int i = 0; i < o_row; i++) {
		delete[] output[i];
	}
	delete[] output;
};

void Conv::_show(float**& matrix, int& row, int& col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << matrix[i][j] << ", ";
		}
		cout << endl;
	}
};
