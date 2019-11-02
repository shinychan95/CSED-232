#include "Zero.h"

// constructor
Zero::Zero(float** kernel, int k_row, int k_col, int padding)
	: Conv(kernel, k_row, k_col) // constructor 명시
{
	this->padding = padding;
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << "Zero Padding Convolution";
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << endl;
};

void Zero::implement(float**& input, int& i_row, int& i_col) {
	// padded matrix 생성
	int p_row = i_row + padding * 2;
	int p_col = i_col + padding * 2;
	float** padded;
	padded = new float* [p_row];
	for (int i = 0; i < p_row; i++)
		padded[i] = new float[p_col];

	// 모든 원소를 0으로 채운다.
	for (int i = 0; i < p_row; i++) {
		for (int j = 0; j < p_col; j++) {
			padded[i][j] = 0;
		}
	}

	// input matrix를 중앙에 입력시킨다.
	for (int i = 0; i < i_row; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[i + padding][j + padding] = input[i][j];
		}
	}

	// convolution 계산 실행
	Conv::implement(padded, p_row, p_col);


	for (int i = 0; i < p_row; i++) {
		delete[] padded[i];
	}
	delete[] padded;
};