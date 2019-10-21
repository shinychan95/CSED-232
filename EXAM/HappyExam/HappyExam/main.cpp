#include <iostream> // ǥ�� ����� ���̺귯�� 
#include <string>	// String Data Type ���̺귯�� 
#include <fstream>	// ���� ����� ���̺귯��
#include <iomanip>	// Manipulator ���̺귯��

using namespace std;	// �� �� ������ ��� ǥ�� �����̶� �̰� ����� �� �� ���ϰ� ��

// Class Declaration

// Virtual Function ����
class Person
{
public:
	void DoAction();

private:
	virtual void Action() = 0; 
};							   
class Student : public Person
{
private:
	virtual void Action();
};
class Employee : public Person
{
private:
	virtual void Action();
};



int main() {
	// �� ������ ���ٸ�,
	std::cout << "Hello Exam" << std::endl;
	std::string name = "Cody";
	std::ifstream file; // ������ �о�帮�� ����

	// ***Chap 1*** 
	// Figure 1.3.1
	string line;	// getline���� �Է¹ޱ� ���� ���� ���� �ʼ�
	ifstream in;
	ofstream out;
	const int num = 1;
	in.open("./data/name.txt");
	out.open("./data/out.dat");
	// getline�� ������, �Է� ���� ������, ������ Ÿ���� ���� ������ �־���� �Ѵ�.
	while (getline(in, line)) { // (istream&, string&, deli), �̸� string ���� ���� ����
		cout << line << endl;
		line.insert(num, "19"); // (index, string&), index �ʰ� �� ���� ����
		cout << line << endl;
		out << line << '\n';
	}
	in.close();
	out.close();

	// Virtual Function
	// ���� �̸��� method�� �θ� �ڽ� ���ÿ� ���� ��, Virtual Function�� ���ٸ�, �θ� �Լ��� ��ȯ ��.
	// Virtual Function���� ����ٸ�, �ش� Ŭ������ method�� ���� ��.

	// Pure Virtual Function�� (�밳) �θ� Ŭ�������� ���� ��� Virtual Function�� NULL (0)���� �����ϸ�,
	// �ش� �Լ��� pure virtual function�� �ǰ�, �� Ŭ������ abstract class�� �ȴ�.
	// ��, �߻� Ŭ������ '�߻����� ����'�� �����ϰ�, ���� ������ �ڽ� Ŭ������ �̷�� ���� ���˴ϴ�.
	// �̸� ���� �����ϸ�, ū ������ ��� ��ȣ�� ������� ���̶�� �� �� �ֽ��ϴ�.
	// �л��� �Ͼ��[����]�� �ϰ� �ῡ ���.
	// ������ �Ͼ��[��]�� �ϰ� �ῡ ���.

	Student student;
	Employee employee;

	student.DoAction();
	std::cout << std::endl;
	employee.DoAction();


	// ***Chap 2*** 
	// Ex. 2.2.3
	// �Է¹޴� ������ Ÿ������ ���α׷��� �帧�� ������ �� �ִ�.
	int val, sum = 0;
	cout << "Enter next number: ";
	/*
	while (cin >> val) {
		sum += val;
		cout << "Enter next number: ";
	}
	*/
	cout << "Sum of all values: " << sum << '\n';


	// 2.3 Files
	ifstream _file;
	string str;
	_file.open("./data/name.txt");
	if (_file >> str) // ������ �����ִٸ� True�ε�, �̴� ������ ���� ������ str�� data�� �Է¹ޱ� ������,
		cout << str << endl; // string�� �ƴ϶� int��� false�� ������ ���� ����.
	

	// reinterpret_cast
	int i;
	float f = -6.9072; // float = 4 byte
	cout << &f << endl; // �ּ�
	unsigned char* p =
		reinterpret_cast<unsigned char*>(&f); // char = 1 byte
	cout << hex; // print bytes of f in hex
	for (i = 0; i < sizeof(float); i++)
		cout << static_cast<int>(p[i]) << "\n";


	enum Color { // ������(enumerator) // �� �����ڴ� �����ݷ�(;)�� �ƴ϶� ��ǥ(,)�� ���еȴ�. 
		COLOR_BLACK, 
		COLOR_RED, 
		COLOR_BLUE, 
		COLOR_GREEN, 
		COLOR_WHITE, 
		COLOR_CYAN, 
		COLOR_YELLOW, 
		COLOR_MAGENTA, 
	}; // �׷��� enum ��ü�� �����ݷ����� ������ �Ѵ�. 
	
	   // ������ Color�� ������ ���� 
	Color paint = COLOR_WHITE; 
	Color house(COLOR_BLUE); 
	Color apple { COLOR_RED };

	cout << paint << endl;
	if (paint == 4)
		cout << "wow" << endl;
	if (paint == COLOR_WHITE)
		cout << "wow" << endl;
	
	return 0;
}



// Class Definition
void Person::DoAction()
{
	std::cout << "Good Morning!" << std::endl;
	Action();
	std::cout << "Sleep.." << std::endl;
}

// ����� �ٸ��� virtual�� �տ� ���µ�,
void Student::Action() // virtual (�����Լ�) �� ����ο��� �ѹ��� �����Ѵ�.
{						// +a static�� ������Ͽ� �����ϰ� �����Ѵ�.
	std::cout << "Study" << std::endl;
}

void Employee::Action()
{
	std::cout << "Work" << std::endl;
}

