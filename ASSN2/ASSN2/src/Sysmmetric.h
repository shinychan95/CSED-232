#include <iostream>
#include <string>

#include "Conv.h"

using namespace std;

class Sysmmetric: public Conv
{
private:
	int padding;

public:
	Sysmmetric(float** kernel, int k_row, int k_col, int padding); // ���� �� Conv�� constructor ���(cpp����)

	virtual void implement(float**& input, int& i_row, int& i_col);
};


 