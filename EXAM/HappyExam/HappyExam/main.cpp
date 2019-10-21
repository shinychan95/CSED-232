#include <iostream> // 표준 입출력 라이브러리 
#include <string>	// String Data Type 라이브러리 
#include <fstream>	// 파일 입출력 라이브러리
#include <iomanip>	// Manipulator 라이브러리

using namespace std;	// 위 세 가지가 사실 표준 내장이라서 이걸 해줘야 셋 다 편하게 씀

// Class Declaration

// Virtual Function 관련
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
	// 위 선언이 없다면,
	std::cout << "Hello Exam" << std::endl;
	std::string name = "Cody";
	std::ifstream file; // 파일을 읽어드리는 변수

	// ***Chap 1*** 
	// Figure 1.3.1
	string line;	// getline에서 입력받기 위한 변수 선언 필수
	ifstream in;
	ofstream out;
	const int num = 1;
	in.open("./data/name.txt");
	out.open("./data/out.dat");
	// getline의 변수로, 입력 파일 변수와, 데이터 타입을 가진 변수를 넣어줘야 한다.
	while (getline(in, line)) { // (istream&, string&, deli), 미리 string 변수 선언 주의
		cout << line << endl;
		line.insert(num, "19"); // (index, string&), index 초과 시 오류 주의
		cout << line << endl;
		out << line << '\n';
	}
	in.close();
	out.close();

	// Virtual Function
	// 같은 이름의 method가 부모 자식 동시에 있을 때, Virtual Function이 없다면, 부모 함수만 소환 됨.
	// Virtual Function으로 만든다면, 해당 클래스의 method가 실행 됨.

	// Pure Virtual Function은 (대개) 부모 클래스에서 구현 대신 Virtual Function에 NULL (0)값을 대입하면,
	// 해당 함수는 pure virtual function이 되고, 그 클래스는 abstract class가 된다.
	// 즉, 추상 클래스는 '추상적인 형태'만 제안하고, 실제 구현은 자식 클래스로 미루기 위해 사용됩니다.
	// 이를 쉽게 비유하면, 큰 명제에 몇개의 괄호를 비워놓은 것이라고 할 수 있습니다.
	// 학생은 일어나서[공부]를 하고 잠에 든다.
	// 직원은 일어나서[일]을 하고 잠에 든다.

	Student student;
	Employee employee;

	student.DoAction();
	std::cout << std::endl;
	employee.DoAction();


	// ***Chap 2*** 
	// Ex. 2.2.3
	// 입력받는 데이터 타입으로 프로그램의 흐름을 조절할 수 있다.
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
	if (_file >> str) // 파일이 열려있다면 True인데, 이는 파일이 열려 있으면 str에 data가 입력받기 때문에,
		cout << str << endl; // string이 아니라 int라면 false로 데이터 받지 않음.
	

	// reinterpret_cast
	int i;
	float f = -6.9072; // float = 4 byte
	cout << &f << endl; // 주소
	unsigned char* p =
		reinterpret_cast<unsigned char*>(&f); // char = 1 byte
	cout << hex; // print bytes of f in hex
	for (i = 0; i < sizeof(float); i++)
		cout << static_cast<int>(p[i]) << "\n";


	enum Color { // 열거자(enumerator) // 각 열거자는 세미콜론(;)이 아니라 쉼표(,)로 구분된다. 
		COLOR_BLACK, 
		COLOR_RED, 
		COLOR_BLUE, 
		COLOR_GREEN, 
		COLOR_WHITE, 
		COLOR_CYAN, 
		COLOR_YELLOW, 
		COLOR_MAGENTA, 
	}; // 그러나 enum 자체는 세미콜론으로 끝나야 한다. 
	
	   // 열거형 Color의 변수들 정의 
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

// 선언과 다르게 virtual이 앞에 없는데,
void Student::Action() // virtual (가상함수) 는 선언부에서 한번만 선언한다.
{						// +a static은 헤더파일에 선언하고 구현한다.
	std::cout << "Study" << std::endl;
}

void Employee::Action()
{
	std::cout << "Work" << std::endl;
}

