#ifndef _CONSOLE_GAME_H
#define _CONSOLE_GAME_H

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <fstream>
#include <conio.h>
using namespace std;

#pragma comment(lib, "winmm.lib")
#pragma execution_character_set("utf-8")

enum class Color
{
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray,
	lightblue,
	lightgreen,
	lightaqua,
	lightred,
	lightpurple,
	lightyellow,
	brightwhite
};

class Console_Game{
public:

	static void GoToXY(COORD);
	void SetConsoleColor(short,short);
	short GetColor(short,short);
	void QuickEdit(bool ); //set nen trang
	void DisableCusor(bool);
	void FixConsoleWindow();
	static void RemoveArea(COORD,COORD);
	void SetSize(short, short);
	void SetCursor(bool);
	void SetBufferSize();
	void SetColor(const HANDLE&, const Color&);
	void DrawGraphics(const HANDLE&, COORD, const std::string&, const Color&);
	void Draw_Text(const string& str, const COORD& COOR, const Color& Color);
};



#endif // !_CONSOLE_GAME_H

