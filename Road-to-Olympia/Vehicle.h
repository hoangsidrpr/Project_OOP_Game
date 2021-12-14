#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <random>
#include <algorithm>
#include <vector>
#include "Graphic.h"
#include "Console_Game.h"
using namespace std;
#pragma execution_character_set("utf-8")

class Vehicle {
protected:
	COORD position,inpos;
	short width, height;
	char graphic[100][100]; // arr 2d
	bool direction;
	bool condition;
	RECT gameboard;
	Color color;
public:
	Vehicle();
	
	Vehicle(COORD pos, short w, short h, string filename, bool dir, bool con, RECT bg, Color cl);

	virtual void Draw() const= 0;
	virtual void Moving() = 0;
	virtual bool isMoving() const = 0;
	virtual short GetX() const = 0;
	virtual short GetY() const = 0;
	virtual void SetPos(COORD) = 0;
	void Stop();
	void Set_Moving(bool);
	short GetWidth();
	short GetHeight();
	~Vehicle() {};
};

#endif // !_VEHICLE_H_

