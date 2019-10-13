#include <iostream>
#include <string>
#include <random>

using namespace std;

class Matrix
{
private:
	float** M;
	int rows;
	int cols;

public:
	void set(float** data, int _rows, int _cols);

	void set(int _rows, int _cols);

	void set(int i, int j, float val);

	int get_rows(void);

	int get_cols(void);

	float get_M_element(int i, int j);

	void init_val_set(float std);

	Matrix* multiply(Matrix *X);

	void add_bias(Matrix *B);

	void view_matrix(void);

	void view_size(void);

	Matrix* get_transpose(void);

	Matrix* sum_by_col(void);

};

