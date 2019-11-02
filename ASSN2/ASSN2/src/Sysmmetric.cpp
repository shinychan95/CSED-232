#include "Sysmmetric.h"

Sysmmetric::Sysmmetric(float** kernel, int k_row, int k_col, int padding)
	: Conv(kernel, k_row, k_col)
{
	this->padding = padding;
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << "Sysmmetric Padding Convolution";
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << endl;
};

void Sysmmetric::implement(float**& input, int& i_row, int& i_col) {
	// padded matrix 선언
	int p_row = i_row + padding * 2;
	int p_col = i_col + padding * 2;
	float** padded;
	padded = new float* [p_row];
	for (int i = 0; i < p_row; i++)
		padded[i] = new float[p_col];

	// 중앙 부분에 input data 입력
	for (int i = 0; i < i_row; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[i + padding][j + padding] = input[i][j];
		}
	}

	// 8부분으로 나누어 데이터를 입력시킨다.
	// 위
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_row; j++) {
			padded[i][padding + j] = padded[i + 2 * (padding - i) - 1][padding + j];
		}
	}
	// 아래
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_row; j++) {
			padded[p_row - 1 - i][padding + j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][padding + j];
		}
	}
	// 왼쪽
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[padding + j][i] = padded[padding + j][i + 2 * (padding - i) - 1];
		}
	}
	// 오른쪽
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[padding + j][p_col - 1 - i] = padded[padding + j][p_col - 1 - i - 2 * (padding - i) + 1];
		}
	}
	// 대각선 위왼
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[i][j] = padded[i + 2 * (padding - i) - 1][j + 2 * (padding - j) - 1];
		}
	}
	// 대각선 위오
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[i][p_col - 1 - j] = padded[i + 2 * (padding - i) - 1][p_col - 1 - j - 2 * (padding - j) + 1];
		}
	}
	// 대각선 아래왼
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[p_row - 1 - i][j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][j + 2 * (padding - j) - 1];
		}
	}
	// 대각선 아래오
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[p_row - 1 - i][p_col - 1 - j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][p_col - 1 - j - 2 * (padding - j) + 1];
		}
	}

	// convolution 계산 실행
	Conv::implement(padded, p_row, p_col);


	for (int i = 0; i < p_row; i++) {
		delete[] padded[i];
	}
	delete[] padded;
};





