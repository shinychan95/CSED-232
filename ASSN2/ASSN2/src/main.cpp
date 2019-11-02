#include <iostream>
#include <string>

#include "Conv.h"
#include "Zero.h"
#include "Reflect.h"
#include "Sysmmetric.h"

using namespace std;

void str_to_matrix(string& elements, int& row, int& col, float** &kernel) {
	string delimeter = " ";
	auto front = 0;
	auto back = elements.find(delimeter);
	
	kernel = new float*[row];
	for (int i = 0; i < row; i++)
		kernel[i] = new float[col];

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			kernel[i][j] = stoi(elements.substr(front, back - front));
			front = back + delimeter.length();
			back = elements.find(delimeter, front);
		}
	}
}

bool check_input(int k_row, int k_col, int i_row, int i_col) {
	bool result = true;
	if (k_row > 0 and k_row % 2 == 1)
		return false;
	if (k_col > 0 and k_col % 2 == 1)
		return false;
	if (i_row > 10 or i_col > 10)
		return false;
	return true;
}

int main() {
	// 임의의 kernel matrix와 size를 입력 받는다.
	int k_row = 3;
	int k_col = 3;
	int i_row = 4;
	int i_col = 4;
	string k = "1 3 2 3 5 7 1 2 3";
	string i = "1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8";

	// input data의 요구사항을 확인한다.
	if (check_input(k_row, k_col, i_row, i_col)) {
		cout << "Error: input data is not possible size" << endl;
		return 0;
	}

		
	// matrix 형태로 바꿔준다.
	float** kernel;
	float** input;
	str_to_matrix(k, k_row, k_col, kernel);
	str_to_matrix(i, i_row, i_col, input);

	// Convoltion을 선언 후 실행한다.
	Conv C(kernel, k_row, k_col);
	C.implement(input, i_row, i_col);

	int padding = 2;
	Zero Z(kernel, k_row, k_col, padding);
	Z.implement(input, i_row, i_col);

	Reflect R(kernel, k_row, k_col, padding);
	R.implement(input, i_row, i_col);

	Sysmmetric S(kernel, k_row, k_col, padding);
	S.implement(input, i_row, i_col);

	for (int i = 0; i < k_row; i++) {
		delete[] kernel[i];
	}
	delete[] kernel;

	for (int i = 0; i < i_row; i++) {
		delete[] input[i];
	}
	delete[] input;

	return 0;
}

