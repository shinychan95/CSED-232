#include <iostream>
#include <string>


class Matrix;

class Loss
{
private:
	Matrix* Logit;
	Matrix* Label;
	Matrix* Output;
	int rows;
	int cols;

public:
	Matrix* forward(Matrix* logit, Matrix* label);
	Matrix* backward(void);
};