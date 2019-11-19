#pragma once

#include "Map.h"
#include "Object.h"
#include <string>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

class Object;

enum ObjectStr {
	B, // BabaText
	R, // RockText
	W, // WallText
	F, // FlagText
	b, // baba
	r, // rock
	w, // wall
	f, // flag
	I, // Is
	Y, // You
	P, // Push
	S, // Stop
	G, // Win
	L, // Lose
	Z  // Space
};

ObjectStr objectEncode(char str) {
	if (str == 'B') return B;
	if (str == 'R') return R;
	if (str == 'W') return W;
	if (str == 'F') return F;
	if (str == 'b') return b;
	if (str == 'r') return r;
	if (str == 'w') return w;
	if (str == 'f') return f;
	if (str == 'I') return I;
	if (str == 'Y') return Y;
	if (str == 'P') return P;
	if (str == 'S') return S;
	if (str == 'G') return G;
	if (str == 'L') return L;
	if (str == ' ') return Z;
};

bool Map::ReadMap(string str) { //파일이름으로부터 맵 생성

	ifstream inFile;

	inFile.open("./data/" + str);

	if (!inFile) {
		cout << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	string line;
	string all_line = "";
	int x = 0;
	int y = 0;
	Object* prev = nullptr;
	while (getline(inFile, line)) {
		x = 0;
		all_line += line;
		for (x; x < line.length(); x++) {
			switch (objectEncode(line[x]))
			{
			case B:
				cursor = new BabaText(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case R:
				cursor = new RockText(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case W:
				cursor = new WallText(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case F:
				cursor = new FlagText(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case b:
				cursor = new Baba(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case r:
				cursor = new Rock(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case w:
				cursor = new Wall(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case f:
				cursor = new Flag(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case I:
				cursor = new Is(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case Y:
				cursor = new You(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case P:
				cursor = new Push(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case S:
				cursor = new Stop(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case G:
				cursor = new Win(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			case L:
				cursor = new Lose(x, y, prev, nullptr);
				prev = cursor;
				cursor = cursor->GetNext();
				break;
			}
		}
		y++;
	}


	while (prev != nullptr) {	// prev가 마지막 object를 가리킨다.
		prev->SetNext(cursor);	// 마지막 object next에 nullptr이 들어간다
		cursor = prev;
		prev = prev->GetPrev();
	}
	head = cursor;

	width = x;
	height = y;

	map = new string * [height];
	for (int i = 0; i < height; i++) {
		map[i] = new string[width];
	}


	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) 
				map[i][j] = "";

	cursor = head;
	while (cursor != nullptr){
		map[cursor->GetY()][cursor->GetX()] = cursor->ToString();
		cursor = cursor->GetNext();
	}


	inFile.close();

};

void Map::PrintMap() { //현재 맵을 출력
	system("cls");
	// 격자무늬 출력
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
			cout << "+--";
		cout << "+" << endl;
		for (int x = 0; x < width; x++)
			cout << "|  ";
		cout << "|" << endl;
		for (int x = 0; x < width; x++)
			cout << "|  ";
		cout << "|" << endl;
	}
	for (int x = 0; x < width; x++)
		cout << "+--";
	cout << "+" << endl;

	// 객체 위치 및 string 길이에 따라 출력

	cursor = head;
	while (cursor != nullptr) {
		if (cursor->ToString().length() == 4) {
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 1);
			cout << cursor->ToString()[0] << cursor->ToString()[1];
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 2);
			cout << cursor->ToString()[2] << cursor->ToString()[3];
		}
		else if (cursor->ToString().length() == 3) {
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 1);
			cout << cursor->ToString()[0] << cursor->ToString()[1];
			gotoxy(cursor->GetX() * 3 + 2, cursor->GetY() * 3 + 2);
			cout << cursor->ToString()[2];
		}
		else if (cursor->ToString().length() == 2) {
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 1);
			cout << cursor->ToString()[0];
			gotoxy(cursor->GetX() * 3 + 2, cursor->GetY() * 3 + 2);
			cout << cursor->ToString()[1];;
		}
		else if (cursor->ToString() == "b") {
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 1);
			cout << cursor->ToString()[0];
		}
		else if (cursor->ToString() == "w") {
			gotoxy(cursor->GetX() * 3 + 1, cursor->GetY() * 3 + 2);
			cout << cursor->ToString()[0];
		}
		else if (cursor->ToString() == "r") {
			gotoxy(cursor->GetX() * 3 + 2, cursor->GetY() * 3 + 1);
			cout << cursor->ToString()[0];
		}
		else if (cursor->ToString() == "f") {
			gotoxy(cursor->GetX() * 3 + 2, cursor->GetY() * 3 + 2);
			cout << cursor->ToString()[0];
		}
		cursor = cursor->GetNext();
	}
	gotoxy(0, height * 3 + 1);


};
void Map::PrintRules() { //존재하는 문장들을 출력
	string NonTextInclude = "";
	cursor = head;
	while (cursor != nullptr) {
		if (IsObjectNonText(cursor) and (NonTextInclude.find(cursor->ToString()) == string::npos)) {
			if (cursor->GetProperty() != null) {
				int integer = cursor->GetProperty();
				string complement = "";
				if (integer & YOU)
					complement += "YOU ";
				if (integer & WIN)
					complement += "WIN ";
				if (integer & STOP) 
					complement += "STOP";
				if (integer & PUSH) 
					complement += "PUSH"; 
				if (integer & BABA) 
					complement += "BABA"; 
				if (integer & ROCK) 
					complement += "ROCK";
				if (integer & WALL) 
					complement += "WALL"; 
				if (integer & FLAG) 
					complement += "FLAG"; 
				if (integer & LOSE) 
					complement += "LOSE"; 

				if (cursor->ToString() == "b")
					for (int i = 0; i < complement.length() / 4; i++) 
						cout << "BABA IS " << complement.substr(4 * i, 4) << endl;
				if (cursor->ToString() == "r")
					for (int i = 0; i < complement.length() / 4; i++)
						cout << "ROCK IS " << complement.substr(4 * i, 4) << endl;
				if (cursor->ToString() == "w")
					for (int i = 0; i < complement.length() / 4; i++)
						cout << "WALL IS " << complement.substr(4 * i, 4) << endl;
				if (cursor->ToString() == "f")
					for (int i = 0; i < complement.length() / 4; i++)
						cout << "FLAG IS " << complement.substr(4 * i, 4) << endl;
				
				NonTextInclude += cursor->ToString();
			}
		}
		cursor = cursor->GetNext();
	}
	
};
Object* Map::GetHead() { //head 리턴
	return head;
};

Object* Map::GetObjectPointer(int x, int y) {
	Object* pointer = head;
	Object* tmp = nullptr;
	while (pointer != nullptr) {
		if (pointer->GetX() == x and pointer->GetY() == y) {
			tmp = pointer;
			if (!IsObjectNonText(pointer) or pointer->GetProperty() & PUSH)
				return pointer;
		}
		pointer = pointer->GetNext();
	}
	return tmp;
}
void Map::SetHead(Object* obj) { //head 설정
	head = obj;
};
int Map::GetWidth() { //width 리턴
	return width;
};
int Map::GetHeight() { //height 리턴
	return height;
};

bool Map::IsObjectNonText(Object* object) {
	string name = object->ToString();
	if ((name == "b" or name == "r" or name == "w" or name == "f"))
		return true;
	return false;
}

bool Map::RecurMove(int x, int y, Direction dir) {
	Object* tmp = GetObjectPointer(x, y);
	Object* tmp2 = nullptr;
	switch (dir)
	{
	case UP:
		if (!IsInBoundary(x, y - 1))
			break;
		if (map[y - 1][x] == "") {
			tmp->Move(dir);
			map[y - 1][x] += tmp->ToString();
			map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
			return true;
		}
		else {
			tmp2 = GetObjectPointer(x, y - 1);
			if (IsObjectNonText(tmp2) and !(tmp2->GetProperty() & STOP) and !(tmp2->GetProperty() & PUSH)) {
				tmp->Move(dir);
				map[y - 1][x] += tmp->ToString();
				map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
				return true;
			}
			else if (IsObjectNonText(tmp2) and (tmp2->GetProperty() & STOP))
				break;
			else {
				if (RecurMove(x, y - 1, dir)) {
					tmp->Move(dir);
					map[y - 1][x] += tmp->ToString();
					map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
					return true;
				}
				break;
			}
		}
		break;
	case DOWN:
		if (!IsInBoundary(x, y + 1))
			break;
		if (map[y + 1][x] == "") {
			tmp->Move(dir);
			map[y + 1][x] += tmp->ToString();
			map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
			return true;
		}
		else {
			tmp2 = GetObjectPointer(x, y + 1);
			if (IsObjectNonText(tmp2) and !(tmp2->GetProperty() & STOP) and !(tmp2->GetProperty() & PUSH)) {
				tmp->Move(dir);
				map[y + 1][x] += tmp->ToString();
				map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
				return true;
			}
			else if (IsObjectNonText(tmp2) and (tmp2->GetProperty() & STOP))
				break;
			else {
				if (RecurMove(x, y + 1, dir)) {
					tmp->Move(dir);
					map[y + 1][x] += tmp->ToString();
					map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
					return true;
				}

				break;
			}
		}
		break;
	case LEFT:
		if (!IsInBoundary(x - 1, y))
			break;
		if (map[y][x - 1] == "") {
			tmp->Move(dir);
			map[y][x - 1] += tmp->ToString();
			map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
			return true;
		}
		else {
			tmp2 = GetObjectPointer(x - 1, y);
			if (IsObjectNonText(tmp2) and !(tmp2->GetProperty() & STOP) and !(tmp2->GetProperty() & PUSH)) {
				tmp->Move(dir);
				map[y][x - 1] += tmp->ToString();
				map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
				return true;
			}
			else if (IsObjectNonText(tmp2) and (tmp2->GetProperty() & STOP))
				break;
			else {
				if (RecurMove(x - 1, y, dir)) {
					tmp->Move(dir);
					map[y][x - 1] += tmp->ToString();
					map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
					return true;
				}
				break;
			}
		}
		break;
	case RIGHT:
		if (!IsInBoundary(x + 1, y))
			break;
		if (map[y][x + 1] == "") {
			tmp->Move(dir);
			map[y][x + 1] += tmp->ToString();
			map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
			return true;
		}
		else {
			tmp2 = GetObjectPointer(x + 1, y);
			if (IsObjectNonText(tmp2) and !(tmp2->GetProperty() & STOP) and !(tmp2->GetProperty() & PUSH)) {
				tmp->Move(dir);
				map[y][x + 1] += tmp->ToString();
				map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
				return true;
			}
			else if (IsObjectNonText(tmp2) and (tmp2->GetProperty() & STOP))
				break;
			else {
				if (RecurMove(x + 1, y, dir)) {
					tmp->Move(dir);
					map[y][x + 1] += tmp->ToString();
					map[y][x].erase(map[y][x].find(tmp->ToString()), tmp->ToString().length());
					return true;
				}
				break;
			}
		}
		break;
	default:
		break;
	}

	return false;
}

void Map::YouMove(Direction dir) { //YOU 개체들을 dir 방향으로 한칸 움직임
	int x, y;
	cursor = head;
	Object* tmp = nullptr;
	while (cursor != nullptr) {
		if (cursor->GetProperty() & YOU) {
			x = cursor->GetX();
			y = cursor->GetY();
			switch (dir)
			{
			case UP:
				if (!IsInBoundary(x, y - 1))
					break;
				if (map[y - 1][x] == "") {
					cursor->YouMove(dir);
					map[y - 1][x] += cursor->ToString();
					map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
					break;
				}
				else {
					tmp = GetObjectPointer(x, y - 1);
					if (IsObjectNonText(tmp) and !(tmp->GetProperty() & STOP) and !(tmp->GetProperty() & PUSH)) {
						cursor->YouMove(dir);
						map[y - 1][x] += cursor->ToString();
						map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
						break;
					}
					else if (IsObjectNonText(tmp) and (tmp->GetProperty() & STOP))
						break;
					else {
						if (RecurMove(x, y - 1, dir)) {
							cursor->YouMove(dir);
							map[y - 1][x] += cursor->ToString();
							map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length());
							break;
						}
					}
				}
				break;
			case DOWN:
				if (!IsInBoundary(x, y + 1))
					break;
				if (map[y + 1][x] == "") {
					cursor->YouMove(dir);
					map[y + 1][x] += cursor->ToString();
					map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
					break;
				}
				else {
					tmp = GetObjectPointer(x, y + 1);
					if (IsObjectNonText(tmp) and !(tmp->GetProperty() & STOP) and !(tmp->GetProperty() & PUSH)) {
						cursor->YouMove(dir);
						map[y + 1][x] += cursor->ToString();
						map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
						break;
					}
					else if (IsObjectNonText(tmp) and (tmp->GetProperty() & STOP))
						break;
					else {
						if (RecurMove(x, y + 1, dir)) {
							cursor->YouMove(dir);
							map[y + 1][x] += cursor->ToString();
							map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length());
						}
						break;
					}
				}
				break;
			case LEFT:
				if (!IsInBoundary(x - 1, y))
					break;
				if (map[y][x - 1] == "") {
					cursor->YouMove(dir);
					map[y][x - 1] += cursor->ToString();
					map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
					break;
				}
				else {
					tmp = GetObjectPointer(x - 1, y);
					if (IsObjectNonText(tmp) and !(tmp->GetProperty() & STOP) and !(tmp->GetProperty() & PUSH)) {
						cursor->YouMove(dir);
						map[y][x - 1] += cursor->ToString();
						map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
						break;
					}
					else if (IsObjectNonText(tmp) and (tmp->GetProperty() & STOP))
						break;
					else {
						if (RecurMove(x - 1, y, dir)) {
							cursor->YouMove(dir);
							map[y][x - 1] += cursor->ToString();
							map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length());;
						}
						break;
					}
				}
				break;
			case RIGHT:
				if (!IsInBoundary(x + 1, y))
					break;
				if (map[y][x + 1] == "") {
					cursor->YouMove(dir);
					map[y][x + 1] += cursor->ToString();
					map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
					break;
				}
				else {
					tmp = GetObjectPointer(x + 1, y);
					if (IsObjectNonText(tmp) and !(tmp->GetProperty() & STOP) and !(tmp->GetProperty() & PUSH)) {
						cursor->YouMove(dir);
						map[y][x + 1] += cursor->ToString();
						map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length()); 
						break;
					}
					else if (IsObjectNonText(tmp) and (tmp->GetProperty() & STOP))
						break;
					else {
						if (RecurMove(x + 1, y, dir)) {
							cursor->YouMove(dir);
							map[y][x + 1] += cursor->ToString();
							map[y][x].erase(map[y][x].find(cursor->ToString()), cursor->ToString().length());
						}
						break;
					}
				}
				break;
			default:
				break;
			}
		}


		cursor = cursor->GetNext();
	}

};
bool Map::IsInBoundary(int x, int y) { //주어진 x, y 좌표가 맵의 범위를 벗어나지 않는지 체크
	if (x < 0 or y < 0 or x >= width or y >= height)
		return false;
	return true;
};
void Map::CheckRules() { //존재하는 문장들을 읽는다
	Baba::InitRule();
	Rock::InitRule();
	Wall::InitRule();
	Flag::InitRule();

	cursor = head;
	while (cursor != nullptr) {
		if (cursor->ToString() == "IS") {
			cursor->RuleCheck();
		}
		cursor = cursor->GetNext();
	}
};
bool Map::WinCheck() { //YOU 개체가 WIN 개체와 같은 칸에 있는지 체크
	cursor = head;
	while (cursor != nullptr) {
		if (IsObjectNonText(cursor) and (cursor->GetProperty() & YOU)) {
			Object* _cursor = head;
			while (_cursor != nullptr) {
				if (IsObjectNonText(_cursor) and _cursor->GetProperty() & WIN) {
					if (cursor->GetX() == _cursor->GetX() and cursor->GetY() == _cursor->GetY())
						return true;
				}
				_cursor = _cursor->GetNext();
			}
		}
		cursor = cursor->GetNext();
	}

	return false;
};
bool Map::CantMoveCheck() { //YOU 속성을 가진 개체가 있는지 체크
	
	cursor = head;
	while (cursor != nullptr) {
		if (IsObjectNonText(cursor))
			if (cursor->GetProperty() & YOU) 
				return false;	
		cursor = cursor->GetNext();
	}

	return true;
};
void Map::LoseCheck() { //YOU 개체가 LOSE 개체와 같은 칸에 있으면 YOU 개체를 없앤다
	cursor = head;
	Object* _cursor = head;
	while (cursor != nullptr) {
		if (cursor->GetProperty() & YOU && IsObjectNonText(cursor)) {
			while (_cursor != nullptr) {
				if (_cursor != cursor && _cursor->GetProperty() & LOSE && IsObjectNonText(_cursor)) {
					if (cursor->GetX() == _cursor->GetX() && cursor->GetY() == _cursor->GetY()) {
						Object* tmp = cursor;
						if (head == tmp) {
							head = cursor->GetNext();
						}
						cursor = cursor->GetNext();
						tmp->Remove();
						delete tmp;
					}
				}
				_cursor = _cursor->GetNext();
			}
		}
		cursor = cursor->GetNext();
	}
};
void Map::ChangeEntity() { //개체 IS 개체 문장 처리
	cursor = head;
	while (cursor != nullptr) {
		if (IsObjectNonText(cursor)) {
			int Property = cursor->GetProperty();
			if (Property & BABA || Property & ROCK || Property & WALL || Property & FLAG) {
				cursor->ChangeEntity();
				if (cursor == head) { // head가 가리키는 object의 prev는 nullptr이므로
					head = cursor->GetNext()->GetPrev();
				}	
			}
			
		}
		cursor = cursor->GetNext(); 
	}
};



int Map::width = 0;
int Map::height = 0;
Object* Map::head;
Object* Map::cursor;
string** Map::map;
