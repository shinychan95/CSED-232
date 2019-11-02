// 상속 시 발생하는 중첩 선언에 대한 오류를 해결하기 위해 사용한 부분
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
	Conv(float**& kernel, int& k_row, int& k_col); // 선언과 동시에 kernel에 대한 데이터 저장

	~Conv(); // destructor

	virtual void implement(float**& input, int& i_row, int& i_col); // convolution 계산 후 시각화하는 함수

	void _show(float**& matrix, int& row, int& col); // matrix 및 size를 입력받으면 출력하는 함수
};

#endif 


