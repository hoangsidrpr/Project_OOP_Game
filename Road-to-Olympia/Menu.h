#ifndef _MENU_H_
#define _MENU_H_
#include "Console_Game.h"
#include "Graphic.h"

class Menu
{
private:
	int state_M,state_S;
	bool quit, g_load,p_game,p_music;
	string load_file;

	void Initialize_Title();

	void Initialize_Menu();
	void choose();

	void Draw_Selection();
	void Draw_Setting_S();


	void About();
	void Setting();
	//void Tutorial();
	void Quit();


	void Music();
public:
	Menu();
	bool IsQuit()const;
	bool IsPlay()const;
	bool IsLoad();
	string Load();
	void setbool();

	void Choose_Menu();
};

#endif // !_MENU_H_



