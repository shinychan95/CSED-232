#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "Enum.h"
#include "Object.h"
#include "Map.h"

using namespace std;

Direction KeyInput()
{
	int key;
	key = _getch();
	switch (key)
	{
	case 'w':
		return UP;
	case 'a':
		return LEFT;
	case 'd':
		return RIGHT;
	case 's':
		return DOWN;
	case 'r':
		return RESTART;
	case 'e':
		return EXIT;
	}
}

int main()
{
	string filename;

	while (true) {
		cout << "Read Stage File: ";
		cin >> filename;
		if (!Map::ReadMap(filename)) continue; //������ �� �о����� �ٽ� �Է��ϰ� �Ѵ�.
		Map::PrintMap();
		cout << filename << " Load Complete. Press Any Key to Continue...";
		KeyInput();
		while (true) {
			Map::CheckRules();
			Map::ChangeEntity();
			Map::LoseCheck();
			Map::PrintMap();
			Map::PrintRules();
			if (Map::CantMoveCheck()) { //YOU ��ü�� ���� �� �й�
				cout << "YOU does not exist. You Lose" << endl;
				break;
			}
			if (Map::WinCheck()) { //�¸� ���� ������ �¸�
				cout << "YOU WIN!" << endl;
				break;
			}
			cout << "Key Input: w=up, s=down, a=left, d=right, r=restart, e=exit" << endl;
			Direction dir = KeyInput(); //Ű �Է��� �޴´�.
			if (dir == RESTART) {
				Map::ReadMap(filename);
			}
			if (dir == EXIT) {
				system("cls");
				break;
			}
			Map::YouMove(dir);
		}
	}

	return 0;
}