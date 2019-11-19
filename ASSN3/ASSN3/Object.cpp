#pragma once

#include "Object.h"
#include <string>
#include <iostream>

using namespace std;


Object::Object(int x, int y, Object* prev, Object* next) { //생성자는 x, y좌표와 이전 노드와 다음 노드를 받는다. 자식 클래스들도 마찬가지
	this->x = x;
	this->y = y;
	this->prev = prev;
	this->next = next;
};
void Object::Remove() { //오브젝트가 제거됨
	Object* _prev = prev;
	Object* _next = next;

	if (next != nullptr) {
		next->SetPrev(_prev);
	}
	if (prev != nullptr) {
		prev->SetNext(_next);
	}
};
void Object::SetX(int x) { //x좌표 지정
	this->x = x;
};
void Object::SetY(int y) { //y좌표 지정
	this->y = y;
};
int Object::GetX() { //x좌표 리턴 
	return x;
};
int Object::GetY() { //y좌표 리턴
	return y;
};
Object* Object::GetNext() { //다음 노드 리턴
	return next;
};
Object* Object::GetPrev() { //이전 노드 리턴
	return prev;
};
void Object::SetNext(Object* next) { //다음 노드 지정
	this->next = next;
};
void Object::SetPrev(Object* prev) { //이전 노드 지정
	this->prev = prev;
};
bool Object::Move(Direction dir) { //오브젝트가 한 칸 dir 방향으로 (이동할 수 있다면) 이동
	MoveXY(x, y, dir);
	return true;
};
void Object::RuleCheck() { //맵의 문장을 읽어 각 개체에 속성을 부여한다. [Is 클래스에서 처리하는 것을 권장]

};
bool Object::IsEntityText() { //Entity 클래스나 그 클래스의 자식이라면 true를 리턴
	return false;
};
bool Object::IsPropertyText() { //Property 클래스나 그 클래스의 자식이라면 true를 리턴
	return false;
};
Complement Object::GetPropertyBit() { //Text가 현재 담당하고 있는 Entity나 Property를 리턴 (Complement Enum)
	return null;
};
int* Object::GetPropertyPointer() { //Non-Text인 클래스에 있는 property 변수를 가리키는 포인터
	return nullptr;
};
int Object::GetProperty() { //Non-Text인 클래스에 있는 property 값을 리턴
	return 0;
};
void Object::YouMove(Direction dir) { //Non-Text에서 YOU 속성을 가지고 있다면 dir 방향으로 이동 [조건 체크 후 Object::Move를 호출하는 것을 권장]
};
void Object::ChangeEntity() { //Non-Text에서 현재 property 변수를 보고 다른 개체로 바뀌어야 한다면 바꾸는 작업을 수행

};
string Object::ToString() { //오브젝트의 종류에 따라 맵 상에 출력되는 string이 다르다
	return "";
};




