#include "Console_Game.h"


//screen: goto [x,y]
void Console_Game::GoToXY(COORD Pos)	
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//DEFAULT WINDOW
void Console_Game::FixConsoleWindow()
{
HWND consoleWindow = GetConsoleWindow();

LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console_Game::DisableCusor(bool flag) // DELETE CUSOR
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(out, &cursorInfo);

}
void Console_Game::SetSize(short width, short height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, FALSE);
}

void Console_Game::SetCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); 

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Console_Game::SetBufferSize() 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);


	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;


	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	int Status = SetConsoleScreenBufferSize(hOut, newSize);
	if (Status == 0)
	{
		std::cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
		exit(Status);
	}

	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
	std::cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
}

short Console_Game::GetColor(short BGcolor, short TxtColor)
{
	return BGcolor * 15 + BGcolor + TxtColor;
}

void Console_Game::SetConsoleColor(short BGcolor, short Txtcolor) {
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;

	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);

	cbi.wAttributes = WORD(GetColor(BGcolor, Txtcolor));
	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);
}

void Console_Game::SetColor(const HANDLE& hwnd, const Color& color)
{
	::SetConsoleTextAttribute(hwnd, (WORD)color);
}

void Console_Game::DrawGraphics(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color)
{

	Console_Game::SetColor(hwnd, color);

	ifstream inp(filename);
	string str;
	while (std::getline(inp, str))
	{
		Console_Game::GoToXY(pos);
		cout << str;
		pos.Y++;
	}
	inp.close();
}

void Console_Game::Draw_Text(const string& str, const COORD& COOR, const Color& color)
{
	Console_Game::GoToXY(COOR);
	SetColor(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << str;
}

void Console_Game::QuickEdit(bool flag)
{
	DWORD prev_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (!flag) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

 void Console_Game::RemoveArea(COORD start, COORD end)
{
	for (short i = start.X; i <= end.X; ++i)
	{
		for (short j = start.Y; j <= end.Y; j++)
		{
			GoToXY({ i,j });
			cout << " ";
		}
		cout << endl;
	}
}