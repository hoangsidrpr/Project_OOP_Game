#include "Animal.h"

Animal::Animal()
{
	inpos = position = { 0,0 };
	width = 0, height = 0;
	direction = true;
	condition = true;
	gameboard = { 0,0,0,0 };
	color = Color::white;
	memset(graphic, 0, 100 * 100 * sizeof(char));
};

Animal::Animal(COORD pos, short w, short h, string filename, bool dir, bool con, RECT bg, Color cl)
{
	color = cl;
	inpos = position = pos;
	width = w; height = h;
	direction = dir;
	condition = con;
	gameboard = bg;
	int i = 0, j = 0;
	ifstream infile;
	infile.open(filename, ios::in);
	string str;
	while (getline(infile, str))
	{
		j = 0;
		for (auto c : str)
		{
			graphic[i][j++] = c;
		}
		i++;
	}
	infile.close();
};
short Animal::GetWidth()
{
	return width;
}
short Animal::GetHeight()
{
	return height;
}

void Animal::Stop()
{
	condition = false;
}
void Animal::Set_Moving(bool con)
{
	condition = con;
}
