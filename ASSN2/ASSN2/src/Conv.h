// ��� �� �߻��ϴ� ��ø ���� ���� ������ �ذ��ϱ� ���� ����� �κ�
#ifndef BASEARRAY_H_GUARD       // include guard
#define BASEARRAY_H_GUARD       // include guard 

#include <iostream>
#include <string>
#include <random>

using namespace std;

class Conv
{
private:
	float** kernel;
	int k_row;
	int k_col;

public:
	Conv(float**& kernel, int& k_row, int& k_col); // ����� ���ÿ� kernel�� ���� ������ ����

	~Conv(); // destructor

	virtual void implement(float**& input, int& i_row, int& i_col); // convolution ��� �� �ð�ȭ�ϴ� �Լ�

	void _show(float**& matrix, int& row, int& col); // matrix �� size�� �Է¹����� ����ϴ� �Լ�
};

#endif 


