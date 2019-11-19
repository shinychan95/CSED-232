#pragma once

#include "Enum.h"
#include <string>


using namespace std;

class Object;

class Map {
private:
	static int width, height; //���� �ʺ�� ����
	static Object* head; //������Ʈ���� �����ϴ� ��ũƮ ����Ʈ�� ����
	static Object* cursor;
	static string** map; //2���� ���� �����ϴ� 2D string
	Map();
public:
	static bool ReadMap(string str); //�����̸����κ��� �� ����
	static void PrintMap(); //���� ���� ���
	static void PrintRules(); //�����ϴ� ������� ���
	static Object* GetHead(); //head ����
	static Object* GetObjectPointer(int x, int y); // x, y ��ġ�� object�� ����Ű�� object ������ ��ȯ
	static void SetHead(Object* obj); //head ����		
	static int GetWidth(); //width ����	
	static int GetHeight(); //height ����
	static bool IsObjectNonText(Object* object); // object�� non-text���� �ƴ��� ��ȯ
	static bool RecurMove(int x, int y, Direction dir); // ��ǥ���� �Է� ���⿡ ���� ������ �� ���� object�� �ִ��� Ȯ��
	static void YouMove(Direction dir); //YOU ��ü���� dir �������� ��ĭ ������
	static bool IsInBoundary(int x, int y); //�־��� x, y ��ǥ�� ���� ������ ����� �ʴ��� üũ
	static void CheckRules(); //�����ϴ� ������� �д´�
	static bool WinCheck(); //YOU ��ü�� WIN ��ü�� ���� ĭ�� �ִ��� üũ
	static bool CantMoveCheck(); //YOU �Ӽ��� ���� ��ü�� �ִ��� üũ
	static void LoseCheck(); //YOU ��ü�� LOSE ��ü�� ���� ĭ�� ������ YOU ��ü�� ���ش�
	static void ChangeEntity(); //��ü IS ��ü ���� ó��
};

