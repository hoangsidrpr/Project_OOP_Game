#include "Dog.h"
void Dog::Draw() const
{
	Console_Game console;
	console.SetColor(GetStdHandle(STD_OUTPUT_HANDLE), color);
	COORD y = position;
	for (int i = 0; i < height; i++)
	{
		if (y.X > gameboard.left + 2)
			console.GoToXY({ y.X, y.Y++ });
		else
			console.GoToXY({ short(gameboard.left + 2), y.Y++ });

		for (int j = 0; j < width; j++)
		{
			if (y.X > gameboard.left + 2)
			{
				if (y.X + width > gameboard.right - 3)
				{
					if (j < gameboard.right - y.X - 3)// vao bien phai
					{
						cout << graphic[i][j];
					}
				}
				else
				{
					cout << graphic[i][j];
				}
			}
			else
			{
				if (j > gameboard.left - y.X - 1) // di tu bien trai ra
					cout << graphic[i][j];
			}
		}
	}
}
void Dog::Moving()
{
	Console_Game console;
	if (condition != true) condition = true;
	if (direction == true) // phai sang trai
	{
		if (position.X + width <= gameboard.left + 3)// cham bien trai
		{
			condition = false;
			position = inpos;
		}
		else
		{
			console.RemoveArea({ short(position.X + width - 2),short(position.Y + height - 1) },{ short(position.X + width - 2),short(position.Y + height - 1)});
			if (position.X + width == gameboard.right + 2)
			{
				position.X = position.X - 3;
			}
			--position.X;
		}
	}
	else// trai sang phai
	{
		if (position.X > gameboard.right - 4)// cham bien phai
		{
			condition = false;
			position = inpos;
		}
		else
		{
			if (position.X == gameboard.left)
				position.X = position.X + 2;
			console.RemoveArea(position, { short(position.X),short(position.Y + height - 1) });
			++position.X;
		}
	}
	Draw();
}


bool Dog::isMoving() const
{
	return condition;
}

short Dog::GetX() const
{
	return position.X;
}
short Dog::GetY() const
{
	return position.Y;
}

void Dog::SetPos(COORD pos)
{
	inpos = pos;
}