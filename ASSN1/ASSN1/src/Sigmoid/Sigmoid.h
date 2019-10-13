#include <iostream>
#include <string>

class Matrix;

class Sigmoid
{
private:
	Matrix* Out;

public:
	Matrix* forward(Matrix* X);

	Matrix* backward(Matrix* dOut);
};
