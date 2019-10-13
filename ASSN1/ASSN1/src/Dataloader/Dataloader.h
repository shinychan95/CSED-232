#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Dataloader
{
private:
	string mode;
	string file_dir;
	string dataset;
	float** data;
	float** label;
	int feature_num;
	int class_num;
	int data_num;

public:
	Dataloader(string _mode, string _dataset, string _file_dir, int _feature_num, int _class_num, int _data_num);
	
	string _set_file_dir(string _dataset, string _file_dir);

	void read(void);

	float** get_data(void);

	float** get_label(void);
	
	int get_feature_num(void);

	int get_class_num(void);

	int get_data_num(void);

	void show_data(void);
};
