#include "Menu_Button.h"

Menu_Button::Menu_Button() {
	pos = { 0,0 };
	str = " ";
	Color = 0;
}

Menu_Button::Menu_Button(const COORD& pos_, const string& str_, const int& Color_) {
	pos = pos_;
	str = str_;
	Color = Color_;
}

//void Menu_Button::DRAW() {
//	Graphics::DrawGraphics(const HANDLE & hwnd, pos, const std::string & filename, const Color & color)
//}
//
//void Menu_Button::DRAW_Color(const int& Color_) {
//
//	DrawString(str, pos, Color_);
