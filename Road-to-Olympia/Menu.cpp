#include "Menu.h"
Console_Game console;
Menu::Menu()
{
	state_M = 1;
	state_S = 1;
	p_music = true;
	g_load = false;
	quit = false;
	p_game = false;
}

void Menu::Music() {
	if (p_music)
		PlaySound(TEXT("Music/InGame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	else
		PlaySound(NULL, 0, 0);
}
void Menu::Initialize_Title()
{
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 30,8 }, "Graphic/crosstheroad.txt", Color::red);
}

void Menu::Initialize_Menu()
{
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,24 }, "Graphic/a.txt", Color::lightred);
	Draw_Selection();
}

void Menu::Draw_Selection()
{
	if (state_M == 5)
	{
		console.Draw_Text(" ", { 114,short(25 + (state_M - 1) * 2) }, Color::red);

		console.Draw_Text("<", { 114,short(25 + state_M * 2) }, Color::red);

		console.Draw_Text(" ", { 114,short(25 + 1 * 2) }, Color::red);
	}
	else if (state_M == 1)
	{
		console.Draw_Text(" ", { 114,short(25 + (5) * 2) }, Color::red);

		console.Draw_Text("<", { 114,short(25 + state_M * 2) }, Color::red);

		console.Draw_Text(" ", { 114,short(25 + (state_M + 1) * 2) }, Color::red);
	}
	else
	{
		console.Draw_Text(" ", { 114,short(25 + (state_M - 1) * 2) }, Color::red);

		console.Draw_Text("<", { 114,short(25 + state_M * 2) }, Color::red);

		console.Draw_Text(" ", { 114,short(25 + (state_M + 1) * 2) }, Color::red);
	}
}


void Menu::choose()
{
	
}

void Menu::Draw_Setting_S()
{
	if (state_S == 1)
	{
		console.Draw_Text("<", { 100,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 100,short(10 + (state_S+1 )* 7) }, Color::red);
	}
	else if (state_S == 2)
	{
		console.Draw_Text("<", { 100,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 100,short(10 + (state_S - 1) * 7) }, Color::red);
	}

}

void Menu::Setting()
{
	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 70,5 }, "Graphic/Setting.txt", Color::white);
	Draw_Setting_S();
	char key = ' ';
	while (true)
	{
		if (_kbhit())
		{
			key = toupper(_getch());
			switch (key)
			{
			case 'W':
				state_S--;
				break;
			case 'S':
				state_S++;
				break;
			}
			if (state_S == 0)
				state_S = 2;
			else if (state_S == 3)
				state_S = 1;
			Draw_Setting_S();
		}
		if (key == char(13))
			break;
	}
	switch (state_S)
	{
	case 1:
		p_music = true;
		system("cls");
		Choose_Menu();
		break;
	case 2:
		p_music = false;
		system("cls");
		Choose_Menu();
		break;
	}
}

void Menu::About()
{
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 90,12 }, "Graphic/Infor.txt", Color::white);
	Console_Game::GoToXY({ 97,35 });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(240));
	cout << "Press ""ENTER"" to back to Menu ";
	char c = ' ';
	while (true) {
		if (_kbhit()) 
		{
			c = _getch();
		}
		if (c == 13)
			break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
	system("cls");
}

string Menu::Load()
{
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	string load_infor;
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,20 }, "Graphic/Load.txt", Color::yellow);
	Console_Game::GoToXY({ 90,23 });
	cout << "> Enter your file name: ";

	getline(cin, load_infor);
	load_file = load_infor;
	system("cls");
	return load_file;
}

void Menu::Quit()
{
	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 45,18 }, "Graphic/TksU.txt", Color::white);
}

void Menu::Choose_Menu()
{
	char key = ' ';
	Initialize_Title();
	Initialize_Menu();
	Music();
	while (true)
	{
		if (_kbhit())
		{
			key = toupper(_getch());
			switch (key)
			{
			case 'W':
				state_M--;
				break;
			case 'S':
				state_M++;
				break;
			}
			if (state_M == 0)
				state_M = 5;
			else if (state_M == 6)
				state_M = 1;
			Draw_Selection();
		}
		if (key == char(13))
			break;
		Initialize_Title();
	}
	switch (state_M)
	{
	case 1:
		p_game = true;
		PlaySound(NULL, 0, 0);
		break;
	case 2:
		g_load = true;
		PlaySound(NULL, 0, 0);
		break;
	case 3:
		Setting();
		Choose_Menu();
		break;
	case 4:
		About();
		Choose_Menu();
		break;
	case 5:
		quit = true;
		Quit();
		break;
	}
}

bool Menu::IsQuit() const 
{
	return quit;
}

bool Menu::IsPlay()const {
	return p_game;
}

bool Menu::IsLoad() {

	return g_load;
}

void Menu::setbool() {
	p_game = g_load = false;
}