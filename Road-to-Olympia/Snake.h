#ifndef _SNAKE_H_
#define _SNAKE_H_


#include "Animal.h"
#include <vector>

class Snake : public Animal
{
private:
	COORD fpos, apos;
public:
	Snake() :Animal() {};
	Snake(COORD pos, short W, short H, string filename, bool dir, bool con, RECT bg, Color color) :Animal(pos, W, H, filename, dir, con, bg, color){};
	void Moving();
	void Draw(const short& start, const short& end) const;
	void Draw() const;
	short GetX() const;
	short GetY() const;
	bool isMoving() const;
	void SetPos(COORD);
	~Snake() {};

};

#endif // !_SNAKE_H_

