#include "TrafficLight.h"

TrafficLight::TrafficLight()
{
	state = true;
	width = 0;
	height = 0;
	count = 0;
	position = { 0,0 };
	GameBoard = { 0,0,0,0 };
	memset(graphic, 0, 100 * 100 * sizeof(char));
}
TrafficLight::TrafficLight(COORD pos, short w, short h, string filename, RECT gb, bool st)
{
	state = st;
	width = w;
	height = h;
	count = 0;
	position = pos;
	GameBoard = gb;
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
void TrafficLight::Draw()
{
	COORD y = position;
	Console_Game console;
	for (int i = 0; i < height; i++)
	{
		console.GoToXY({ y.X,y.Y++ });
		for (int j = 0; j < width; j++)
		{
			if (i == 1 && j == 2 && state == true)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::green);
			else if (i==3 && j==2 && state==false)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::red);
			else 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::white);
				cout << graphic[i][j];

		}
		cout << endl;
	}
}

bool TrafficLight::GetState()
{
	return state;
}
void TrafficLight::Run()
{
	static int t = 20 + rand() % 100;
	if (count == t)
	{
		state = !state;
		count = 0;
	}
	else count++;
	Draw();
}