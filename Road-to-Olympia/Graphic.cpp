#include "Graphic.h"

void Graphics::SetColor(const HANDLE& hwnd, const Color& color)
{
	::SetConsoleTextAttribute(hwnd, (WORD)color);
}

void Graphics::DrawGraphics(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color)
{
	
	Graphics::SetColor(hwnd, color);

	ifstream inp(filename);

	std::string str;
	while (std::getline(inp, str))
	{
		Console_Game::GoToXY(pos);
		std::cerr << str;
		pos.Y++;
	}
	inp.close();
}

void Graphics::Draw_Text(const string& str, const COORD& COOR, const Color& color)
{
	Console_Game::GoToXY(COOR);
	SetColor(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << str;
}