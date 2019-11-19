#pragma once

#include "Object.h"
#include <string>
#include <iostream>

using namespace std;


Object::Object(int x, int y, Object* prev, Object* next) { //�����ڴ� x, y��ǥ�� ���� ���� ���� ��带 �޴´�. �ڽ� Ŭ�����鵵 ��������
	this->x = x;
	this->y = y;
	this->prev = prev;
	this->next = next;
};
void Object::Remove() { //������Ʈ�� ���ŵ�
	Object* _prev = prev;
	Object* _next = next;

	if (next != nullptr) {
		next->SetPrev(_prev);
	}
	if (prev != nullptr) {
		prev->SetNext(_next);
	}
};
void Object::SetX(int x) { //x��ǥ ����
	this->x = x;
};
void Object::SetY(int y) { //y��ǥ ����
	this->y = y;
};
int Object::GetX() { //x��ǥ ���� 
	return x;
};
int Object::GetY() { //y��ǥ ����
	return y;
};
Object* Object::GetNext() { //���� ��� ����
	return next;
};
Object* Object::GetPrev() { //���� ��� ����
	return prev;
};
void Object::SetNext(Object* next) { //���� ��� ����
	this->next = next;
};
void Object::SetPrev(Object* prev) { //���� ��� ����
	this->prev = prev;
};
bool Object::Move(Direction dir) { //������Ʈ�� �� ĭ dir �������� (�̵��� �� �ִٸ�) �̵�
	MoveXY(x, y, dir);
	return true;
};
void Object::RuleCheck() { //���� ������ �о� �� ��ü�� �Ӽ��� �ο��Ѵ�. [Is Ŭ�������� ó���ϴ� ���� ����]

};
bool Object::IsEntityText() { //Entity Ŭ������ �� Ŭ������ �ڽ��̶�� true�� ����
	return false;
};
bool Object::IsPropertyText() { //Property Ŭ������ �� Ŭ������ �ڽ��̶�� true�� ����
	return false;
};
Complement Object::GetPropertyBit() { //Text�� ���� ����ϰ� �ִ� Entity�� Property�� ���� (Complement Enum)
	return null;
};
int* Object::GetPropertyPointer() { //Non-Text�� Ŭ������ �ִ� property ������ ����Ű�� ������
	return nullptr;
};
int Object::GetProperty() { //Non-Text�� Ŭ������ �ִ� property ���� ����
	return 0;
};
void Object::YouMove(Direction dir) { //Non-Text���� YOU �Ӽ��� ������ �ִٸ� dir �������� �̵� [���� üũ �� Object::Move�� ȣ���ϴ� ���� ����]
};
void Object::ChangeEntity() { //Non-Text���� ���� property ������ ���� �ٸ� ��ü�� �ٲ��� �Ѵٸ� �ٲٴ� �۾��� ����

};
string Object::ToString() { //������Ʈ�� ������ ���� �� �� ��µǴ� string�� �ٸ���
	return "";
};




Baba::Baba(int x, int y, Object* prev, Object* next) : Object(x, y, prev, next) {
};
void Baba::InitRule() { //�ʿ��� ������ �б� ���� ��� ������Ʈ�� �Ӽ��� �ʱ�ȭ �ؾ��Ѵ�.
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

	// IS object �պκп��� ���ǿ� �´� object ã��
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