Baba::Baba(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {
};
void Baba::InitRule() { //맵에서 문장을 읽기 전에 모든 오브젝트의 속성을 초기화 해야한다.
	property = NULL;
}
string Baba::ToString() {
	return "b";
};
int Baba::GetProperty() {
	return property;
}
void Baba::YouMove(Direction dir) {
	if (property & YOU)
		Object::Move(dir);
}
bool Baba::Move(Direction dir) {
	if (property & PUSH) {
		return Object::Move(dir);
	}
	return false;
};
void Baba::ChangeEntity() {
	Object* tmp;
	if (property & ROCK) {
		tmp = new Rock(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & WALL) {
		tmp = new Wall(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & FLAG) {
		tmp = new Flag(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
}




Rock::Rock(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {

}
void Rock::InitRule() {
	property = NULL;
}
string Rock::ToString() {
	return "r";
}
int Rock::GetProperty() {
	return property;
}
void Rock::YouMove(Direction dir) {
	if (property & YOU) {
		Object::Move(dir);
	}
}
bool Rock::Move(Direction dir) {
	if (property & PUSH) {
		return Object::Move(dir);
	}
	return false;
}
void Rock::ChangeEntity() {
	Object* tmp;

	if (property & BABA) {
		tmp = new Baba(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & WALL) {
		tmp = new Wall(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & FLAG) {
		tmp = new Flag(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
}



Wall::Wall(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {

}
void Wall::InitRule() {
	property = NULL;
}
string Wall::ToString() {
	return "w";
}
int Wall::GetProperty() {
	return property;
}
void Wall::YouMove(Direction dir) {
	if (property & YOU) {
		Object::Move(dir);
	}
}
bool Wall::Move(Direction dir) {
	if (property & PUSH) {
		return Object::Move(dir);
	}
	return false;
}
void Wall::ChangeEntity() {
	Object* tmp;

	if (property & ROCK) {
		tmp = new Rock(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & BABA) {
		tmp = new Baba(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & FLAG) {
		tmp = new Flag(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
}


Flag::Flag(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {

}
void Flag::InitRule() {
	property = NULL;
}
string Flag::ToString() {
	return "f";
}
int Flag::GetProperty() {
	return property;
}
void Flag::YouMove(Direction dir) {
	if (property & YOU) {
		Object::Move(dir);
	}
}
bool Flag::Move(Direction dir) {
	if (property & PUSH) {
		return Object::Move(dir);
	}
	return false;
}
void Flag::ChangeEntity() {
	Object* tmp;

	if (property & ROCK) {
		tmp = new Rock(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & WALL) {
		tmp = new Wall(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
	else if (property & BABA) {
		tmp = new Baba(this->GetX(), this->GetY(), this->GetPrev(), this->GetNext());
		if (this->GetPrev() != nullptr) {
			this->GetPrev()->SetNext(tmp);
		}
		if (this->GetNext() != nullptr) {
			this->GetNext()->SetPrev(tmp);
		}
	}
}



Text::Text(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {
}
bool Text::Move(Direction dir) {
	Object::Move(dir);
	return true;
}

Entity::Entity(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {
}
bool Entity::IsEntityText() {
	return true;
}


BabaText::BabaText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {

}
int* BabaText::GetPropertyPointer() {
	return &Baba::property;
}
Complement BabaText::GetPropertyBit() {
	return BABA;
}
string BabaText::ToString() {
	return "BABA";
}



RockText::RockText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {

}
int* RockText::GetPropertyPointer() {
	return &Rock::property;
}
Complement RockText::GetPropertyBit() {
	return ROCK;
}
string RockText::ToString() {
	return "ROCK";
}



WallText::WallText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {

}
int* WallText::GetPropertyPointer() {
	return &Wall::property;
}
Complement WallText::GetPropertyBit() {
	return WALL;
}
string WallText::ToString() {
	return "WALL";
}


FlagText::FlagText(int x, int y, Object* prev, Object* next) : Entity(x, y, prev, next) {

}
int* FlagText::GetPropertyPointer() {
	return &Flag::property;
}
Complement FlagText::GetPropertyBit() {
	return FLAG;
}
string FlagText::ToString() {
	return "FLAG";
}



Is::Is(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {

}
void Is::RuleCheck() {
	int x = this->GetX();
	int y = this->GetY();
	Object* L = nullptr;
	Object* R = nullptr;
	Object* T = nullptr;
	Object* B = nullptr;

	// IS object 앞부분에서 조건에 맞는 object 찾기
	Object* cursor = this->GetPrev();
	while (cursor != nullptr) {
		if (cursor->GetX() == x - 1 and cursor->GetY() == y and cursor->IsEntityText()) {
			L = cursor;
		}
		else if (cursor->GetX() == x + 1 and cursor->GetY() == y and (cursor->IsEntityText() || cursor->IsPropertyText())) {
			R = cursor;
		}
		else if (cursor->GetX() == x and cursor->GetY() == y - 1 and cursor->IsEntityText()) {
			T = cursor;
		}
		else if (cursor->GetX() == x and cursor->GetY() == y + 1 and (cursor->IsEntityText() || cursor->IsPropertyText())) {
			B = cursor;
		}
		cursor = cursor->GetPrev();
	}

	Object* cursor2 = this->GetNext();
	while (cursor2 != nullptr) {
		if (cursor2->GetX() == x - 1 and cursor2->GetY() == y and cursor2->IsEntityText()) {
			L = cursor2;
		}
		else if (cursor2->GetX() == x + 1 and cursor2->GetY() == y and (cursor2->IsEntityText() || cursor2->IsPropertyText())) {
			R = cursor2;
		}
		else if (cursor2->GetX() == x and cursor2->GetY() == y - 1 and cursor2->IsEntityText()) {
			T = cursor2;
		}
		else if (cursor2->GetX() == x and cursor2->GetY() == y + 1 and (cursor2->IsEntityText() || cursor2->IsPropertyText())) {
			B = cursor2;
		}
		cursor2 = cursor2->GetNext();
	}

	if (L != nullptr && R != nullptr) {
		*L->GetPropertyPointer() |= R->GetPropertyBit();
	}
	if (T != nullptr && B != nullptr) {
		*T->GetPropertyPointer() |= B->GetPropertyBit();
	}


}
string Is::ToString() {
	return "IS";
}


Property::Property(int x, int y, Object* prev, Object* next) : Text(x, y, prev, next) {

}
bool Property::IsPropertyText() {
	return true;
}


You::You(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {

}
Complement You::GetPropertyBit() {
	return YOU;
}
string You::ToString() {
	return "YOU";
}


Win::Win(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {

}
Complement Win::GetPropertyBit() {
	return WIN;
}
string Win::ToString() {
	return "WIN";
}



Stop::Stop(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {

}
Complement Stop::GetPropertyBit() {
	return STOP;
}
string Stop::ToString() {
	return "STOP";
}



Push::Push(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {

}
Complement Push::GetPropertyBit() {
	return PUSH;
}
string Push::ToString() {
	return "PUSH";
}


Lose::Lose(int x, int y, Object* prev, Object* next) : Property(x, y, prev, next) {

}
Complement Lose::GetPropertyBit() {
	return LOSE;
}
string Lose::ToString() {
	return "LOSE";
}

int Baba::property;
int Rock::property;
int Flag::property;
int Wall::property;