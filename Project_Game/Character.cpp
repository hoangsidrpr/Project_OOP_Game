#include "Character.h"
Character::Character()
{
	color = Color::white;
	position = { 0,0 };
	width = 0, height = 0;
	dead_alive = true;
	gameboard = { 0,0,0,0 };
	memset(graphic, 0, 100 * 100 * sizeof(char));
	count = 0;
}
Character::Character(COORD pos, short w, short h, string filename, bool cond, RECT gb, Color cl)
{
	color = cl;
	position = pos;
	width = w; height = h;
	dead_alive = cond;
	gameboard = gb;
	count = 0;
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
}

void Character::Draw()
{
	Console_Game console;
	console.SetColor(GetStdHandle(STD_OUTPUT_HANDLE), color);
	COORD y = position;
	for (int i = 0; i < height; i++)
	{
		console.GoToXY({ y.X,y.Y++ });
		for (int j = 0; j < width; j++)
		{
			cout << graphic[i][j];
		}
		cout << endl;
	}
}

bool Character::operator !=(Character& human)
{
	COORD pos0 = { 0,0 };
	short h = this->height - human.height;
	short w = this->width - human.width;
	COORD pos = { this->position.X - human.position.X, this->position.Y - human.position.Y };
	if (h == 0 && w == 0 && pos.X == pos0.X && pos.Y == pos0.Y)
		return false;
	else
		return true;
}
void Character::Moveup()
{

	Console_Game console;
	console.RemoveArea(position, { short(position.X + width),short(position.Y + height-1) });
	if (position.Y != gameboard.top+1 ) // tranh bien tren
	{

		 position.Y =position.Y -height-1;
	}
	Draw();
}
void Character::Movedown()
{
	 
	Console_Game console;
	console.RemoveArea(position, { short(position.X + width),short(position.Y + height - 1) });
	if (position.Y != gameboard.bottom-2)// tranh bien duoi
	{

		position.Y = position.Y + height + 1;

	}
	Draw();
}
void Character::Moveleft()
{
	
	Console_Game console;
	console.RemoveArea(position, { short(position.X + width),short(position.Y + height - 1) });
	if (position.X >= gameboard.left + width )// tranh bien trai
	{
		position.X = position.X - width;
	}
	Draw();
}
void Character::Moveright()
{
	
	Console_Game console;
	console.RemoveArea(position, { short(position.X + width),short(position.Y + height - 1) });
	if (position.X <= gameboard.right - 2*width)// tranh bien phai
	{
		position.X = position.X + width;
	}
	Draw();
}
void Character::Moving(char key)
{
	Sound sound;
	Draw();
	switch (key)
	{
	case 'W':

		Moveup();
		sound.CharacterStep();
		break;
	case 'S':

		Movedown();
		sound.CharacterStep();
		break;
	case 'A':

		Moveleft();
		sound.CharacterStep();
		break;
	case 'D':

		Moveright();
		sound.CharacterStep();
		break;
	}

}

bool Character::Crashed_veh(vector<Vehicle*> veh)
{
	for (Vehicle*& x : veh)
	{
		if ((position.X + width - 1 >= x->GetX()) && (x->GetX() + x->GetWidth() - 1 >= position.X) &&
			(position.Y + height - 1 >= x->GetY()) && (x->GetHeight() + x->GetY() - 1 >= position.Y))
		{
			dead_alive = false;
			return true;
		}
	}
	return false;
}
bool Character::Crashed_animal(vector<Animal*> ani)
{
	for (Animal*& x : ani)
	{
		if ((position.X + width - 1 >= x->GetX()) && (x->GetX() + x->GetWidth() - 1 >= position.X) &&
			(position.Y + height - 1 >= x->GetY()) && (x->GetHeight() + x->GetY() - 1 >= position.Y))
		{
			dead_alive = false;
			return true;
		}
	}
	return false;
}
bool Character::Crashed(vector<Character> human)
{
	for (auto x : human)
	{
		if( *this != x && x.dead_alive)
		if ((position.X + width - 1 >= x.GetX()) && (x.GetX() + x.GetWidth() - 1 >= position.X) &&
			(position.Y + height - 1 >= x.GetY()) && (x.GetHeight() + x.GetY() - 1 >= position.Y))
		{
			dead_alive = false;
			return true;
		}
	}
	return false;
}


void Character::Alive()
{
	 dead_alive = true;
}
bool Character::Character_ontop()
{
	return position.Y == gameboard.top +1 ;
}



void Character::SetPos(COORD _pos)
{
	position = _pos;
}

short Character::GetX()
{
	return position.X;
}
short Character::GetY()
{
	return position.Y;
}
short Character::GetHeight()
{
	return height;
}
short Character::GetWidth()
{
	return width;
}