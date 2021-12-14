#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#pragma once
#include "Console_Game.h"

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

