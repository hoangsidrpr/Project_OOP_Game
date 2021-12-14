#ifndef _GAME_H_
#define _GAME_H_

#include "Sound.h"
#include "Console_Game.h"
#include "Graphic.h"
#include "TrafficLight.h"
#include "Character.h"
#include "Menu.h"


class Game
{
private:
	thread Run_Game;
	Character Human;
	vector<Character> People;
	vector<Animal*> List_Snakes,List_Dogs;
	vector<Vehicle*> List_car, List_Truck, List_carR;
	TrafficLight tf_car,tf_truck;
	bool g_running,gameover, g_process;
	int level,max_level,speed,count_P,key_moving,score,state_S;
	RECT gameboard;
	Menu* menu;
	string profile_load;
public:
	Game();
	Game(const short& , const short& , const std::wstring& , const bool& );

	
	void DrawGameBoard(const COORD&,const Color& );
	void Create_Map();
	void Initialize_Cars();
	void Initialize_Trucks();
	void Initialize_Dogs();
	void Initialize_Snakes();
	void Initialize_Characters();
	void Initialize_setting();
	void Initialize_Menu();


	void Clear_Cars();
	void Clear_Trucks();
	void Clear_Dogs();
	void Clear_Snakes();
	void Clear_Menu();
	void Clear_People();

	template<class T>
	void Object_Moving(vector<T*> ,const bool& );
	template<class T>
	void DrawStoping_Object(vector<T*>);

	void Draw_Setting_S();
	bool WinGame();
	bool GameOver();
	void Dead_Screen();

	void PauseGame();
	void SaveGame(string);
	void LoadGame(string);
	void StartGame();
	void Update_Character();
	void ResetGame();

	void Processing();
	void Gameplay();
};


#endif // !_GAME_H_







