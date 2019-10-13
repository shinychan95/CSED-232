#include <iostream>
#include <string>

class Matrix;

class Sigmoid
{
private:
	Matrix* Out;

public:
	~Sigmoid(void);

	Matrix* forward(Matrix* X);

	Matrix* backward(Matrix* dOut);
};
