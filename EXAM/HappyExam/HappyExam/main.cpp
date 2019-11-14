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
class Stack {
public:
	enum { MaxStack = 5 }; // public�� enum�� ���� Ŭ���� ���� ����ȭ. ������ ����.
	void init() { top = -1; }
	void push(int n) {
		if (isFull()) {
			errMsg("Fullstack.Can'tpush.");
			return;
		}
		arr[++top] = n;
	}
	int pop() { // top�̶�� index�� ���� ���� ��� ���Է��ϱ� ������, ������ �ʿ䰡 ����.
		if (isEmpty()) {
			errMsg("Emptystack.Poppingdummyvalue.");
			return dummy_val;
		}
		return arr[top--];
	}
	bool isEmpty() { return top < 0; }
	bool isFull() { return top >= MaxStack - 1; }
	void dump() {
		cout << "Stackcontents,toptobottom:\n";
		for (int i = top; i >= 0; i--)
			cout << '\t' << arr[i] << '\n';
	}
private:
	void errMsg(const char* msg)const {
		cerr << "\n***Stackoperationfailure:" << msg << '\n';
	}
	int top;
	int arr[MaxStack]; // enum value�� ���� �ʱ�ȭ ����.
	int dummy_val;
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



	// Enumerated Types
	enum Color { 
		// ������(enumerator) 
		// �� �����ڴ� �����ݷ�(;)�� �ƴ϶� ��ǥ(,)�� ���еȴ�. 
		COLOR_BLACK, 
		COLOR_RED, 
		COLOR_BLUE, 
		COLOR_GREEN, 
		COLOR_WHITE, 
		COLOR_CYAN, 
		COLOR_YELLOW, 
		COLOR_MAGENTA
	}; // �׷��� enum ��ü�� �����ݷ����� ������ �Ѵ�.

	// ������ Color�� ������ ���� 
	Color paint = COLOR_WHITE; 
	Color house(COLOR_BLUE); 
	Color apple { COLOR_RED };

	cout << paint << endl; // 4 ���, +a �������� �� ���� ����
	if (paint == 4)
		cout << "Can Use enum index" << endl;
	if (paint == COLOR_WHITE)
		cout << "Can Use enum value" << endl;
	


	// Member Selector Operators
	struct C {
		int x;
		float y;
		float z;
	};
	
	float f;
	int* i_ptr;
	C c1, c2;
	C* c_ptr; // C�� ����Ű�� ������ ����
	float C::*f_ptr; // C�� float ����� ����Ű�� ������ ����
	c_ptr = &c1; // c_ptr�� c1�� ����Ű���� ����
	f_ptr = &C::z; // f_ptr�� z�� ����Ű���� ����
	c1.*f_ptr = 3.14; // c1.y�� 3.14�� ����
	c_ptr->*f_ptr = 123.32; // c1.z�� 123.32�� ����
	
	

	// cast_const�� conversion type���� pointer�� reference�� �;��ϴ� ����
	// �켱 const�� �� ���� ����, ���ͷ� const, ��� const �ǹ�
	// ���ͷ� const�� ��� #define�� ���� compile�� �ƿ� true constant�� ���Ѵٰ� �����ϸ� ���ϴ�.
	struct type {
		int i;

		type() : i(3) {} // �ణ constructor ����

		void f(int v) const {
			// this->i = v;                 // compile error: this is a pointer to const
			const_cast<type*>(this)->i = v; // OK as long as the type object isn't const
		}
	};

	type t;
	cout << "t: " << t.i << endl;

	i = 3;                 // i is not declared const
	const int& rci = i;
	const_cast<int&>(rci) = 4; // OK: modifies i
	std::cout << "i = " << i << '\n';

	int number = 3;
	const int* var = &number;

	*const_cast<int*>(var) = 5; // �̷� �����ε� �ٲ� �� ����

	cout << "var: " << *var << endl;

	// ���
	// When a value of a ��const�� variable can be calculated during the compilation, it creates a true constant.
	// That��s why there is no location in the memory that can be changed to affect all places where it is used. 
	// It is like using #define.
	// ���� pointer�� ���ؼ� ���� �ٲ� �� �ֱ� �ϴ�.




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

