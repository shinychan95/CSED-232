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
	// padded matrix ����
	int p_row = i_row + padding * 2;
	int p_col = i_col + padding * 2;
	float** padded;
	padded = new float* [p_row];
	for (int i = 0; i < p_row; i++)
		padded[i] = new float[p_col];

	// �߾� �κп� input data �Է�
	for (int i = 0; i < i_row; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[i + padding][j + padding] = input[i][j];
		}
	}

	// 8�κ����� ������ �����͸� �Է½�Ų��.
	// ��
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_row; j++) {
			padded[i][padding + j] = padded[i + 2 * (padding - i) - 1][padding + j];
		}
	}
	// �Ʒ�
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_row; j++) {
			padded[p_row - 1 - i][padding + j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][padding + j];
		}
	}
	// ����
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[padding + j][i] = padded[padding + j][i + 2 * (padding - i) - 1];
		}
	}
	// ������
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < i_col; j++) {
			padded[padding + j][p_col - 1 - i] = padded[padding + j][p_col - 1 - i - 2 * (padding - i) + 1];
		}
	}
	// �밢�� ����
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[i][j] = padded[i + 2 * (padding - i) - 1][j + 2 * (padding - j) - 1];
		}
	}
	// �밢�� ����
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[i][p_col - 1 - j] = padded[i + 2 * (padding - i) - 1][p_col - 1 - j - 2 * (padding - j) + 1];
		}
	}
	// �밢�� �Ʒ���
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[p_row - 1 - i][j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][j + 2 * (padding - j) - 1];
		}
	}
	// �밢�� �Ʒ���
	for (int i = 0; i < padding; i++) {
		for (int j = 0; j < padding; j++) {
			padded[p_row - 1 - i][p_col - 1 - j] = padded[p_row - 1 - i - 2 * (padding - i) + 1][p_col - 1 - j - 2 * (padding - j) + 1];
		}
	}

	// convolution ��� ����
	Conv::implement(padded, p_row, p_col);


	for (int i = 0; i < p_row; i++) {
		delete[] padded[i];
	}
	delete[] padded;
};





