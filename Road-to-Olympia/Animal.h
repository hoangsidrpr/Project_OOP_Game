#ifndef _ANIMAL_H_
#define _ANIMAL_H_
#pragma once
#include "Console_Game.h"

class Animal {
protected:
	COORD position,inpos;
	short width, height;
	char graphic[100][100];
	bool direction;
	bool condition;
	RECT gameboard;
	Color color;
public:
	Animal();
	Animal(COORD pos, short w, short h, string filename, bool dir, bool con, RECT bg, Color cl);

	virtual void Draw() const= 0;
	virtual void Moving() = 0;
	virtual bool isMoving()const = 0;
	virtual short GetX() const = 0;
	virtual short GetY() const = 0;
	virtual void SetPos(COORD)=0 ;
	void Stop();
	void Set_Moving(bool);
	short GetWidth();
	short GetHeight();
	~Animal() {};
};

#endif // !_ANIMAL_H_

