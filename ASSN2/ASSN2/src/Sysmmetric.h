#include <iostream>
#include <string>

#include "Conv.h"

using namespace std;

class Sysmmetric: public Conv
{
private:
	int padding;

public:
	Sysmmetric(float** kernel, int k_row, int k_col, int padding); // 선언 시 Conv의 constructor 명시(cpp에서)

	virtual void implement(float**& input, int& i_row, int& i_col);
};


 