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
class Stack {
public:
	enum { MaxStack = 5 }; // public에 enum을 통해 클래스 내부 변수화. 가독성 증가.
	void init() { top = -1; }
	void push(int n) {
		if (isFull()) {
			errMsg("Fullstack.Can'tpush.");
			return;
		}
		arr[++top] = n;
	}
	int pop() { // top이라는 index를 통해 값을 계속 재입력하기 떄문에, 지워줄 필요가 없음.
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
	int arr[MaxStack]; // enum value를 통해 초기화 가능.
	int dummy_val;
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



	// Enumerated Types
	enum Color { 
		// 열거자(enumerator) 
		// 각 열거자는 세미콜론(;)이 아니라 쉼표(,)로 구분된다. 
		COLOR_BLACK, 
		COLOR_RED, 
		COLOR_BLUE, 
		COLOR_GREEN, 
		COLOR_WHITE, 
		COLOR_CYAN, 
		COLOR_YELLOW, 
		COLOR_MAGENTA
	}; // 그러나 enum 자체는 세미콜론으로 끝나야 한다.

	// 열거형 Color의 변수들 정의 
	Color paint = COLOR_WHITE; 
	Color house(COLOR_BLUE); 
	Color apple { COLOR_RED };

	cout << paint << endl; // 4 출력, +a 열거자의 값 지정 가능
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
	C* c_ptr; // C를 가리키는 포인터 정의
	float C::*f_ptr; // C의 float 멤버를 가리키는 포인터 정의
	c_ptr = &c1; // c_ptr이 c1을 가리키도록 설정
	f_ptr = &C::z; // f_ptr이 z를 가리키도록 설정
	c1.*f_ptr = 3.14; // c1.y를 3.14로 설정
	c_ptr->*f_ptr = 123.32; // c1.z에 123.32로 설정
	
	

	// cast_const의 conversion type으로 pointer와 reference만 와야하는 이유
	// 우선 const의 두 가지 측면, 리터럴 const, 상수 const 의미
	// 리터럴 const의 경우 #define과 같이 compile시 아예 true constant로 변한다고 생각하면 편하다.
	struct type {
		int i;

		type() : i(3) {} // 약간 constructor 느낌

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

	*const_cast<int*>(var) = 5; // 이런 식으로도 바꿀 수 있음

	cout << "var: " << *var << endl;

	// 결론
	// When a value of a ‘const’ variable can be calculated during the compilation, it creates a true constant.
	// That’s why there is no location in the memory that can be changed to affect all places where it is used. 
	// It is like using #define.
	// 물론 pointer를 통해서 값을 바꿀 수 있긴 하다.




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

