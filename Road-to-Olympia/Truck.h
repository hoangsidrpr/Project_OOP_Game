#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "Vehicle.h"
#include <vector>

class Truck : public Vehicle
{
private:
	COORD fpos, apos;
public:
	Truck() :Vehicle() {};
	Truck(COORD pos, short W, short H, string filename, bool dir, bool con, RECT bg, Color color) :Vehicle(pos, W, H, filename, dir, con, bg, color) {};
	void Moving();
	void Draw(const short& start, const short& end) const;
	void Draw() const;

	short GetX() const;
	short GetY() const;
	bool isMoving() const;

	void SetPos(COORD);
	~Truck() {};
};

#endif // !_TRUCK_H_

