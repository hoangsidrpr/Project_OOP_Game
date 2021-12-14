#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_
#include "Vehicle.h"
class TrafficLight
{
private:
	COORD position;
	bool state;
	char graphic[100][100];
	short width, height,count;
	RECT GameBoard;

public:
	TrafficLight();
	TrafficLight(COORD pos, short w, short h, string filename, RECT gb, bool st);
	void Draw();
	bool GetState();
	void Run();
};

#endif // !_TRAFFIC_LIGHT_H_