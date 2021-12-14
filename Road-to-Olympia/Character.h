#ifndef _CHARACTER_H_
#define _CHARACTER_H_


#include "Console_Game.h"
#include "Truck.h"
#include "Sound.h"
#include "Car.h"
#include <thread>
#include "Snake.h"
#include "Dog.h"

class Character
{
private:
	COORD position;
	short width, height;
	char graphic[100][100];
	bool dead_alive;
	int count;
	Color color;
	RECT gameboard;
public:
	Character();
	Character(COORD pos, short w, short h, string filename, bool cond, RECT gb, Color cl);
	void Draw();
	void Moveup();
	void Movedown();
	void Moveleft();
	void Moveright();

	void Moving(char key);
	bool Character_ontop();
	bool Crashed_veh(vector<Vehicle*>);
	bool Crashed_animal(vector<Animal*>);
	bool Crashed(vector <Character>);

	bool Dead();
	void Alive();

	short GetX();
	short GetY();
	short GetHeight();
	short GetWidth();

	bool operator !=(Character&);
	void SetPos(COORD );
	~Character() {};

};

#endif // !_CHARACTER_H_


