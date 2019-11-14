#pragma once

#include "Enum.h"
#include <string>

using namespace std;

class Object {
private:
	int x, y; //x, y ��ǥ
	Object* prev, * next; //���� ���� ���� ���
public:
	Object(int x, int y, Object* prev = nullptr, Object* next = nullptr); //�����ڴ� x, y��ǥ�� ���� ���� ���� ��带 �޴´�. �ڽ� Ŭ�����鵵 ��������
	void Remove(); //������Ʈ�� ���ŵ�
	void SetX(int x); //x��ǥ ����
	void SetY(int y); //y��ǥ ����
	int GetX(); //x��ǥ ����
	int GetY(); //y��ǥ ����
	Object* GetNext(); //���� ��� ����
	Object* GetPrev(); //���� ��� ����
	void SetNext(Object* obj); //���� ��� ����
	void SetPrev(Object* obj); //���� ��� ����
	virtual bool Move(Direction dir); //������Ʈ�� �� ĭ dir �������� (�̵��� �� �ִٸ�) �̵�
	virtual void RuleCheck(); //���� ������ �о� �� ��ü�� �Ӽ��� �ο��Ѵ�. [Is Ŭ�������� ó���ϴ� ���� ����]
	virtual bool IsEntityText(); //Entity Ŭ������ �� Ŭ������ �ڽ��̶�� true�� ����
	virtual bool IsPropertyText(); //Property Ŭ������ �� Ŭ������ �ڽ��̶�� true�� ����
	virtual Complement GetPropertyBit(); //Text�� ���� ����ϰ� �ִ� Entity�� Property�� ���� (Complement Enum)
	virtual int* GetPropertyPointer(); //Non-Text�� Ŭ������ �ִ� property ������ ����Ű�� ������
	virtual int GetProperty(); //Non-Text�� Ŭ������ �ִ� property ���� ����
	virtual void YouMove(Direction dir); //Non-Text���� YOU �Ӽ��� ������ �ִٸ� dir �������� �̵� [���� üũ �� Object::Move�� ȣ���ϴ� ���� ����]
	virtual void ChangeEntity(); //Non-Text���� ���� property ������ ���� �ٸ� ��ü�� �ٲ��� �Ѵٸ� �ٲٴ� �۾��� ����
	virtual string ToString(); //������Ʈ�� ������ ���� �� �� ��µǴ� string�� �ٸ���
};

class Baba : public Object {
private:
public:
	static int property;
	Baba(int x, int y, Object* prev, Object* next);
	static void InitRule() { //�ʿ��� ������ �б� ���� ��� ������Ʈ�� �Ӽ��� �ʱ�ȭ �ؾ��Ѵ�.
		property = NULL;
	}
	string ToString();
	int GetProperty();
	void YouMove(Direction dir);
	bool Move(Direction dir);
	void ChangeEntity();
};

class Rock : public Object {
private:
public:
	static int property;
	Rock(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString();
	int GetProperty();
	void YouMove(Direction dir);
	bool Move(Direction dir);
	void ChangeEntity();
};

class Wall : public Object {
private:
public:
	static int property;
	Wall(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString();
	int GetProperty();
	void YouMove(Direction dir);
	bool Move(Direction dir);
	void ChangeEntity();
};

class Flag : public Object {
private:
public:
	static int property;
	Flag(int x, int y, Object* prev, Object* next);
	static void InitRule() {
		property = NULL;
	}
	string ToString();
	int GetProperty();
	void YouMove(Direction dir);
	bool Move(Direction dir);
	void ChangeEntity();
};

class Text : public Object {
public:
	Text(int x, int y, Object* prev, Object* next);
	bool Move(Direction dir);
};

class Entity : public Text {
public:
	Entity(int x, int y, Object* prev, Object* next);
	bool IsEntityText();
};

class BabaText : public Entity {
public:
	BabaText(int x, int y, Object* prev, Object* next);
	int* GetPropertyPointer();
	Complement GetPropertyBit();
	string ToString();
};

class RockText : public Entity {
public:
	RockText(int x, int y, Object* prev, Object* next);
	int* GetPropertyPointer();
	Complement GetPropertyBit();
	string ToString();
};

class WallText : public Entity {
public:
	WallText(int x, int y, Object* prev, Object* next);
	int* GetPropertyPointer();
	Complement GetPropertyBit();
	string ToString();
};

class FlagText : public Entity {
public:
	FlagText(int x, int y, Object* prev, Object* next);
	int* GetPropertyPointer();
	Complement GetPropertyBit();
	string ToString();
};

class Is : public Text {
public:
	Is(int x, int y, Object* prev, Object* next);
	void RuleCheck();
	string ToString();
};

class Property : public Text {
public:
	Property(int x, int y, Object* prev, Object* next);
	bool IsPropertyText();
};

class You : public Property {
public:
	You(int x, int y, Object* prev, Object* next);
	Complement GetPropertyBit();
	string ToString();
};

class Win : public Property {
public:
	Win(int x, int y, Object* prev, Object* next);
	Complement GetPropertyBit();
	string ToString();
};

class Stop : public Property {
public:
	Stop(int x, int y, Object* prev, Object* next);
	Complement GetPropertyBit();
	string ToString();
};

class Push : public Property {
public:
	Push(int x, int y, Object* prev, Object* next);
	Complement GetPropertyBit();
	string ToString();
};

class Lose : public Property {
public:
	Lose(int x, int y, Object* prev, Object* next);
	Complement GetPropertyBit();
	string ToString();
};