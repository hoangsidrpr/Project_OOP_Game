#ifndef _CAR_H_
#define _CAR_H_


#include "Vehicle.h"
#include <vector>
#include <random>

class Car : public Vehicle
{
private:
	COORD fpos, apos;
public:
	Car(COORD pos, short W, short H, string filename, bool dir, bool con, RECT bg, Color color) :Vehicle(pos, W, H, filename, dir, con, bg, color){};
	void Moving();
	void Draw() const;

	short GetX() const;
	short GetY() const;
	bool isMoving() const;

	void SetPos(COORD);
	~Car() {};
};

#endif // !_CAR_H_

