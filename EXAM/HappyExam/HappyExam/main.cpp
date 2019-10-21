#include <iostream> // ǥ�� ����� ���̺귯�� 
#include <string>	// String Data Type ����ϱ� ���ؼ�
#include <fstream>	// ���� ����� ���̺귯��

using namespace std;	// �� �� ������ ��� ǥ�� �����̶� �̰� ����� �� �� ���ϰ� ��

class Person
{
public:
	void DoAction();

private:
	virtual void Action() = 0; 
};							   // static�� ������Ͽ� �����ϰ� �����Ѵ�.

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



	// Chap 1 Figure 1.3.1
	string line;	// getline���� �Է¹ޱ� ���� ���� ���� �ʼ�
	ofstream out;
	const int num = 1;
	file.open("./data/name.txt");
	out.open("./data/out.dat");
	// getline�� ������, �Է� ���� ������, ������ Ÿ���� ���� ������ �־���� �Ѵ�.
	while (getline(file, line)) { // (istream&, string&, deli), �̸� string ���� ���� ����
		cout << line << endl;
		line.insert(num, "19"); // (index, string&), index �ʰ� �� ���� ����
		cout << line << endl;
		out << line << '\n';
	}
	file.close();
	out.close();


	// Virtual Function ����
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




	return 0;
}



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

